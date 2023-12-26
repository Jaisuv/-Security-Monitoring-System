#include "cameraopenthread.h"
#include <QDebug>
#include <stdio.h>

CameraOpenThread::CameraOpenThread(QString cameraname)
{
    this->timeFactor=SettingController::getInstance()->getCapInterval();
    //编码线程类
    this->toH264=new Encode2H264;
    //注册组件和设备
    av_register_all();
    avdevice_register_all();
    //成员初始化
    this->pFormatContext=avformat_alloc_context();
    QString camera ="video="+cameraname;
    AVInputFormat *fmt =av_find_input_format("dshow");//视频打开方式，推流方式
    int res=avformat_open_input(&this->pFormatContext,camera.toUtf8(),fmt,nullptr);
    if(res!=0)
    {
        qDebug()<<"fail to open camera";
        return;
    }
//    qDebug()<<"success to open camera";
    //2.查找流媒体数据
    res = avformat_find_stream_info(pFormatContext,nullptr);
    if(res<0)
    {
        qDebug()<<"fail to find stream info ";
        return;
    }
//    qDebug()<<"success to find stream info";
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
//    qDebug()<<"success to find video stream info";
    //4.查找解码器
    this->pCodecContent=pFormatContext->streams[video_index]->codec;//编解码上下文结构体
    this->decoder=avcodec_find_decoder(pCodecContent->codec_id);//编解码结构体
    if(nullptr==decoder)
    {
        qDebug()<<"fail to find decoder";
        return;
    }
//    qDebug()<<"success to find decoder";
    //5.打开解码器
    res=avcodec_open2(pCodecContent,decoder,nullptr);
    if(res!=0)
    {
        qDebug()<<"fail to open decoder";
        return;
    }
//    qDebug()<<"success to open decoder";
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
    this->pictureYUV=av_frame_alloc();

    picture->width=pCodecContent->width;
    picture->height=pCodecContent->height;
    picture->format=pCodecContent->pix_fmt;
    //RGB像素数据--用于播放在屏幕上
    pictureRGB->width=pCodecContent->width;
    pictureRGB->height=pCodecContent->height;
    pictureRGB->format=pCodecContent->pix_fmt;
    //YUV像素数据--用于存储
    pictureYUV->width=pCodecContent->width;
    pictureYUV->height=pCodecContent->height;
    pictureYUV->format=pCodecContent->pix_fmt;

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
    //========================YUV压缩编码=========================================
    //压缩的一帧YUV420P的大小
    int numByteYUV=avpicture_get_size(AV_PIX_FMT_YUV420P,pCodecContent->width,pCodecContent->height);
    this->bufferYUV=(uint8_t *)av_malloc(numByteYUV*sizeof (uint8_t));
    avpicture_fill((AVPicture*)pictureYUV,bufferYUV,
                   AV_PIX_FMT_YUV420P,pCodecContent->width,pCodecContent->height);

    //YUV转置规则
    this->swsContentYUV=sws_getContext(pCodecContent->width,pCodecContent->height,pCodecContent->pix_fmt,
                                       pCodecContent->width,pCodecContent->height,AV_PIX_FMT_YUV420P,
                                       SWS_BICUBIC,nullptr,nullptr,nullptr);

    this->toH264->setWidth(pCodecContent->width);
    this->toH264->setHeight(pCodecContent->height);
    //编码成h264的线程开启
    this->toH264->start();
}

CameraOpenThread::~CameraOpenThread()
{
    avformat_close_input(&this->pFormatContext);
}

AVFormatContext *CameraOpenThread::getPFormatContext() const
{
    return pFormatContext;
}

void CameraOpenThread::setPFormatContext(AVFormatContext *value)
{
    pFormatContext = value;
}

void CameraOpenThread::run()
{
    int num=0;  //帧数

    //7 读取码流数据
    while (av_read_frame(pFormatContext,pkt)==0)
    {
        //判断是否视频流
        if(pkt->stream_index==video_index)
        {
            int ptr=-1;
            avcodec_decode_video2(pCodecContent,picture,&ptr,pkt);
            if(ptr!=0)
            {
                sws_scale(swsContentRGB,picture->data,picture->linesize,0,picture->height,
                         pictureRGB->data,pictureRGB->linesize);
                sws_scale(swsContentYUV,picture->data,picture->linesize,0,picture->height,
                         pictureYUV->data,pictureYUV->linesize);

                Encode2H264::encodedFrameQue.enqueue(pictureYUV);
                this->img=QImage((uchar*)bufferRGB,pictureRGB->width,pictureRGB->height,QImage::Format_RGB32);
                if(num==0)
                {
                    Encode2H264::ImgQueue.enqueue(this->img);
                }
                num++;
                emit sendImg(this->img);
                if(num>=1500*this->timeFactor){
                    num=0;
                }
            }
        }
        //对pkt解引用
        av_packet_unref(pkt);
    }
}

