#include "exportthread.h"
#include <QDebug>
#include <QMessageBox>

ExportThread::ExportThread(QString filename)
{
    //1.注册组件
    av_register_all();
    //2.打开视频流
    this->pFormatContext=avformat_alloc_context();
    this->videoIndex=-1;
    this->pkt=(AVPacket *)malloc(sizeof(AVPacket));
    this->frameCount=0;
//===========================输入的视频，需要被转码的视频=======================
    int res= avformat_open_input(&this->pFormatContext,filename.toUtf8(),nullptr,nullptr);
    if(res!=0)
    {
        qDebug()<<"打开视频文件流失败";
        return;
    }
    //3.查找是否有流媒体信息
    res = avformat_find_stream_info(this->pFormatContext,nullptr);
    if(res<0)
    {
        qDebug()<<"无法获取视频流信息";
        return;
    }
    //4.查找视频流
    for (int i=0;i<this->pFormatContext->nb_streams;i++) {
        if(this->pFormatContext->streams[i]->codec->codec_type==AVMEDIA_TYPE_VIDEO)
        {
            this->videoIndex=i;
            break;
        }
    }
    if(this->videoIndex==-1)
    {
        qDebug()<<"未找到视频流";
        return;
    }
    qDebug()<<"输入准备已完成";
}

void ExportThread::Exportsetting()
{
    //5.猜测封装格式
    this->outputFormat=av_guess_format(nullptr,savePath.toUtf8(),nullptr);
    if(nullptr==outputFormat)
    {
        qDebug()<<"猜测格式失败";
        return;
    }
    //6.打开目标文件流
    this->outFormatContext=avformat_alloc_context();
    this->outFormatContext->oformat=this->outputFormat;
    //===========================转换格式======================
    int res=avio_open(&this->outFormatContext->pb,savePath.toUtf8(),AVIO_FLAG_WRITE);
    if(res<0)
    {
        qDebug()<<"打开视频文件流失败";
        return;
    }
    //7.新建目标视频流
    this->newStream=avformat_new_stream(this->outFormatContext,nullptr);
    if(nullptr==newStream)
    {
        qDebug()<<"新建流失败";
        return;
    }
    //8.编码器参数设置
    res=avcodec_parameters_copy(this->newStream->codecpar,this->pFormatContext->streams[videoIndex]->codecpar);
    if(res<0)
    {
        qDebug()<<"编码器参数设置失败";
        return;
    }
    this->newStream->codecpar->codec_tag=0;
    this->newStream->codecpar->codec_type=AVMEDIA_TYPE_VIDEO;
    //9.写入头部信息
    res=avformat_write_header(this->outFormatContext,nullptr);
    if(res<0)
    {
        qDebug()<<"写入头部信息失败";
        return;
    }
}

QString ExportThread::getSavePath() const
{
    return savePath;
}

void ExportThread::setSavePath(const QString &value)
{
    savePath = value;
}

void ExportThread::transcode()
{
    while (av_read_frame(this->pFormatContext,this->pkt)==0) {
        //判断是不是视频流
        if(this->pkt->stream_index==this->videoIndex)
        {
            this->frameCount++;
            qDebug()<<"当前帧: "<<this->frameCount;
            //转码--时间基的转换与设置
            //没有时间基的设置
            if(this->pkt->pts==AV_NOPTS_VALUE)
            {
                //时间基的转换
                AVRational time_base1=this->pFormatContext->streams[videoIndex]->time_base;
                //计算两帧之间的长度
                int64_t duration=(double)AV_TIME_BASE/av_q2d(this->pFormatContext->streams[videoIndex]->r_frame_rate);
                //计算显示时间基
                this->pkt->pts=(double)(frameCount*duration)/(double)(av_q2d(time_base1)*AV_TIME_BASE);
                //无B帧，解码时间基=显示时间基
                this->pkt->dts=this->pkt->pts;
                this->pkt->duration=duration/(double)(av_q2d(time_base1)*AV_TIME_BASE);
            }
            else if (this->pkt->pts<this->pkt->dts)//有B帧，显示时间基大于界面时间基不做处理
            {
                continue;
            }
            //显示时间基转换
           this->pkt->pts=av_rescale_q_rnd(this->pkt->pts,
                                           this->pFormatContext->streams[videoIndex]->time_base,
                                           this->newStream->time_base,
                                           (AVRounding)(AV_ROUND_INF|AV_ROUND_PASS_MINMAX));
            //解码时间基的转换
            this->pkt->dts=av_rescale_q_rnd(this->pkt->dts,
                                            this->pFormatContext->streams[videoIndex]->time_base,
                                            this->newStream->time_base,
                                            (AVRounding)(AV_ROUND_INF|AV_ROUND_PASS_MINMAX));
            this->pkt->duration=av_rescale_q(this->pkt->duration,
                                             this->pFormatContext->streams[videoIndex]->time_base,
                                             this->newStream->time_base);
            this->pkt->pos=-1;
            this->pkt->flags|=AV_PKT_FLAG_KEY;
            this->pkt->stream_index=0;
            //写入数据到输出视频信息结构体
            av_interleaved_write_frame(this->outFormatContext,this->pkt);
        }
        av_packet_unref(this->pkt);
    }
    //写入尾巴帧
    av_write_trailer(this->outFormatContext);
    //关闭编码器
    avcodec_close(this->outFormatContext->streams[videoIndex]->codec);
    av_freep(&this->outFormatContext->streams[videoIndex]->codec);
    //关闭输出流
    avio_close(this->outFormatContext->pb);
    //释放输出信息结构体
    av_free(this->outFormatContext);
    //关闭输入流
    avformat_close_input(&this->pFormatContext);
    //释放输入视频信息结构体
    av_free(this->pFormatContext);
    //释放包
    av_packet_free(&this->pkt);
    emit ExportSuccess();
}

void ExportThread::run()
{
    this->transcode();
}


