#include "settingcontroller.h"
#include <QDebug>

SettingController *SettingController::settingCtrl_ins=nullptr;

SettingController *SettingController::getInstance()
{
    if(nullptr==SettingController::settingCtrl_ins)
    {
        SettingController::settingCtrl_ins=new SettingController;
    }
    return SettingController::settingCtrl_ins;
}

//返回0说明存在数据
int SettingController::getSetting()
{
    int res=-2;
    if(SettingModel::getInstance()->getSetting()==0) //==0说明有数据，==1才是没数据
    {
        res=0;
    }
    return res;
}

int SettingController::updateSetting(QString video_path,QString photo_path,int cap_interval,QString camera_name)
{
    int res=-2;
    if(SettingModel::getInstance()->updateTbl_setting(video_path,photo_path,cap_interval,camera_name)==0)
    {
        res=0;
    }
    return res;
}

QString SettingController::getCameraNameInDB()
{
    QString cameraName="";
    char **qres=nullptr;    //结果集
    int row=0,col=0;
    int res=SettingModel::getInstance()->selectCameraName(qres,row,col);
    if(0==res)//成功获取数据
    {
        cameraName=qres[col];
    }
    else{
        qDebug()<<"获取摄像头失败";
    }
    return cameraName;
}

QString SettingController::getVideoPathInDB()
{
    QString videoPath="";
    char **qres=nullptr;    //结果集
    int row=0,col=0;
    int res=SettingModel::getInstance()->selectVideoPath(qres,row,col);
    if(0==res)//成功获取数据
    {
        videoPath=qres[col];
    }
    else{
        qDebug()<<"获取视频文件夹失败";
    }
    return videoPath;
}

QString SettingController::getPhotoPathInDB()
{
    QString photoPath="";
    char **qres=nullptr;    //结果集
    int row=0,col=0;
    int res=SettingModel::getInstance()->selectPhotoPath(qres,row,col);
    if(0==res)//成功获取数据
    {
        photoPath=qres[col];
    }
    else{
        qDebug()<<"获取照片文件夹失败";
    }
    return photoPath;
}

int SettingController::getCapInterval()
{
    int intervalInLib=0;
    char **qres=nullptr;    //结果集
    int row=0,col=0;
    int res=SettingModel::getInstance()->selectCaptureInterval(qres,row,col);
    if(0==res)//成功获取数据
    {
        intervalInLib=atoi(qres[col]);
    }
    else{
        qDebug()<<"获取照片文件夹失败";
    }
    return intervalInLib;
}

SettingController::SettingController()
{

}
