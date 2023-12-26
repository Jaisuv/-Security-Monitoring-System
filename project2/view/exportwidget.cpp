#include "exportwidget.h"
#include <QMessageBox>

ExportWidget::ExportWidget(QString fileH264)
{
    this->initCtrl();
    this->h264File = fileH264;
}

void ExportWidget::doSelect()
{
    QString exportPth=QFileDialog::getExistingDirectory(nullptr,tr("选择导出目录"),"../data/export");
    //若目录路径不为空
    if(!exportPth.isEmpty())
    {
        this->pathEdt->setText(exportPth);
    }
    else {
        QMessageBox::critical(this,tr("导出路径选择"),tr("<font color='red'>所选路径为空</font>"));
    }
}

void ExportWidget::doOK()
{
    //表单验证
    if(this->pathEdt->text().isEmpty())
    {
        QMessageBox::warning(nullptr,"表单提醒",tr("<font color='red' size='5'>所选路径为空！</font>"));
        return;
    }
    if(this->nameEdt->text().isEmpty())
    {
        QMessageBox::warning(nullptr,"表单提醒",tr("<font color='red' size='5'>文件名为空！</font>"));
        return;
    }
    this->exportThread=new ExportThread(this->h264File);
    connect(this->exportThread,SIGNAL(ExportSuccess()),this,SLOT(taskDone()));
    //生成输出的文件名与格式
    QString videoPath=this->pathEdt->text()+"/";
    QString videoName=this->nameEdt->text();
    QString format="."+this->formatBox->currentText();
    QString finalName=videoPath+videoName+format;
    this->exportThread->setSavePath(finalName);
//=============转码参数设置=====================
    this->exportThread->Exportsetting();
    this->exportThread->start();
}

void ExportWidget::doCancel()
{
    //这样子不会出错
    this->close();
}

void ExportWidget::taskDone()
{
    if(this->exportThread!=nullptr)
    {
        disconnect(this->exportThread,SIGNAL(ExportSuccess()),this,SLOT(taskDone()));
        delete this->exportThread;
        this->exportThread=nullptr;
    }
    QMessageBox::information(nullptr,"导出提示",tr("<font color='blue' size='6'>导出成功!</font>"));
    this->close();
}


void ExportWidget::initCtrl()
{
    this->setFixedSize(400,300);

    this->exPath=new QLabel("选择文件夹:",this);
    this->exPath->move(20,50);
    this->exPath->setStyleSheet("color:black;font-size:20px;font-weight:700");

    this->exName=new QLabel("保存文件名:",this);
    this->exName->move(20,140);
    this->exName->setStyleSheet("color:black;font-size:20px;font-weight:700");

    this->exFormat=new QLabel("导出格式：",this);
    this->exFormat->move(20,230);
    this->exFormat->setStyleSheet("color:black;font-size:20px;font-weight:700");

    this->pathEdt=new QLineEdit(this);
    this->pathEdt->move(150,45);
    this->pathEdt->setReadOnly(1);
    this->pathEdt->setFixedSize(200,30);

    this->nameEdt=new QLineEdit(this);
    this->nameEdt->move(150,135);
    this->nameEdt->setFixedSize(200,30);

    this->formatBox=new QComboBox(this);
    this->formatBox->move(150,225);
    this->formatBox->setFixedSize(200,30);
    this->formatBox->addItem("mp4");
    this->formatBox->addItem("flv");
    this->formatBox->addItem("wmv");

    this->pathBtn=new QPushButton("...",this);
    this->pathBtn->setFixedSize(30,30);
    this->pathBtn->move(360,45);
    connect(this->pathBtn,SIGNAL(clicked()),this,SLOT(doSelect()));

    this->okBtn=new QPushButton("确定",this);
    this->okBtn->move(100,260);
    this->okBtn->setFixedSize(50,30);
    connect(this->okBtn,SIGNAL(clicked()),this,SLOT(doOK()));

    this->cancelBtn=new QPushButton("取消",this);
    this->cancelBtn->move(200,260);
    this->cancelBtn->setFixedSize(50,30);
    connect(this->cancelBtn,SIGNAL(clicked()),this,SLOT(doCancel()));
}
