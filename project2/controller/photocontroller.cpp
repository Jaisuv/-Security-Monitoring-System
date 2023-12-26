#include "photocontroller.h"

PhotoController* PhotoController::photoCtrl_ins=nullptr;

PhotoController *PhotoController::getInstance()
{
    if(nullptr==PhotoController::photoCtrl_ins)
    {
        PhotoController::photoCtrl_ins=new PhotoController;
    }
    return PhotoController::photoCtrl_ins;
}

int PhotoController::addPhoto(QString photo_name, QString photo_path, QString created_time)
{
    int res=-2;
    if(PhotoModel::getInstance()->addPhoto(photo_name,photo_path,created_time)==0)
    {
        res=0;
    }
    return res;
}

QList<MyPhoto *> PhotoController::getInitPhotoList(int start)
{
    QList<MyPhoto *> photoList;
    char **qres=nullptr;
    int row=0,col=0;
    int res=PhotoModel::getInstance()->getLatestPhoto(start,qres,row,col);
    if(res==0)
    {
        if(row>0)
        {
            for (int i=1;i<=row;i++) {
               photoList.push_back(new MyPhoto(atoi(qres[i*col]),qres[i*col+1],qres[i*col+2],qres[i*col+3]));
            }
        }
        else {
            qDebug()<<"Get data error!";
        }
    }
    else {
        qDebug()<<"Get Video data failed.";
    }
    return photoList;
}

QList<MyPhoto *> PhotoController::getMorePhoto(int offFactor)
{
    QList<MyPhoto *> photoList;
    char **qres=nullptr;
    int row=0,col=0;
    int res=PhotoModel::getInstance()->getMorePhoto(offFactor,qres,row,col);
    if(res==0)
    {
        if(row>0)
        {
            for (int i=1;i<=row;i++) {
               photoList.push_back(new MyPhoto(atoi(qres[i*col]),qres[i*col+1],qres[i*col+2],qres[i*col+3]));
            }
        }
        else {
            qDebug()<<"Get data error!";
        }
    }
    else {
        qDebug()<<"Get Video data failed.";
    }
    return photoList;
}

QString PhotoController::getPhotoPathById(int id)
{
    QString photoPath;
    char **qres=nullptr;
    int row=0,col=0;
    int res=PhotoModel::getInstance()->getPhotoPathById(qres,row,col,id);
    if(res==0)
    {
        if(row>0)
        {
            photoPath=qres[col];
        }
        else {
            qDebug()<<"Get data error!";
        }
    }
    else {
        qDebug()<<"Get Video data failed.";
    }
    return photoPath;
}

QString PhotoController::getPhotoNameById(int id)
{
    QString photoName;
    char **qres=nullptr;
    int row=0,col=0;
    int res=PhotoModel::getInstance()->getPhotoNameById(qres,row,col,id);
    if(res==0)
    {
        if(row>0)
        {
            photoName=qres[col];
        }
        else {
            qDebug()<<"Get data error!";
        }
    }
    else {
        qDebug()<<"Get Video data failed.";
    }
    return photoName;
}

QString PhotoController::getPhotoTimeById(int id)
{
    QString photoCreatedTime;
    char **qres=nullptr;
    int row=0,col=0;
    int res=PhotoModel::getInstance()->getPhotoTimeById(qres,row,col,id);
    if(res==0)
    {
        if(row>0)
        {
            photoCreatedTime=qres[col];
        }
        else {
            qDebug()<<"Get data error!";
        }
    }
    else {
        qDebug()<<"Get Video data failed.";
    }
    return photoCreatedTime;
}

QList<MyPhoto *> PhotoController::getPhotoListByDate(int start,QString date)
{
    QList<MyPhoto *> photoList;
    char **qres=nullptr;
    int row=0,col=0;
    int res=PhotoModel::getInstance()->getPhotoByDate(date,start,qres,row,col);
    if(res==0)
    {
        if(row>0)
        {
            for (int i=1;i<=row;i++) {
               photoList.push_back(new MyPhoto(atoi(qres[i*col]),qres[i*col+1],qres[i*col+2],qres[i*col+3]));
            }
        }
        else {
            qDebug()<<"Get data error!";
        }
    }
    else {
        qDebug()<<"Get Video data failed.";
    }
    return photoList;
}

PhotoController::PhotoController()
{

}
