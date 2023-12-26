#ifndef MYITEM_H
#define MYITEM_H
#include <QGraphicsItem>
#include <QObject>
#include <QString>
#include <QPixmap>
#include <QPainter>
#include <QWidget>

class MyItem:public QObject,public QGraphicsItem //多继承 两个父亲
{
    Q_OBJECT
public:
    MyItem(int status,QString path);

    /**返回图元位置
     * @brief boundingRect
     * @return
     */
    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);

    /**图元移动
     * @brief advance
     * @param phase
     */
    void advance(int phase);

private:
    int status; //状态 0-不动 1-从左往右 2-从右往左
    QPixmap img;    //图片
signals:
    void stopMove();
    void turnPage();
public slots:

};

#endif // MYITEM_H
