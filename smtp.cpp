#include "smtp.h"

#include <QDebug>
SMTP::SMTP(QObject* parent)
    : QObject(parent)
{
    USERNAME = "18040506495@163.com";
    PASSWORD = "wz19965050318";
    Host = "smtp.163.com"; //初始化为本地ip
    Port = 25;
    sock = new QTcpSocket(); //建立一个Tcp sock
}

void SMTP::readMesg()
{
    //str.append(sock->readAll());
    //qDebug()<<str;
}

void SMTP::WriteAndWait(QString &s,bool wait)
{ //write and wait for result
    qDebug() << "command: " << s;
    s += "\r\n";
    sock->write(s.toLatin1(), s.toLatin1().size());
    //qDebug() << sock->state();
    if(wait)return;
    sock->waitForReadyRead(30000); //等待最多30秒
    //qDebug() << sock->bytesAvailable();
    str = sock->readAll();
    qDebug() << "reply: " << str;
}

SMTP::~SMTP()
{
    delete sock;
}

bool SMTP::Connect(QString host, quint16 port)
{
    Host = host;
    Port = port;
    QHostInfo info = QHostInfo::fromName(Host);
    if (0 == info.addresses().size()) {
        QMessageBox::critical(0, QObject::tr("错误！"), ("服务器域名错误！"), QMessageBox::Yes); //警告对话框
        return false;
    }
    qDebug() << "SMTP" << info.addresses();
    qDebug() << "SMTP" << Port;
    //连接所有IP列表
    //QString str;
    for (int i = 0; i < info.addresses().size(); i++) {
        this->sock->connectToHost(QHostAddress(info.addresses().at(i)), Port);
        qDebug() << sock->state();
        sock->waitForReadyRead(30000); //等待最多30秒
        qDebug() << sock->bytesAvailable();
        str = sock->readAll();
        qDebug() << str;
        if ("220" == str.left(3)) {
            //connect(sock,SIGNAL(readyRead()),this,SLOT(readMesg()));//连接槽函数，使得自动接受数据
            return true;
        }
        sock->abort(); //中断本次连接
    }
    //连接服务器失败
    QMessageBox::warning(0, QObject::tr("警告！"), ("连接服务器失败！"), QMessageBox::Yes); //警告对话框
    return false;
}

bool SMTP::Login(QString username, QString password)
{
    USERNAME = username;
    PASSWORD = password;
    qDebug() << "USERNAME: " << USERNAME;
    connect(sock, SIGNAL(readyRead()), this, SLOT(readMesg())); //连接槽函数，使得自动接受数据
    QString s = "HELO SMTP.163.com";
    WriteAndWait(s);
    if ("250" == str.left(3)) {
        s = "AUTH LOGIN";
        WriteAndWait(s);
        if ("334" == str.left(3)) {
            s = USERNAME.toLatin1().toBase64();
            WriteAndWait(s);
            if ("334" == str.left(3)) {
                s = PASSWORD.toLatin1().toBase64();
                WriteAndWait(s);
                if ("235" == str.left(3)) {
                    qDebug() << "LOGIN SUCCESSFULLY.";
                        qDebug() << "USERNAME: " << USERNAME;
                    return true;
                }
            }
        }
    }
    qDebug() << "LOGIN FAILED.";
    return false;
}

bool SMTP::SendMail(QString subject, QString recipient,QString content) {
    //wait to be modified
    QString s = "MAIL FROM: <" + USERNAME + "@163.com" + ">",ans;
    WriteAndWait(s);
    if ("250" == str.left(3)) {
        s = "RCPT TO: <" + recipient + ">";
        WriteAndWait(s);
        if ("250" == str.left(3)) {
            s = "DATA";
            WriteAndWait(s);
            if ("354" == str.left(3)) {      
                s = "from:" + USERNAME + "@163.com";
                WriteAndWait(s,true); 
                s = "to:" + recipient;
                WriteAndWait(s,true);  
                s = "Subject:" + subject;
                WriteAndWait(s,true);                                   
                WriteAndWait(content,true);
                s = ".";
                WriteAndWait(s);
                if ("250" == str.left(3)) {
                    qDebug() << "SendMail SUCCESSFULLY!";
                }
            }   
        }
    }
}

