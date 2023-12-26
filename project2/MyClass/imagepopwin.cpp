#include "imagepopwin.h"
#include <QEvent>
#include <QApplication>
#include <QPixmap>

imagePopWin::imagePopWin(QListWidgetItem *item, QRect rect, QWidget *parent):QWidget(parent)
{
    qApp->installEventFilter(this);//安装事件过滤器
    this->setGeometry(rect);//设置显示窗口的x、y、w、h
    this->setFixedSize(rect.width(),rect.height());//将窗口的大小定住
//    this->setWindowModality(Qt::ApplicationModal);//阻塞除当前窗体外的其他所有窗体
    this->lab=new QLabel(this);//将Icon上的图片加载在QLabel上
    lab->setFixedSize(this->width(),this->height());//将Label大小设置的和窗口一样大
    //让图片适应QLabel的大小
    lab->setPixmap(item->icon().pixmap(QSize(this->width(),this->height())).scaled(lab->width(),lab->height()));
    this->setWindowFlags(Qt::ToolTip);//同时隐藏任务栏和标题栏图标
}

/************************************************************
* 函数名称：
* 函数功能：利用事件过滤器，实现点击窗口任意位置，窗口就可以关闭
* 参   数:
* 返 回 值:
**************************************************************/
bool imagePopWin::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type()==QEvent::MouseButtonPress)
    {
        this->close();
    }
    return QWidget::eventFilter(obj,event);
}
