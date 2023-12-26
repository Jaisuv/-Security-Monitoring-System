#ifndef PHOTOMODEL_H
#define PHOTOMODEL_H
#include "singleton_db.h"
#include <QString>
#include <QDebug>

class PhotoModel
{
public:
    static PhotoModel *getInstance();
    int addPhoto(QString photo_name,QString photo_path,QString created_time);
    int getLatestPhoto(int offset,char **&qres,int &row,int &col);
/************************************************************
* 函数名称：
* 函数功能：懒加载更多的数据
* 参   数:
* 返 回 值:
**************************************************************/
    int getMorePhoto(int offsetFacator,char **&qres,int &row,int &col);
/************************************************************
* 函数名称：
* 函数功能：根据id获取照片名称
* 参   数:
* 返 回 值:
**************************************************************/
    int getPhotoNameById(char **&qres,int &row,int &col,int id);
    int getPhotoPathById(char **&qres,int &row,int &col,int id);
    int getPhotoTimeById(char **&qres,int &row,int &col,int id);
/************************************************************
* 函数名称：
* 函数功能：根据日期搜索照片
* 参   数:
* 返 回 值:
**************************************************************/
    int getPhotoByDate(QString date,int offset,char **&qres,int &row,int &col);
private:
    PhotoModel();
    static PhotoModel* photoModel_ins;
};

#endif // PHOTOMODEL_H
