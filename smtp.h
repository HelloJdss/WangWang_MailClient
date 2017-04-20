#ifndef SMTP_H
#define SMTP_H

#include "stdafx.h"
#include "dialog_login.h"
#include <QByteArray>

namespace SMTPClass{
    class SMTP;
}

class SMTP: public QObject
{
    Q_OBJECT
public:
    explicit SMTP(QObject *parent = 0);
    ~SMTP();
    void WriteAndWait(QString s);
    bool Connect(QString host,quint16 port);
    bool Login(QString username,QString password);
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
