#include "getmd5.h"


QString GetMd5::str2MD5(const QString &passwd)
{
    QString md5;
    QByteArray bb; //字符数组
    bb=QCryptographicHash::hash(passwd.toUtf8(),QCryptographicHash::Md5);
    md5.append(bb.toHex());
    return md5;
}
