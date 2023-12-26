#include "settingmodel.h"

//静态成员初始化
SettingModel *SettingModel::settingModel_ins=nullptr;

SettingModel *SettingModel::getInstance()
{
    if(nullptr==SettingModel::settingModel_ins)
    {
        SettingModel::settingModel_ins=new SettingModel;
    }
    return SettingModel::settingModel_ins;
}

int SettingModel::addSetting(QString video_path, QString photo_path, int cap_interval, QString camera_name)
{
    QString settingSelect=QString("SELECT * FROM tbl_setting");
    char **qres=nullptr;
    int row=0,col=0;
    Singleton_db *dbInstance=Singleton_db::getInstance();
    int res = dbInstance->getData(settingSelect,qres,row,col);
    if(SQLITE_OK==res)
    {
        if(row>0)   //已经存在一条设置信息
        {
            return 1;   //设置信息已经存在
        }
    }
    else {
        return -1;     //SQL执行失败
    }
    QString settingAdd=QString("INSERT INTO tbl_setting(video_path,photo_path,cap_interval,camera_name) \
            VALUES('%1','%2',%3,'%4');").arg(video_path,photo_path).arg(cap_interval).arg(camera_name);
    res= dbInstance->insertDeleteUpdate(settingAdd);
    return 0;
}

//查询设置表中是否有数据存在
//返回0说明有数据
int SettingModel::getSetting()
{
    QString selectSetting=QString("SELECT * FROM tbl_setting;");
    char **qres=nullptr;
    int row=0,col=0;
    //数据库单例
    Singleton_db *dbInstance=Singleton_db::getInstance();
    int res=dbInstance->getData(selectSetting,qres,row,col);
    if(SQLITE_OK==res)
    {
        if(row>0)       //设置表中存在数据
        {
            return 0;
        }
        else {
            return 1;   //设置表中没有数据
        }
    }
    else {
        return -1;      //SQL执行失败
    }
}

int SettingModel::updateTbl_setting(QString video_path, QString photo_path, int cap_interval, QString camera_name)
{
    //设置表中始终只有一条数据，要更新的时候直接把表中的数据全部删掉
    QString deleteSQL=QString("DELETE FROM tbl_setting;");
    Singleton_db *dbInstance=Singleton_db::getInstance();
    int res = dbInstance->insertDeleteUpdate(deleteSQL);
    if(SQLITE_OK!=res)
    {
        return -1;
    }
    //删完再加
    QString settingAdd=QString("INSERT INTO tbl_setting(video_path,photo_path,cap_interval,camera_name) \
            VALUES('%1','%2',%3,'%4');").arg(video_path,photo_path).arg(cap_interval).arg(camera_name);
    res= dbInstance->insertDeleteUpdate(settingAdd);
    return 0;
}

int SettingModel::selectCameraName(char **&qres, int &row, int &col)
{
    QString selectCameraNameSQL=QString("SELECT camera_name FROM tbl_setting;");
    Singleton_db *dbInstance=Singleton_db::getInstance();
    int res=dbInstance->getData(selectCameraNameSQL,qres,row,col);
    if(SQLITE_OK==res)
    {
        if(row>0)       //设置表中存在数据
        {
            return 0;
        }
        else {
            return 1;   //设置表中没有数据
        }
    }
    else {
        return -1;      //SQL执行失败
    }
}

int SettingModel::selectVideoPath(char **&qres, int &row, int &col)
{
    QString selectVideoPathSQL=QString("SELECT video_path FROM tbl_setting;");
    Singleton_db *dbInstance=Singleton_db::getInstance();
    int res=dbInstance->getData(selectVideoPathSQL,qres,row,col);
    if(SQLITE_OK==res)
    {
        if(row>0)       //设置表中存在数据
        {
            return 0;
        }
        else {
            return 1;   //设置表中没有数据
        }
    }
    else {
        return -1;      //SQL执行失败
    }
}

int SettingModel::selectPhotoPath(char **&qres, int &row, int &col)
{
    QString selectPhotoPathSQL=QString("SELECT photo_path FROM tbl_setting;");
    Singleton_db *dbInstance=Singleton_db::getInstance();
    int res=dbInstance->getData(selectPhotoPathSQL,qres,row,col);
    if(SQLITE_OK==res)
    {
        if(row>0)       //设置表中存在数据
        {
            return 0;
        }
        else {
            return 1;   //设置表中没有数据
        }
    }
    else {
        return -1;      //SQL执行失败
    }
}

int SettingModel::selectCaptureInterval(char **&qres, int &row, int &col)
{
    QString selectCapInterval=QString("SELECT cap_interval FROM tbl_setting;");
    Singleton_db *dbInstance=Singleton_db::getInstance();
    int res=dbInstance->getData(selectCapInterval,qres,row,col);
    if(SQLITE_OK==res)
    {
        if(row>0)       //设置表中存在数据
        {
            return 0;
        }
        else {
            return 1;   //设置表中没有数据
        }
    }
    else {
        return -1;      //SQL执行失败
    }
}

SettingModel::SettingModel()
{

}
