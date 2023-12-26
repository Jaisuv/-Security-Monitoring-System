#include "myphoto.h"

MyPhoto::MyPhoto(int photoId,QString photoName,QString photoPath,QString createdTime)
{
    this->photo_id=photoId;
    this->photo_name=photoName;
    this->photo_path=photoPath;
    this->created_time=createdTime;
}

int MyPhoto::getPhoto_id() const
{
    return photo_id;
}

void MyPhoto::setPhoto_id(int value)
{
    photo_id = value;
}

QString MyPhoto::getPhoto_name() const
{
    return photo_name;
}

void MyPhoto::setPhoto_name(const QString &value)
{
    photo_name = value;
}

QString MyPhoto::getPhoto_path() const
{
    return photo_path;
}

void MyPhoto::setPhoto_path(const QString &value)
{
    photo_path = value;
}

QString MyPhoto::getCreated_time() const
{
    return created_time;
}

void MyPhoto::setCreated_time(const QString &value)
{
    created_time = value;
}


