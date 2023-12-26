#include "photomodel.h"

PhotoModel* PhotoModel::photoModel_ins=nullptr;

PhotoModel *PhotoModel::getInstance()
{
    if(nullptr==PhotoModel::photoModel_ins)
    {
        PhotoModel::photoModel_ins=new PhotoModel;
    }
    return PhotoModel::photoModel_ins;
}

int PhotoModel::addPhoto(QString photo_name, QString photo_path, QString created_time)
{
    QString insertPhotoSQL=QString("INSERT INTO tbl_photo(photo_name,photo_path,created_time) \
                                   VALUES('%1','%2','%3');").arg(photo_name,photo_path,created_time);
    Singleton_db *dbInstance=Singleton_db::getInstance();
    int res=dbInstance->insertDeleteUpdate(insertPhotoSQL);
    if(SQLITE_OK==res)
    {
        return 0;
    }
    else {
        return -1;
    }
}

int PhotoModel::getLatestPhoto(int offset, char **&qres, int &row, int &col)
{
    QString initPhotoSelectSQL=QString("SELECT * FROM tbl_photo ORDER BY created_time DESC LIMIT 9 OFFSET %1;").arg(offset);
    Singleton_db *dbInstance=Singleton_db::getInstance();
    int res=dbInstance->getData(initPhotoSelectSQL,qres,row,col);
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

int PhotoModel::getMorePhoto(int offsetFacator,char **&qres,int &row,int &col)
{
    QString morePhotoSQL=QString("SELECT * FROM tbl_photo ORDER BY "
                                 "created_time DESC LIMIT 3 OFFSET 9+3* %1;").arg(offsetFacator);
    Singleton_db *dbInstance=Singleton_db::getInstance();
    int res=dbInstance->getData(morePhotoSQL,qres,row,col);
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

int PhotoModel::getPhotoNameById(char **&qres, int &row, int &col, int id)
{
    QString getPhotoByIdSQL=QString("SELECT photo_name FROM tbl_photo WHERE pthoto_id= %1;").arg(id);
    Singleton_db *dbInstance=Singleton_db::getInstance();
    int res=dbInstance->getData(getPhotoByIdSQL,qres,row,col);
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

int PhotoModel::getPhotoPathById(char **&qres, int &row, int &col, int id)
{
    QString getPhotoByIdSQL=QString("SELECT photo_path FROM tbl_photo WHERE pthoto_id=%1;").arg(id);
    Singleton_db *dbInstance=Singleton_db::getInstance();
    int res=dbInstance->getData(getPhotoByIdSQL,qres,row,col);
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

int PhotoModel::getPhotoTimeById(char **&qres, int &row, int &col, int id)
{
    QString getPhotoByIdSQL=QString("SELECT created_time FROM tbl_photo WHERE pthoto_id=%1;").arg(id);
    Singleton_db *dbInstance=Singleton_db::getInstance();
    int res=dbInstance->getData(getPhotoByIdSQL,qres,row,col);
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

int PhotoModel::getPhotoByDate(QString date, int offset, char **&qres, int &row, int &col)
{
    QString selectByDateSQL=QString("SELECT * FROM tbl_photo WHERE created_time LIKE '%%%1%%' ORDER BY created_time DESC LIMIT 9 OFFSET %2;").arg(date).arg(offset);
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

PhotoModel::PhotoModel()
{

}
