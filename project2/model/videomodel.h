#ifndef VIDEOMODEL_H
#define VIDEOMODEL_H
#include "singleton_db.h"
#include <QString>
#include <QDebug>

class VideoModel
{
public:
    static VideoModel *getInstance();
    int addVideo(QString video_name,QString video_path,QString created_time,QString cover_name,int frame_num);
    int getVideoData(int offset,char **&qres,int &row,int &col);
    int getLatest(char **&qres,int &row,int &col);
    int getVideoByDate(QString date,int offset,char **&qres,int &row,int &col);
/************************************************************
* 函数名称：getVideoPathByName
* 函数功能：根据视频名称获取视频路径
* 参   数:
*        A:   char **&qres,int &row,int &col ：从数据库中查询的结果
*        B:     int
* 返 回 值:int
**************************************************************/
    int getVideoPathByName(char **&qres,int &row,int &col,QString videoName);
/************************************************************
* 函数名称：
* 函数功能：以下三条函数，根据ID查询信息
* 参   数:
* 返 回 值:
**************************************************************/
    int getVideoPathById(char **&qres,int &row,int &col,int id);
    int getVideoNameById(char **&qres,int &row,int &col,int id);
    int getVideoCoverById(char **&qres,int &row,int &col,int id);
/************************************************************
* 函数名称：
* 函数功能：根据日期，获取当天视频数量
* 参   数:
* 返 回 值:
**************************************************************/
    int getVideoNum(QString date,char **&qres,int &row,int &col);
private:
    VideoModel();
    static VideoModel* videoModel_ins;
};

#endif // VIDEOMODEL_H
