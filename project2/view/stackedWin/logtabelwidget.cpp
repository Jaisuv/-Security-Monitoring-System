//日志界面
#include "logtabelwidget.h"

LogTabelWidget::LogTabelWidget(QWidget *parent) : QWidget(parent)
{
    this->initUI();
    this->initData();
}

void LogTabelWidget::initUI()
{
    this->entireLayout=new QHBoxLayout;
    this->leftWidget=new QWidget(this);
    this->leftWidget->setStyleSheet("background:#2e2f33;border-top:1px solid #e6e6e6; border-right:2px solid #e6e6e6;");
    this->leftLayout=new QVBoxLayout;
    this->Widgetab=new QLabel("系统日志");
    this->Widgetab->setStyleSheet("color:white;border:none;background:transparent;font-size:25px");
    this->leftLayout->addWidget(this->Widgetab);
    this->leftLayout->addStretch(1);
    this->leftWidget->setLayout(this->leftLayout);

    this->logTable=new QTableWidget(this);
    this->logTable->setStyleSheet("border:none;");
    this->logTable->setStyleSheet("border:none;");
    this->header<<tr("序号")<<tr("时间")<<tr("用户")<<tr("操作");
    this->logTable->setColumnCount(4);
    this->logTable->setHorizontalHeaderLabels(this->header);
    // 调整第一列的宽度以适应内容
    this->logTable->resizeColumnToContents(0);
    this->logTable->verticalHeader()->setVisible(false);
    this->logTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->logTable->setColumnWidth(0,150);//序号
    this->logTable->setColumnWidth(1,300);//id
    this->logTable->setColumnWidth(2,300);//日期
    this->logTable->setColumnWidth(3,350);//操作内容
    this->logTable->setRowHeight(0,100);
    this->logTable->setRowCount(20);
    this->entireLayout->addWidget(this->leftWidget,1);
    this->entireLayout->addWidget(this->logTable,9);
    this->entireLayout->setMargin(0);
    this->entireLayout->setSpacing(0);
    this->setLayout(this->entireLayout);
}

void LogTabelWidget::initData()
{
    this->logList=LogController::getInstance()->getlogList(0);
    if(this->logList.size()<=0)
    {
        QMessageBox::warning(nullptr,tr("日志查询"),tr("<font color='red' size='5'>日志查询出错</font>"));
        return;
    }
    for (int i=0;i<this->logList.size();i++)
    {
        QTableWidgetItem *item0=new QTableWidgetItem(QString::number(this->logList.at(i)->getLog_id()));
        QTableWidgetItem *item1=new QTableWidgetItem(this->logList.at(i)->getDatetime());
        QTableWidgetItem *item2=new QTableWidgetItem(this->logList.at(i)->getUser_name());
        QTableWidgetItem *item3=new QTableWidgetItem(this->logList.at(i)->getOperation());
        this->logTable->setItem(i,0,item0);
        this->logTable->setItem(i,1,item1);
        this->logTable->setItem(i,2,item2);
        this->logTable->setItem(i,3,item3);
    }
}
