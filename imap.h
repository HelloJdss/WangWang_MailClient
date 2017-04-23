#ifndef IMAPDATA_H
#define IMAPDATA_H

#include "stdafx.h"
class Dialog_login;

namespace iMapClass {
class iMap;
}

class iMap : public QObject {
    Q_OBJECT
public:
    explicit iMap(QObject* parent = 0);
    qint32 setUserName(QString USERNAME); //设置用户名，返回用户名长度
    qint32 setPassWord(QString PASSWORD); //设置密码，返回密码字符串长度
    qint32 setServerfield(QString Serverfield);
    qint32 setHost(QString Host); //设置邮件服务器地址
    void setPort(quint16 Port); //设置邮件服务器端口号
    bool login(); //登陆imap服务器
    void sendMsg(QString msg); //向服务器发送信息
    bool recvMsg(); //获取服务器信息并更新缓冲区
    void updateLog(QString msg); //更新日志
    const QStringList& getLog(); //获取日志信息
    QStringList& getInboxMailList(bool &OK); //获取收件箱邮件列表
    ~iMap();

private:
    QString USERNAME;
    QString PASSWORD;
    QString Serverfield; //服务器域
    QString Host; //主机地址
    quint16 Port; //主机端口
    QTcpSocket* sock;
    QString buf; //读取数据缓冲区
    QStringList log; //系统接收日志
    QStringList InboxList; //收件箱列表
private slots:
    void readMesg();
};

#endif // IMAPDATA_H
