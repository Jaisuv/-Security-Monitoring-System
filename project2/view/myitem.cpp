#include "myitem.h"
#include <QDebug>
#include <QThread>

MyItem::MyItem(int status,QString path)
{
    this->status=status;
    this->img.load(path);
}

/**返回图元所在区域
 * @brief MyItem::boundingRect
 * @return
 */
QRectF MyItem::boundingRect() const
{
    return QRect(-this->img.width()/2,-this->img.height()/2,img.width(),img.height());
}

/**绘制图元
 * @brief MyItem::paint
 * @param painter
 * @param option
 * @param widget
 */
void MyItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-this->img.width()/2,-this->img.height()/2,img.width(),img.height(),this->img);
}

void MyItem::advance(int phase)
{
    if(this->status==1)
    {
        this->setPos(mapToScene(2,0));//每次向右移动两个像素
    }
    else if (this->status==2)
    {
        this->setPos(mapToScene(-2,0));//每次向左移动两个像素
    }
    else if (this->status==0) {
        return;
    }
    if(collidingItems().count()>0)
    {
        emit stopMove();
        this->status=0;
        return;
    }
}
