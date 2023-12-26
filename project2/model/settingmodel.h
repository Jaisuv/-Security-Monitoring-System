#ifndef SETTINGMODEL_H
#define SETTINGMODEL_H
#include "singleton_db.h"
#include <QString>
#include <QDebug>

class SettingModel
{
public:
    static SettingModel *getInstance();
    //往设置表中新增一条记录
    int addSetting(QString video_path,QString photo_path,int cap_interval,QString camera_name);
    //查询设置表中是否有数据存在，返回0说明有数据
    int getSetting();
    int updateTbl_setting(QString video_path,QString photo_path,int cap_interval,QString camera_name);
    int selectCameraName(char **&qres,int &row,int &col);
    int selectVideoPath(char **&qres,int &row,int &col);
    int selectPhotoPath(char **&qres,int &row,int &col);
    int selectCaptureInterval(char **&qres,int &row,int &col);
private:
    SettingModel();
    static SettingModel *settingModel_ins;
};

#endif // SETTINGMODEL_H
