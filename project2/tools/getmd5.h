#ifndef GETMD5_H
#define GETMD5_H
#include <QCryptographicHash>   //用于生成密码散列
#include <QString>

class GetMd5
{
public:
    //使用静态成员无需实例化即可使用
    //将一段QString字符串密码进行MD5加密
    static QString str2MD5(const QString &passwd);
};

#endif // GETMD5_H
