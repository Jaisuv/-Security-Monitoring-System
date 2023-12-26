#ifndef PLAYH264_H
#define PLAYH264_H
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

class PlayH264:public QThread
{
    Q_OBJECT
public:
    PlayH264(QString filename);
    ~PlayH264();
    bool isRun;
    double getSpeedFactor() const;
    void setSpeedFactor(double value);
private:
    AVFormatContext *pFormatContext;    //封装格式上下文结构体
    int video_index;                    //视频流下标
    AVCodecContext *pCodecContent;      //编解码器上下文结构体
    AVCodec *decoder;                   //编解码器
    AVPacket *pkt;                      //存储一帧压缩码流数据
    int size;
    AVFrame *picture,*pictureRGB;       //携带无用像素数据  和纯净像素数据
    uint8_t *bufferRGB;                    //
    SwsContext *swsContentRGB;          //转置规则
    QImage img;                         //发送的图片
    unsigned long interval;
    unsigned long speedFactor;
protected:
    void run();
signals:
    void sendImg2(QImage);
public slots:
    void changeSpeed(int);
};

#endif // PLAYH264_H
