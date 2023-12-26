#include "myvideo.h"

MyVideo::MyVideo(int video_id,QString video_name,QString video_path,QString created_time,QString cover_name,int frame_num)
{
    this->video_id=video_id;
    this->video_name=video_name;
    this->video_path=video_path;
    this->created_time=created_time;
    this->cover_name=cover_name;
    this->frame_num=frame_num;
}

int MyVideo::getVideo_id() const
{
    return video_id;
}

void MyVideo::setVideo_id(int value)
{
    video_id = value;
}

QString MyVideo::getVideo_name() const
{
    return video_name;
}

void MyVideo::setVideo_name(const QString &value)
{
    video_name = value;
}

QString MyVideo::getVideo_path() const
{
    return video_path;
}

void MyVideo::setVideo_path(const QString &value)
{
    video_path = value;
}

QString MyVideo::getCreated_time() const
{
    return created_time;
}

void MyVideo::setCreated_time(const QString &value)
{
    created_time = value;
}

QString MyVideo::getCover_name() const
{
    return cover_name;
}

void MyVideo::setCover_name(const QString &value)
{
    cover_name = value;
}

int MyVideo::getFrame_num() const
{
    return frame_num;
}

void MyVideo::setFrame_num(int value)
{
    frame_num = value;
}
