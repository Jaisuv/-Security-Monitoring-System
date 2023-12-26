#ifndef ENCODE2H264_H
#define ENCODE2H264_H
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
#include <QString>
#include <QThread>
#include <QQueue>
#include <QDateTime>
#include "controller/settingcontroller.h"
#include <QImage>
#include "controller/videocontroller.h"

class Encode2H264:public QThread
{
public:
    Encode2H264();
    /**将YUV420P像素数据压缩到AVPacket写入h264压缩格式文件
     * @brief EncodeFrame
     * @param pictureYUV
     */
    void EncodeFrame(AVFrame *pictureYUV);
    //写尾帧,结束此次编码，并将需要释放的资源释放掉
    void writeTail();

    /**编码准备
     * @brief prepareEncode
     */
    void prepareEncode();

    QString getFilename() const;
    void setFilename(const QString &value);

    int getWidth() const;
    void setWidth(int value);

    int getHeight() const;
    void setHeight(int value);
    static QQueue<AVFrame *> encodedFrameQue;
    static QQueue<QImage> ImgQueue;
    int count; //帧数统计
    int timeFactor;
private:
    AVFormatContext *pFormatContext;
    AVCodecContext *pCodecContext;
    AVCodec *encoder;
    AVPacket *pkt;//码流，包
    int pkt_index;
    QString filename;
    int width,height;
    QString videoName,videoPath,timestr,coverName;
protected:
    void run();
};

#endif // ENCODE2H264_H
