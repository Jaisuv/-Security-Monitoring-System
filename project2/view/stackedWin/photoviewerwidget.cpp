//照片列表的设计
#include "photoviewerwidget.h"
#include <QMessageBox>

PhotoViewerWidget::PhotoViewerWidget(QWidget *parent) : QWidget(parent)
{
    this->moreFactor=0;//懒加载偏移量
    this->isLoading=false;//是否正在加载的标志位
    this->initCtrl();
    this->setStyleSheet("background:#2e2f33");
    this->initConnect();
}
/************************************************************
* 函数名称：init
* 函数功能：初始化控件,该界面作为回放模式下，照片查看堆栈窗口的widget部件
* 函数简介: 整体布局 entireLayout是分左右两块的水平布局，左边照片列表，右边照片信息
* 参   数:
* 返 回 值:
**************************************************************/
void PhotoViewerWidget::initCtrl()
{
    this->entireLayout=new QHBoxLayout(this);
    this->leftWidget=new QWidget(this);//左半边的部件
    //初始的9张照片数据，存入容器
    this->photoList=PhotoController::getInstance()->getInitPhotoList(0);
    //照片墙部件
    this->photoWall=new QListWidget(this);
    this->photoWall->setViewMode(QListWidget::IconMode);//上图下文
    this->photoWall->setIconSize(QSize(270,240));
    this->photoWall->setGridSize(QSize(270,240));//设置每个单元格的大小
    this->photoWall->setResizeMode(QListView::Adjust);//大小自适应
    this->photoWall->setMovement(QListView::Static);//列表的每一项不可移动
    this->photoWall->setFlow(QListView::LeftToRight);//从左到右
    this->photoWall->setSpacing(5);
    //加载数据
    for (int i=0;i<this->photoList.size();i++)
    {
        QString Path=this->photoList.at(i)->getPhoto_path()+"/";
        //路径拼接文件名就能访问到照片，""空字符串让他不显示文字
        QListWidgetItem *item=new QListWidgetItem(QIcon(Path+photoList.at(i)->getPhoto_name()),"");
        item->setData(Qt::UserRole,this->photoList.at(i)->getPhoto_id());
        item->setTextAlignment(Qt::AlignVCenter);//设置每个item居中对齐
        this->photoWall->addItem(item);
    }
//===============================照片墙的样式==========================================
    this->photoWall->setStyleSheet("QListWidget{padding-top:30px;border:3px dashed gray;padding-left:15px}"
                                   "QListWidget::item{border:1px solid white;height:155px}");


    this->verticalScrollBar = this->photoWall->verticalScrollBar();//将左边照片墙部件的滚动条地址传给整个堆栈窗口的成员
    this->photoLayout=new QVBoxLayout;
    this->photoLayout->setMargin(10);
    this->photoLayout->addWidget(this->photoWall);
    this->leftWidget->setLayout(this->photoLayout);
//===============================左右分界线===================================
    this->rightWidget=new QWidget(this);
    this->rightWidget->setObjectName("rightWidget");
    this->rightWidget->setStyleSheet("#rightWidget{background:#3e3f43;border:2px solid gray}\
                                       QLabel{background:#3e3f43;color:#e6e6e6;font-size:20px;}");
    this->rightLayout=new QVBoxLayout(this->rightWidget);

    this->searchNote=new QLabel("选择查找的日期",this);
    this->dateEdt=new QDateEdit(this);
    this->dateEdt->setStyleSheet("height:25px;font-weight:bold;background:white;");
    this->dateEdt->setDateTime(QDateTime::currentDateTime());
    this->dateEdt->setCalendarPopup(true);

    this->photoName=new QLabel("照片路径名称：",this->rightWidget);
    this->photoNameDetail=new QLabel(this->rightWidget);
    this->photoNameDetail->setWordWrap(1);
    this->photoSize=new QLabel("照片文件大小：",this->rightWidget);
    this->photoSizeDetail=new QLabel(this->rightWidget);
    this->photoSizeDetail->setWordWrap(true);
    this->photoWH=new QLabel("照片宽高尺寸：",this->rightWidget);
    this->photoWHDetail=new QLabel(this->rightWidget);
    this->photoWHDetail->setWordWrap(1);
//    this->moreBtn=new QPushButton(tr("加载更多"),this);
//    this->moreBtn->setFixedSize(100,30);
    this->rightLayout->addWidget(this->searchNote);
    this->rightLayout->addWidget(this->dateEdt);
    this->rightLayout->addWidget(this->photoName);
    this->rightLayout->addWidget(this->photoNameDetail);
    this->rightLayout->addStretch(1);
    this->rightLayout->addWidget(this->photoSize);
    this->rightLayout->addWidget(this->photoSizeDetail);
    this->rightLayout->addStretch(1);
    this->rightLayout->addWidget(this->photoWH);
    this->rightLayout->addWidget(this->photoWHDetail);
    this->rightLayout->addStretch(1);
//    this->rightLayout->addWidget(this->moreBtn);
    this->rightLayout->setMargin(20);
    this->rightLayout->setSpacing(10);
    this->rightWidget->setLayout(this->rightLayout);

    this->entireLayout->addWidget(this->leftWidget,4);
    this->entireLayout->addWidget(this->rightWidget,1);
    this->entireLayout->setMargin(0);
    this->entireLayout->setSpacing(0);
    this->setLayout(this->entireLayout);
}

void PhotoViewerWidget::initConnect()
{
    connect(this->photoWall,SIGNAL(itemClicked(QListWidgetItem *)),this,SLOT(showPhotoInfo(QListWidgetItem *)));
    connect(this->photoWall,SIGNAL(itemDoubleClicked(QListWidgetItem *)),this,SLOT(enlargeImg(QListWidgetItem *)));
    connect(this->dateEdt,SIGNAL(dateChanged(QDate)),this,SLOT(initByDate(QDate)));
}

void PhotoViewerWidget::initData()
{
    this->moreFactor=0;
    this->photoList=PhotoController::getInstance()->getInitPhotoList(0);
    if(this->photoList.size()==0)
    {
        QMessageBox::warning(nullptr,"查询提醒",tr("<font color='red' size='5'>没有数据</font>"));
        return;
    }
    this->photoWall->clear();
    //加载数据
    for (int i=0;i<this->photoList.size();i++)
    {
        QString Path=this->photoList.at(i)->getPhoto_path()+"/";
        //路径拼接文件名就能访问到照片，""空字符串让他不显示文字
        QListWidgetItem *item=new QListWidgetItem(QIcon(Path+photoList.at(i)->getPhoto_name()),"");
        item->setData(Qt::UserRole,this->photoList.at(i)->getPhoto_id());
        item->setTextAlignment(Qt::AlignVCenter);//设置每个item居中对齐
        this->photoWall->addItem(item);
    }
}

//使用懒加载，offsetFactor要从0开始。
void PhotoViewerWidget::wheelEvent(QWheelEvent *event)
{
    if (event->angleDelta().y() > 0) {
        // Scroll up
        QWidget::wheelEvent(event);
    } else {
        // Scroll down
        if (!isLoading && this->verticalScrollBar->value() == verticalScrollBar->maximum())
        {
            isLoading = true;
            QList<MyPhoto*> tempPhotoList = PhotoController::getInstance()->getMorePhoto(this->moreFactor);
            if (!tempPhotoList.isEmpty()) { // Check if the list is not empty
                for (int i = 0; i < tempPhotoList.size(); ++i) {
                    QString Path = tempPhotoList.at(i)->getPhoto_path() + "/";
                    QListWidgetItem *item = new QListWidgetItem(QIcon(Path + tempPhotoList.at(i)->getPhoto_name()), "");
                    item->setData(Qt::UserRole,tempPhotoList.at(i)->getPhoto_id());
                    item->setSizeHint(QSize(280,230));//设置每个item的大小
                    item->setTextAlignment(Qt::AlignVCenter);//设置每个item居中对齐
                    this->photoWall->addItem(item);
                }
                this->moreFactor++;
            } else {
                // No more photos to load, show a message
                QMessageBox::information(nullptr, "加载提醒", tr("<font color='red' size='5'>没有更多照片可加载</font>"));
            }
            isLoading = false;
        }
        QWidget::wheelEvent(event);
    }
}

void PhotoViewerWidget::showPhotoInfo(QListWidgetItem *photoClicked)
{
    //照片信息准备
    int photoId=photoClicked->data(Qt::UserRole).toInt();//获取被单击的图片的ID
    QString photoPath=PhotoController::getInstance()->getPhotoPathById(photoId);
    QString photoName=PhotoController::getInstance()->getPhotoNameById(photoId);
    QString photoCreatedTime=PhotoController::getInstance()->getPhotoTimeById(photoId);
    QString finalPath=photoPath+"/"+photoName;
    this->photoNameDetail->setText(finalPath);
    QPixmap thePix(finalPath);
    int width=thePix.width();
    int height=thePix.height();
    this->photoWHDetail->setText(tr("%1*%2").arg(width).arg(height));
    QFile imageFile(finalPath);
    if (imageFile.open(QIODevice::ReadOnly)) {
        qint64 fileSize = imageFile.size(); // 字节大小
        qint64 temp=fileSize;
        double fileSizeKB= static_cast<double>(fileSize)/1024.0;
        QString formattedSize = QString::asprintf("%.1f KB", fileSizeKB);
        this->photoSizeDetail->setText(formattedSize+tr("\n%1字节").arg(temp));
        imageFile.close();
        qDebug() << "Image file size:" << fileSize << "bytes";
    } else {
        qDebug() << "Failed to open image file";
    }

}

void PhotoViewerWidget::enlargeImg(QListWidgetItem *item)
{
    QRect rect=this->geometry();//获取当前窗口坐标与大小
    //声明为类成员会在该窗口
    this->curPhotoWin=new imagePopWin(item,QRect(rect.x()+rect.width()/2,rect.y()+rect.height()*1/2-20,rect.width()/3*2,rect.height()/3*2));
    curPhotoWin->show();
}

void PhotoViewerWidget::initByDate(QDate date)
{
    this->moreFactor=0;
    QString photoDate =date.toString("yyyyMMdd");//选中日期字符串
    this->photoList=PhotoController::getInstance()->getPhotoListByDate(this->moreFactor,photoDate);//获取那天最后的4条记录
    if(this->photoList.size()==0)
    {
        QMessageBox::warning(nullptr,"查询提醒",tr("<font color='red' size='5'>没有数据</font>"));
        return;
    }
    this->photoWall->clear();
    for(int i=0;i<this->photoList.size();i++)
    {
        QString Path=photoList.at(i)->getPhoto_path()+'/';
        QListWidgetItem *item=new QListWidgetItem(QIcon(Path+photoList[i]->getPhoto_name()),
                                                  "");
        item->setData(Qt::UserRole,this->photoList.at(i)->getPhoto_id());
        this->photoWall->addItem(item);
    }
}



