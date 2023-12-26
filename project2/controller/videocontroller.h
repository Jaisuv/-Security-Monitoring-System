#ifndef VIDEOCONTROLLER_H
#define VIDEOCONTROLLER_H
#include <QString>
#include "model/videomodel.h"
#include "MyClass/myvideo.h"
#include <QList>

class VideoController
{
public:
    static VideoController *getInstance();
    int addVideo(QString video_name,QString video_path,QString created_time,QString cover_name,int frame_num);
    QList<MyVideo *> getVideoList(int start);
    MyVideo *getLatest();
    QString getVideoPathByName(QString videoName);
    QList<MyVideo *> getVideoListByDate(QString date,int offset);
//根据id获取视频信息
    QString getVideoPathById(int id);
    QString getVideoNameById(int id);
    QString getVideoCoverById(int id);
/************************************************************
* 函数名称：
* 函数功能：根据日期，筛选视频记录数量
* 参   数:
* 返 回 值:
**************************************************************/
    int getVideoNumByDate(QString Date);
private:
    VideoController();
    static VideoController* vidoeController_ins;
};

#endif // VIDEOCONTROLLER_H
