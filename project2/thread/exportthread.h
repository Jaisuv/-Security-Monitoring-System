#ifndef EXPORTTHREAD_H
#define EXPORTTHREAD_H
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

class ExportThread :public QThread
{
    Q_OBJECT
public:
    ExportThread(QString filename);
    void Exportsetting();
    QString getSavePath() const;
    void setSavePath(const QString &value);
    void transcode();
private:
    AVFormatContext *pFormatContext,*outFormatContext;
    AVOutputFormat *outputFormat;
    AVStream *newStream;
    int videoIndex;
    AVPacket *pkt;
    int frameCount;
    QString savePath;
protected:
    void run();
signals:
    void ExportSuccess();
};

#endif // EXPORTTHREAD_H
