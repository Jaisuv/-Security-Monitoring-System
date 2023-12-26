#ifndef CAMERAOPENTHREAD_H
#define CAMERAOPENTHREAD_H
extern "C"
{
    #include "libavcodec/avcodec.h"         //编解码库
    #include "libavdevice/avdevice.h"       //输入输出设备库；读取摄像头
    #include "libavfilter/avfilter.h"       //音视频滤镜库；进行音视频处理与编辑
    #include "libavformat/avformat.h"       //格式
    #include "libavutil/avutil.h"           //巩固
    #include "libswresample/swresample.h"
    #include "libswscale/swscale.h"         //转置
}
#include <QThread>
#include <QImage>
#include "thread/encode2h264.h"
#include "controller/logcontroller.h"

class CameraOpenThread :public QThread
{
    Q_OBJECT
public:
    explicit CameraOpenThread(QString cameraname); //构造记得传入摄像头的名字
    ~CameraOpenThread();

    AVFormatContext *getPFormatContext() const;
    void setPFormatContext(AVFormatContext *value);
private:
    AVFormatContext *pFormatContext;    //封装格式上下文结构体
    int video_index;                    //视频流下标
    AVCodecContext *pCodecContent;      //编解码器上下文结构体
    AVCodec *decoder;                   //编解码器
    AVPacket *pkt;                      //存储一帧压缩码流数据
    int size;
    AVFrame *picture,*pictureRGB,*pictureYUV;       //携带无用像素数据  和纯净像素数据
    uint8_t *bufferRGB,*bufferYUV;                    //
    SwsContext *swsContentRGB,*swsContentYUV;          //转置规则
    QImage img;                         //发送的图片
    //编码线程
    Encode2H264 *toH264;
    int timeFactor;
protected:
    void run();                     //持续解码的过程，发送图片
signals:
    void sendImg(QImage);
};

#endif // CAMERAOPENTHREAD_H
