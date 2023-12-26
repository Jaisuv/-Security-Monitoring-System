#include "verification.h"
#include <QTime>        //
#include <QtGlobal>     //生成随机数的两个函数qsrand() 、qrand()
#include <QChar>
#include <QPainter>


Verification::Verification(QWidget *parent): QPushButton(parent)
{
    this->m_timer= new QTimer(this);
    //随机数种子
    qsrand(QTime::currentTime().second()*1000+QTime::currentTime().msec());
    this->vcode=this->generateRandNum();//生成4位验证码
//    this->vcode=QString("7K7K");
    this->vcolor=this->getColor();//产生颜色
    connect(this->m_timer,SIGNAL(timeout()),this,SLOT(TimeoutSlot()));//时间一到就变颜色
    m_timer->start(200);//200微秒变一次色
    connect(this,SIGNAL(clicked()),this,SLOT(generateRandNum()));//图片被点击则产生新的验证码
}

Qt::GlobalColor *Verification::getColor()
{
    static Qt::GlobalColor colors[4]; //定义填充样式的颜色
    for(int i=0;i<4;i++)
    {
        colors[i]=static_cast<Qt::GlobalColor>((qrand()%13)+4); //GlobalColor下标4-17是彩色
    }
    return colors;
}

void Verification::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(0, 0, 100, 36, Qt::white);//背景设为白色
    painter.setFont(QFont("Microsoft YaHei",16));

    //绘制噪点
     for(int i = 0; i < 100; i++){
         painter.setPen(vcolor[i % 4]);
         painter.drawPoint((qrand() % 100), (qrand() % 40));
     }
     //绘制验证码
     for(int i = 0; i < 4; i++){
         painter.setPen(vcolor[i]);
         painter.drawText(1+25 * i, 5, 18, 18, Qt::AlignCenter, QString(vcode[i]));
     }
}

QString Verification::generateRandNum()
{
    QString temp="";
    int c=0;
    int type=0;

    for(int i=0;i<4;i++) //4位验证码，循环4次
    {
        type=qrand()%3;
        if(type==0)//生成数字
        {
            c=qrand()%10;//生成一个0-9的数字
            temp+=QString::number(c);
        }
        else if (type==1) //大写字母
        {
            char ch='A';
            temp+=static_cast<QChar>(ch+qrand()%26);
        }
        else if (type==2) //小写字母
        {
            char ch='a';
            temp+=static_cast<QChar>(ch+qrand()%26);
        }
    }
    this->vcode=temp;
    return temp;
}

void Verification::TimeoutSlot()
{
    vcolor=this->getColor();
    update();
}
