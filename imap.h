#ifndef IMAPDATA_H
#define IMAPDATA_H

#include "stdafx.h"
class Dialog_login;

namespace iMapClass{
    class iMapData;
}

class iMap: public QObject
{
    Q_OBJECT
public:
    explicit iMap(QObject *parent = 0);
    qint32 setUserName(QString USERNAME); //设置用户名，返回用户名长度
    qint32 setPassWord(QString PASSWORD); //设置密码，返回密码字符串长度
    qint32 setHost(QString Host); //设置邮件服务器地址
    void setPort(quint16 Port); //设置邮件服务器端口号
    bool login(); //登陆imap服务器

    ~iMap();
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

#endif // IMAPDATA_H
