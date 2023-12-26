#ifndef LOGINWIN_H
#define LOGINWIN_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QList>
#include "tools/verification.h"
#include "registwin.h" //登录为主，注册界面成为登录的成员，防止头文件互相包含
#include <QPaintEvent>
#include <QIcon>
#include "controller/usercontroller.h"
#include "controller/logcontroller.h"

class LoginWin : public QWidget
{
    Q_OBJECT
public:
    explicit LoginWin(QWidget *parent = nullptr);

    /**加载样式
     * @brief loadQss
     */
    void loadQss();

    /**窗口控件初始化
     * @brief initControl
     */
    void initControl();

    //加载连接关系
    void initConnect();
private:
    QLabel *title,*accountLab,*pwdLab,*codeLab;
    QLineEdit *accountEdt,*pwdEdt,*codeEdt;
    QPushButton *loginBtn,*quitBtn,*toRegistBtn,*pwdChangeBtn;
    Verification *veriBtn; //图形验证码
    QString codenum;//验证码的值
    QIcon icon1,icon2;
    RegistWin *regWin; //跳转到的注册界面
    volatile bool isVisible;
protected:
//    void paintEvent(QPaintEvent *event);
//    void keyPressEvent(QKeyEvent *event);
signals:
    void LogInSuccess(QString);
public slots:
    //获取四位数字的验证码
    void getCode();
    //登录
    void doLogin();
    //点击取消
    void doQuit();
    //去注册界面
    void toRegistWin();
    //注册时取消，返回该登录界面
    void showSelf();
    //注册完携带账号跳回登录界面
    void Reg2Log(QString newAccount);
    //小眼睛明密文
    void changeEchoMode();
};

#endif // LOGINWIN_H
