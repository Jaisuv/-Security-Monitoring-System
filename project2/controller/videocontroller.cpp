#include "videocontroller.h"
#include <QMessageBox>

VideoController* VideoController::vidoeController_ins=nullptr;

VideoController *VideoController::getInstance()
{
    if(nullptr==VideoController::vidoeController_ins)
    {
        VideoController::vidoeController_ins=new VideoController;
    }
    return VideoController::vidoeController_ins;
}

int VideoController::addVideo(QString video_name, QString video_path, QString created_time, QString cover_name, int frame_num)
{
    int res=-2;
    if (VideoModel::getInstance()->addVideo(video_name,video_path,created_time,cover_name,frame_num)==0)
    {
        res=0;
    }
    return res;
}

QList<MyVideo *> VideoController::getVideoList(int start)
{
    QList<MyVideo *> videoList;
    char **qres=nullptr;
    int row=0,col=0;
    int res=VideoModel::getInstance()->getVideoData(start,qres,row,col);
    if(res==0)
    {
        if(row>0)
        {
            for (int i=1;i<=row;i++) {
               videoList.push_back(new MyVideo(atoi(qres[i*col]),qres[i*col+1],qres[i*col+2],qres[i*col+3],qres[i*col+4],atoi(qres[i*col+5])));
            }
        }
        else {
            qDebug()<<"Get data error!";
        }
    }
    else {
        qDebug()<<"Get Video data failed.";
    }
    return videoList;
}

MyVideo *VideoController::getLatest()
{
    MyVideo* videoObj=nullptr;
    char **qres=nullptr;
    int row=0,col=0;
    int res=VideoModel::getInstance()->getLatest(qres,row,col);
    if(res==0)
    {
        if(row>0)
        {
            for (int i=1;i<=row;i++) {
               videoObj=new MyVideo(atoi(qres[i*col]),qres[i*col+1],qres[i*col+2],qres[i*col+3],qres[i*col+4],atoi(qres[i*col+5]));
            }
        }
        else {
            qDebug()<<"Get data error!";
        }
    }
    else {
        qDebug()<<"Get Video data failed.";
    }
    return videoObj;
}

QString VideoController::getVideoPathByName(QString videoName)
{
    QString videoPath;
    char **qres=nullptr;
    int row=0,col=0;
    int res=VideoModel::getInstance()->getVideoPathByName(qres,row,col,videoName);
    if(res==0)
    {
        if(row>0)
        {
            videoPath=qres[col];
        }
        else {
            qDebug()<<"Get data error!";
        }
    }
    else {
        qDebug()<<"Get Video data failed.";
    }
    return videoPath;
}

QList<MyVideo *> VideoController::getVideoListByDate(QString date,int offset)
{
    QList<MyVideo *> videoList;
    char **qres=nullptr;
    int row=0,col=0;
    int res=VideoModel::getInstance()->getVideoByDate(date,offset,qres,row,col);
    if(res==0)
    {
        if(row>0)
        {
            for (int i=1;i<=row;i++) {
               videoList.push_back(new MyVideo(atoi(qres[i*col]),qres[i*col+1],qres[i*col+2],qres[i*col+3],qres[i*col+4],atoi(qres[i*col+5])));
            }
        }
        else {
            qDebug()<<"Get data error!";
        }
    }
    else {
        qDebug()<<"Get Video data failed.";
    }
    return videoList;
}

QString VideoController::getVideoPathById(int id)
{
    QString videoPath;
    char **qres=nullptr;
    int row=0,col=0;
    int res=VideoModel::getInstance()->getVideoPathById(qres,row,col,id);
    if(res==0)
    {
        if(row>0)
        {
            videoPath=qres[col];
        }
        else {
            qDebug()<<"Get data error!";
        }
    }
    else {
        qDebug()<<"Get Video data failed.";
    }
    return videoPath;
}

QString VideoController::getVideoNameById(int id)
{
    QString videoName;
    char **qres=nullptr;
    int row=0,col=0;
    int res=VideoModel::getInstance()->getVideoNameById(qres,row,col,id);
    if(res==0)
    {
        if(row>0)
        {
            videoName=qres[col];
        }
        else {
            qDebug()<<"Get data error!";
        }
    }
    else {
        qDebug()<<"Get Video data failed.";
    }
    return videoName;
}

QString VideoController::getVideoCoverById(int id)
{
    QString coverName;
    char **qres=nullptr;
    int row=0,col=0;
    int res=VideoModel::getInstance()->getVideoCoverById(qres,row,col,id);
    if(res==0)
    {
        if(row>0)
        {
            coverName=qres[col];
        }
        else {
            qDebug()<<"Get data error!";
        }
    }
    else {
        qDebug()<<"Get Video data failed.";
    }
    return coverName;
}

int VideoController::getVideoNumByDate(QString Date)
{
    int videoNum=0;
    char **qres=nullptr;
    int row=0,col=0;
    int res=VideoModel::getInstance()->getVideoNum(Date,qres,row,col);
    if(res==0)
    {
        if(row>0)
        {
            videoNum=atoi(qres[col]);
        }
        else {
            qDebug()<<"Get data error!";
        }
    }
    else {
        qDebug()<<"Get Video data failed.";
    }
    return videoNum;
}

VideoController::VideoController()
{

}
