#include "videomodel.h"

VideoModel* VideoModel::videoModel_ins=nullptr;//静态成员初始化

VideoModel *VideoModel::getInstance()
{
    if(nullptr==VideoModel::videoModel_ins)
    {
        VideoModel::videoModel_ins=new VideoModel;
    }
    return VideoModel::videoModel_ins;
}

int VideoModel::addVideo(QString video_name, QString video_path, QString created_time, QString cover_name, int frame_num)
{
    QString insertVideoSQL=QString("INSERT INTO tbl_video(video_name,video_path,created_time,cover_name,frame_num)\
       VALUES('%1','%2','%3','%4',%5);").arg(video_name,video_path,created_time,cover_name).arg(frame_num);
    Singleton_db *dbInstance=Singleton_db::getInstance();
    int res=dbInstance->insertDeleteUpdate(insertVideoSQL);
    if(SQLITE_OK==res)
    {
        return 0;
    }
    else {
        return -1;
    }
}

int VideoModel::getVideoData(int offset,char **&qres, int &row, int &col)
{
    QString videoSelectSQL=QString("SELECT * FROM tbl_video ORDER BY created_time DESC LIMIT 4 OFFSET %1;").arg(offset);
    Singleton_db *dbInstance=Singleton_db::getInstance();
    int res=dbInstance->getData(videoSelectSQL,qres,row,col);
    if(SQLITE_OK==res)
    {
        if(row>0)
        {
            return 0; //查找到数据
        }
        else {
            return 1;   //无数据
        }
    }
    else {
        return -1;  //执行SQL失败
    }
}

int VideoModel::getLatest(char **&qres, int &row, int &col)
{
    QString videoSelectSQL=QString("SELECT * FROM tbl_video ORDER BY created_time DESC LIMIT 1;");
    Singleton_db *dbInstance=Singleton_db::getInstance();
    int res=dbInstance->getData(videoSelectSQL,qres,row,col);
    if(SQLITE_OK==res)
    {
        if(row>0)
        {
            return 0; //查找到数据
        }
        else {
            return 1;   //无数据
        }
    }
    else {
        return -1;  //执行SQL失败
    }
}

int VideoModel::getVideoByDate(QString date,int offset,char **&qres,int &row,int &col)
{
    QString selectByDateSQL=QString("SELECT * FROM tbl_video WHERE created_time LIKE '%%%1%%' ORDER BY created_time DESC LIMIT 4 OFFSET %2 ;").arg(date).arg(offset);
    Singleton_db *dbInstance=Singleton_db::getInstance();
    int res=dbInstance->getData(selectByDateSQL,qres,row,col);
    if(SQLITE_OK==res)
    {
        if(row>0)
        {
            return 0; //查找到数据
        }
        else {
            return 1;   //无数据
        }
    }
    else {
        return -1;  //执行SQL失败
    }
}

int VideoModel::getVideoPathByName(char **&qres, int &row, int &col, QString videoName)
{
    QString videoPathSelectSQL=QString("SELECT video_path FROM tbl_video WHERE video_name='%1';").arg(videoName);
    Singleton_db *dbInstance=Singleton_db::getInstance();
    int res=dbInstance->getData(videoPathSelectSQL,qres,row,col);
    if(SQLITE_OK==res)
    {
        if(row>0)
        {
            return 0; //查找到数据
        }
        else {
            return 1;   //无数据
        }
    }
    else {
        return -1;  //执行SQL失败
    }
}

int VideoModel::getVideoPathById(char **&qres, int &row, int &col, int id)
{
    QString videoPathSelectSQL=QString("SELECT video_path FROM tbl_video WHERE video_id = %1;").arg(id);
    Singleton_db *dbInstance=Singleton_db::getInstance();
    int res=dbInstance->getData(videoPathSelectSQL,qres,row,col);
    if(SQLITE_OK==res)
    {
        if(row>0)
        {
            return 0; //查找到数据
        }
        else {
            return 1;   //无数据
        }
    }
    else {
        return -1;  //执行SQL失败
    }
}

int VideoModel::getVideoNameById(char **&qres, int &row, int &col, int id)
{
    QString videoPathSelectSQL=QString("SELECT video_name FROM tbl_video WHERE video_id = %1;").arg(id);
    Singleton_db *dbInstance=Singleton_db::getInstance();
    int res=dbInstance->getData(videoPathSelectSQL,qres,row,col);
    if(SQLITE_OK==res)
    {
        if(row>0)
        {
            return 0; //查找到数据
        }
        else {
            return 1;   //无数据
        }
    }
    else {
        return -1;  //执行SQL失败
    }
}

int VideoModel::getVideoCoverById(char **&qres, int &row, int &col, int id)
{
    QString videoPathSelectSQL=QString("SELECT cover_name FROM tbl_video WHERE video_id = %1;").arg(id);
    Singleton_db *dbInstance=Singleton_db::getInstance();
    int res=dbInstance->getData(videoPathSelectSQL,qres,row,col);
    if(SQLITE_OK==res)
    {
        if(row>0)
        {
            return 0; //查找到数据
        }
        else {
            return 1;   //无数据
        }
    }
    else {
        return -1;  //执行SQL失败
    }
}

int VideoModel::getVideoNum(QString date,char **&qres,int &row,int &col)
{
    QString selectByDateSQL=QString("SELECT COUNT(*) FROM tbl_video WHERE created_time LIKE '%%%1%%' ;").arg(date);
    Singleton_db *dbInstance=Singleton_db::getInstance();
    int res=dbInstance->getData(selectByDateSQL,qres,row,col);
    if(SQLITE_OK==res)
    {
        if(row>0)
        {
            return 0; //查找到数据
        }
        else {
            return 1;   //无数据
        }
    }
    else {
        return -1;  //执行SQL失败
    }
}

VideoModel::VideoModel()
{

}
