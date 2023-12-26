#ifndef MYPHOTO_H
#define MYPHOTO_H
#include <QString>

class MyPhoto
{
public:
    MyPhoto(int photoId,QString photoName,QString photoPath,QString createdTime);

    int getPhoto_id() const;
    void setPhoto_id(int value);

    QString getPhoto_name() const;
    void setPhoto_name(const QString &value);

    QString getPhoto_path() const;
    void setPhoto_path(const QString &value);

    QString getCreated_time() const;
    void setCreated_time(const QString &value);

private:
    int photo_id;
    QString photo_name;
    QString photo_path;
    QString created_time;
};

#endif // MYPHOTO_H
