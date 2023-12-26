#include "encode2h264.h"
#include <QDebug>

QQueue<AVFrame *> Encode2H264::encodedFrameQue;
QQueue<QImage> Encode2H264::ImgQueue;

Encode2H264::Encode2H264()
{
    this->pkt_index=0;  //只初始化一次，表示视频流的顺序
    count=0;
    this->timeFactor=SettingController::getInstance()->getCapInterval();
}

void Encode2H264::EncodeFrame(AVFrame *pictureYUV)
{
    int res=avcodec_send_frame(this->pCodecContext,pictureYUV);
    if(res<0)
    {
        qDebug()<<"发送给编码器失败";
        return;
    }
    //qDebug()<<"成功发送给编码器";
    //一帧YUV420P像素数据，1个AVPacket可能放不下，需要2个AVPacket，循环处理去接收码流数据
    while (res>=0) {
        pictureYUV->pts=pkt_index++;
        res=avcodec_receive_packet(this->pCodecContext,this->pkt);
        if(res==AVERROR_EOF || res==AVERROR(EAGAIN))
        {
            break;
        }
        av_interleaved_write_frame(this->pFormatContext,this->pkt);
        qDebug()<<"now encode num："<<pkt_index;
        //这里帧数加一
    }
}

void Encode2H264::writeTail()
{
    //写尾帧
    av_write_trailer(this->pFormatContext);
    //关闭输入流
    avio_close(this->pFormatContext->pb);
    //释放视频信息
    avformat_free_context(this->pFormatContext);

}

void Encode2H264::prepareEncode()
{
    //上下文结构体要在准备中，构造只执行一次，后面写尾巴帧就不会再开空间
    this->pFormatContext=avformat_alloc_context();
    this->pkt=av_packet_alloc();

    //1.注册组件
    av_register_all();
    //2.猜测输出文件封装格式
    AVOutputFormat *outputFormat=av_guess_format(nullptr,this->filename.toUtf8(),nullptr);
    if(nullptr==outputFormat)
    {
        qDebug()<<"猜测格式失败";
        return;
    }
    //设置输出格式
    this->pFormatContext->oformat=outputFormat;
    //3.打开视频文件流
    int res=avio_open(&this->pFormatContext->pb,this->filename.toUtf8(),AVIO_FLAG_WRITE);
    if(res<0)
    {
        qDebug()<<"打开视频文件流失败";
        return;
    }
    //4.新建视频流
    AVStream *newStream=avformat_new_stream(this->pFormatContext,nullptr);
    if(nullptr==newStream)
    {
        qDebug()<<"新建视频流失败";
        return;
    }
    //5.编码器参数设置
    //5.1 初始化编码器上下文结构体，保存视频编码相关信息
    this->pCodecContext=newStream->codec;
    //宽高信息从解码器解得
    this->pCodecContext->width=this->width;       //可以变成类成员属性
    this->pCodecContext->height=this->height;      //可以变成类成员属性
    this->pCodecContext->time_base={1,25};    //时间基 1s播放的帧数
    this->pCodecContext->bit_rate=400000;     //码率
    this->pCodecContext->framerate={25,1};    //帧率
    //清晰度设置
    this->pCodecContext->gop_size=10; //10帧为一个单位，官方建议
    this->pCodecContext->qmax=51;
    this->pCodecContext->qmin=10;
    this->pCodecContext->max_b_frames=0;      //没有B帧,只有I帧和P帧
    this->pCodecContext->pix_fmt=AV_PIX_FMT_YUV420P;  //设置编码格式-YUV420P像素数
    this->pCodecContext->codec_type=AVMEDIA_TYPE_VIDEO;   //设置编码的流的格式
    this->pCodecContext->codec_id=outputFormat->video_codec;  //设置编码器的id
    //6.根据猜测到的编码器的ID查找编码器
    this->encoder=avcodec_find_encoder(this->pCodecContext->codec_id);
    if(nullptr==this->encoder)
    {
        qDebug()<<"未找到编码器";
        return;
    }
    //7.打开编码器
    res = avcodec_open2(this->pCodecContext,this->encoder,nullptr);
    if(res<0)
    {
        qDebug()<<"打开编码器失败";
        return;
    }
    //8.写入编码的头部信息，完成编码前的所有初始化工作
    res=avformat_write_header(pFormatContext,nullptr);
    if(res<0)
    {
        qDebug()<<"写入头部信息失败";
        return;
    }
}

QString Encode2H264::getFilename() const
{
    return filename;
}

void Encode2H264::setFilename(const QString &value)
{
    filename = value;
}

int Encode2H264::getWidth() const
{
    return width;
}

void Encode2H264::setWidth(int value)
{
    width = value;
}

int Encode2H264::getHeight() const
{
    return height;
}

void Encode2H264::setHeight(int value)
{
    height = value;
}

void Encode2H264::run()
{
    while (1) {
        msleep(10);//qDebug()<<count;//要打印一下，不然队列判断是否为空时候太快会不进入判断，或者msleep(10)
        if(!Encode2H264::encodedFrameQue.isEmpty())//不为空 计数器为0开始编码
        {
            if(count==0)
            {
                QDateTime datetime;
                timestr=datetime.currentDateTime().toString("yyyyMMddHHmmss");
                videoPath=SettingController::getInstance()->getVideoPathInDB();
                QString videoSavePathName=videoPath+"/"+timestr+".h264";
                videoName=timestr+".h264";
                coverName=timestr+".jpg";
                this->filename=videoSavePathName;//文件名
                this->prepareEncode();

                //保存视频封面
                QString coverSavePath=videoSavePathName.replace(".h264",".jpg");//替换文件后缀名
                QImage videoCoverImg=Encode2H264::ImgQueue.dequeue();
                videoCoverImg.save(coverSavePath);
            }
            this->EncodeFrame(Encode2H264::encodedFrameQue.dequeue());
            count++;
            if(count>=1500*this->timeFactor)
            {
                this->writeTail();
                VideoController::getInstance()->addVideo(videoName,videoPath,timestr,coverName,count);
                count=0;
            }
        }
    }
}



