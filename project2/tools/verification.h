#ifndef VERIFICATION_H
#define VERIFICATION_H
#include <QPushButton>
#include <QPaintEvent>
#include <QTimer>

class Verification: public QPushButton //验证码继承自按钮
{
    Q_OBJECT
public:
    explicit Verification(QWidget *parent = nullptr);

    /**
     * @brief getColor
     * 随机挑选颜色
     * @return 返回颜色
     */
    Qt::GlobalColor* getColor();

    void paintEvent(QPaintEvent *);

    QString vcode;  //验证码的字符
    Qt::GlobalColor* vcolor;   //验证码的颜色
    QTimer *m_timer;
signals:

public slots:
    /**
     * @brief generateRanNum
     * 生成验证码
     */
    QString generateRandNum();

    /**
     * @brief TimeoutSlot
     * 如果图片被点击，就更新
     */
    void TimeoutSlot();

};

#endif // VERIFICATION_H
