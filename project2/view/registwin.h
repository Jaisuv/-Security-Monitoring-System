#ifndef REGISTWIN_H
#define REGISTWIN_H

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QIcon>
#include "controller/usercontroller.h"

class RegistWin : public QWidget
{
    Q_OBJECT
public:
    explicit RegistWin(QWidget *parent = nullptr);
    void initCtrl();
    void loadQSS();
    void initConnect();
    void initUI();
private:
    QLabel *title,*accountLab,*nameLab,*pwdLab,*cfpwdLab;
    QLineEdit *accountEdt,*nameEdt,*pwdEdt,*cfpwdEdt;
    QPushButton *okBtn,*cancelBtn,*eye1,*eye2;
    QIcon icon1,icon2;
    volatile bool pwdVisible,cfpwdVisible;
signals:
    void RegtoLoginWin();
    void back2Login(QString);
public slots:
    void pwd_EchoMode_Sw();
    void cfpwd_EchoMode_Sw();
    void clickCancelBtn();
    void Regist();
};

#endif // REGISTWIN_H
