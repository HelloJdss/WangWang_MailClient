#include "imap.h"

#include <QDebug>
iMap::iMap(QObject *parent) :
    QObject(parent)
{
    USERNAME="Admin";
    PASSWORD="123456";
    Host="127.0.0.1"; //初始化为本地ip
    Port=5678;
    sock=new QTcpSocket(); //建立一个Tcp sock
}

qint32 iMap::setUserName(QString USERNAME)
{
    this->USERNAME=USERNAME;
    return this->USERNAME.size();
}

qint32 iMap::setPassWord(QString PASSWORD)
{
    this->PASSWORD=PASSWORD;
    return this->PASSWORD.size();
}

qint32 iMap::setHost(QString Host)
{
    this->Host=Host;
    return this->Host.size();
}

void iMap::setPort(quint16 Port)
{
    this->Port=Port;
}

bool iMap::login()
{
    QHostInfo info=QHostInfo::fromName(Host);
    if(0==info.addresses().size()){
        QMessageBox::critical(0,QObject::tr("错误！"),("服务器域名错误！"),QMessageBox::Yes);    //警告对话框
        return false;
    }
    qDebug()<<info.addresses();
    qDebug()<<Port;

    //连接所有IP列表
    QString str;
    for(int i=0;i<info.addresses().size();i++){
        this->sock->connectToHost(QHostAddress(info.addresses().at(i)),Port);
        qDebug()<<sock->state();
        sock->waitForReadyRead(30000); //等待最多30秒
        qDebug()<<sock->bytesAvailable();
        str=sock->readAll();

        qDebug()<<str;
        if("* OK"==str.left(4)) {
            connect(sock,SIGNAL(readyRead()),this,SLOT(readMesg()));//连接槽函数，使得自动接受数据
            return true;
        }
        sock->abort(); //中断本次连接
    }
    //连接服务器失败
    QMessageBox::warning(0,QObject::tr("警告！"),("连接服务器失败！"),QMessageBox::Yes);    //警告对话框
    return false;
}

void iMap::readMesg()
{
    str=sock->readAll();
    qDebug()<<str;
}

iMap::~iMap()
{
    delete sock;
}
