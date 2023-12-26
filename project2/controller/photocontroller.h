#ifndef PHOTOCONTROLLER_H
#define PHOTOCONTROLLER_H
#include <QString>
#include "model/photomodel.h"
#include <QList>
#include "MyClass/myphoto.h"

class PhotoController
{
public:
    static PhotoController* getInstance();

/************************************************************
* 函数名称：
* 函数功能：往数据库中增加照片信息
* 参   数:
* 返 回 值:
**************************************************************/
    int addPhoto(QString photo_name,QString photo_path,QString created_time);
/************************************************************
* 函数名称：
* 函数功能：获取9张照片
* 参   数:
* 返 回 值:
**************************************************************/
    QList<MyPhoto *> getInitPhotoList(int start);
/************************************************************
* 函数名称：
* 函数功能：懒加载时候调用的数据库操作
* 参   数:
* 返 回 值:
**************************************************************/
    QList<MyPhoto *> getMorePhoto(int offFactor);
/************************************************************
* 函数名称：
* 函数功能：根据id获取照片信息
* 参   数:
* 返 回 值:
**************************************************************/
    QString getPhotoPathById(int id);//获取照片路径
    QString getPhotoNameById(int id);//获取照片名称
    QString getPhotoTimeById(int id);//获取生成照片时间
/************************************************************
* 函数名称：
* 函数功能：根据日期查询照片
* 参   数:
* 返 回 值:
**************************************************************/
    QList<MyPhoto *> getPhotoListByDate(int start,QString date);
private:
    PhotoController();
    static PhotoController* photoCtrl_ins;
};

#endif // PHOTOCONTROLLER_H
