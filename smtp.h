#ifndef SMTP_H
#define SMTP_H

#include "stdafx.h"
#include "dialog_login.h"


namespace SMTPClass{
    class SMTP;
}

class SMTP: public QObject
{
    Q_OBJECT
public:
    explicit SMTP(QObject *parent = 0);
    qint32 setUserName(QString USERNAME); //设置用户名，返回用户名长度
    qint32 setPassWord(QString PASSWORD); //设置密码，返回密码字符串长度
    qint32 setHost(QString Host); //设置邮件服务器地址
    void setPort(quint16 Port); //设置邮件服务器端口号
    bool login(); //登陆smtp服务器

    ~SMTP();
private:
    QString USERNAME;
    QString PASSWORD;
    QString Host; //主机地址
    quint16 Port; //主机端口
    QTcpSocket *sock;
    QString str; //读取数据缓冲区
private slots:
    void readMesg();
};

#endif // SMTP_H