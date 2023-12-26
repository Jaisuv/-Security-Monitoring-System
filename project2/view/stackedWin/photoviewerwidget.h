//照片列表
#ifndef PHOTOVIEWERWIDGET_H
#define PHOTOVIEWERWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QList>
#include <QPixmap>
#include <QString>
#include <QWheelEvent>
#include "controller/photocontroller.h"
#include <QScrollBar>
#include <QFile>
#include "MyClass/imagepopwin.h"
#include <QDateEdit>

class PhotoViewerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PhotoViewerWidget(QWidget *parent = nullptr);
    void initCtrl();
    int moreFactor;//懒加载时候的偏移量
    void initConnect();
    void initData();
protected:
    //滚轮事件实现懒加载
    void wheelEvent(QWheelEvent *event);
private:
    QLabel *searchNote;
    QDateEdit *dateEdt;
    QHBoxLayout *entireLayout;
    QWidget *leftWidget,*rightWidget;
    QVBoxLayout *rightLayout,*photoLayout;
    QListWidget *photoWall;//9宫格滚动照片墙
    QPushButton *moreBtn;
    QLabel *photoName,*photoSize,*photoWH;//标签
    QLabel *photoNameDetail,*photoSizeDetail,*photoWHDetail;//详情
    QList<MyPhoto *> photoList;//照片类型的容器
    bool isLoading;
    QScrollBar *verticalScrollBar;
    imagePopWin *curPhotoWin;
signals:

public slots:
    void showPhotoInfo(QListWidgetItem *);
    void enlargeImg(QListWidgetItem *);
    void initByDate(QDate);
};

#endif // PHOTOVIEWERWIDGET_H
