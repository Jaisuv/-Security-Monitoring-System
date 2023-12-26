#include "replayh264.h"
#include <QDebug>
#include <stdio.h>

RePlayH264::RePlayH264(QString filename)
{
    this->isRun=true;
    this->interval=80;
    this->speedFactor=2;
    //注册组件和设备
    av_register_all();
    //成员初始化
    this->pFormatContext=avformat_alloc_context();
    int res=avformat_open_input(&this->pFormatContext,filename.toUtf8(),nullptr,nullptr);
    if(res!=0)
    {
        qDebug()<<"fail to open camera";
        return;
    }
    //2.查找流媒体数据
    res = avformat_find_stream_info(pFormatContext,nullptr);
    if(res<0)
    {
        qDebug()<<"fail to find stream info ";
        return;
    }
    this->video_index=-1;
    //3.找到视频流
    for(int i=0;i<pFormatContext->nb_streams;i++)
    {
        if(pFormatContext->streams[i]->codec->codec_type== AVMEDIA_TYPE_VIDEO)
        {
            video_index=i;
            break;
        }
    }
    if(video_index==-1)
    {
        qDebug()<<"fail to find video stream info";
        return;
    }
    //4.查找解码器
    this->pCodecContent=pFormatContext->streams[video_index]->codec;//编解码上下文结构体
    this->decoder=avcodec_find_decoder(pCodecContent->codec_id);//编解码结构体
    if(nullptr==decoder)
    {
        qDebug()<<"fail to find decoder";
        return;
    }
    //5.打开解码器
    res=avcodec_open2(pCodecContent,decoder,nullptr);
    if(res!=0)
    {
        qDebug()<<"fail to open decoder";
        return;
    }
    //6.数据准备
    this->pkt = (AVPacket *)malloc(sizeof (AVPacket)); // 开空间
    this->size =pCodecContent->width*pCodecContent->height;
    res=av_new_packet(pkt,size);
    if(res!=0)
    {
        qDebug()<<" fail to av_new_packet";
        return;
    }
//    qDebug()<<"success to av_new_packet";
    this->picture=av_frame_alloc();  //开空间  像素数据-带无效数据
    this->pictureRGB=av_frame_alloc();  //开空间 像素数据-纯净
    picture->width=pCodecContent->width;
    picture->height=pCodecContent->height;
    picture->format=pCodecContent->pix_fmt;
    //RGB像素数据--用于播放在屏幕上
    pictureRGB->width=pCodecContent->width;
    pictureRGB->height=pCodecContent->height;
    pictureRGB->format=pCodecContent->pix_fmt;
    //=======================RGB压缩编码============================
    //压缩的一帧RGB32的大小
    int numByteRGB=avpicture_get_size(AV_PIX_FMT_RGB32,pCodecContent->width,pCodecContent->height);
    //动态开空间
    this->bufferRGB=(uint8_t *)av_malloc(numByteRGB*sizeof (uint8_t));
    //填充规则
    avpicture_fill((AVPicture*)pictureRGB,bufferRGB,
                   AV_PIX_FMT_RGB32,pCodecContent->width,pCodecContent->height);
    //转置规则
    this->swsContentRGB=sws_getContext(pCodecContent->width,pCodecContent->height,pCodecContent->pix_fmt,
                                             pCodecContent->width,pCodecContent->height,AV_PIX_FMT_RGB32,
                                       SWS_BICUBIC,nullptr,nullptr,nullptr);
}

RePlayH264::~RePlayH264()
{
   avformat_close_input(&this->pFormatContext);
}

void RePlayH264::run()
{
    while (av_read_frame(pFormatContext,pkt)==0)            //判断是否视频流
    {
        while(1)
        {
            if(this->isRun)
            {
                if(pkt->stream_index==video_index)
                {
                    int ptr=-1;
                    avcodec_decode_video2(pCodecContent,picture,&ptr,pkt);
                    if(ptr!=0)
                    {
                        sws_scale(swsContentRGB,picture->data,picture->linesize,0,picture->height,
                                 pictureRGB->data,pictureRGB->linesize);

                        this->img=QImage(static_cast<uchar*>(bufferRGB),pictureRGB->width,pictureRGB->height,QImage::Format_RGB32);

                        msleep(this->interval/speedFactor);//倍速计算公式

                        emit sendImg3(this->img);

                    }
                }
                //对pkt解引用
                av_packet_unref(pkt);
                break;
            }
        }
    }
    emit playFinish();
}
