#ifndef MYVIDEO_H
#define MYVIDEO_H
#include <QString>

class MyVideo
{
public:
    MyVideo(int video_id,QString video_name,QString video_path,QString created_time,QString cover_name,int frame_num);

    int getVideo_id() const;
    void setVideo_id(int value);

    QString getVideo_name() const;
    void setVideo_name(const QString &value);

    QString getVideo_path() const;
    void setVideo_path(const QString &value);

    QString getCreated_time() const;
    void setCreated_time(const QString &value);

    QString getCover_name() const;
    void setCover_name(const QString &value);

    int getFrame_num() const;
    void setFrame_num(int value);

private:
    int video_id;
    QString video_name;
    QString video_path;
    QString created_time;
    QString cover_name;
    int frame_num;
};

#endif // MYVIDEO_H
