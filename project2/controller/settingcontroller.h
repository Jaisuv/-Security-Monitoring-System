#ifndef SETTINGCONTROLLER_H
#define SETTINGCONTROLLER_H
#include <QString>
#include "model/settingmodel.h"

class SettingController
{
public:
    static SettingController *getInstance();
    //判断数据库中是否有设置信息，返回0说明存在数据，返回1说明没有数据
    int getSetting();
    int updateSetting(QString video_path,QString photo_path,int cap_interval,QString camera_name);
    QString getCameraNameInDB();
    QString getVideoPathInDB();
    QString getPhotoPathInDB();
    int getCapInterval();
private:
    SettingController();
    static SettingController *settingCtrl_ins;
};

#endif // SETTINGCONTROLLER_H
