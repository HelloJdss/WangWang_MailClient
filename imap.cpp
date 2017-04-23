#include "imap.h"
class clientwindow;

#include <QDebug>
iMap::iMap(QObject* parent)
    : QObject(parent)
{
    USERNAME = "Admin";
    PASSWORD = "123456";
    Host = "127.0.0.1"; //初始化为本地ip
    Port = 5678;
    sock = new QTcpSocket(); //建立一个Tcp sock
}

qint32 iMap::setUserName(QString USERNAME)
{
    this->USERNAME = USERNAME;
    return this->USERNAME.size();
}

qint32 iMap::setPassWord(QString PASSWORD)
{
    this->PASSWORD = PASSWORD;
    return this->PASSWORD.size();
}

qint32 iMap::setServerfield(QString Serverfield)
{
    this->Serverfield = Serverfield;
    return this->Serverfield.size();
}

qint32 iMap::setHost(QString Host)
{
    this->Host = Host;
    return this->Host.size();
}

void iMap::setPort(quint16 Port) { this->Port = Port; }

bool iMap::login()
{

    QHostInfo info = QHostInfo::fromName(Host);
    if (0 == info.addresses().size()) {
        QMessageBox::critical(0, QObject::tr("错误！"), ("服务器域名错误！"),
            QMessageBox::Yes); //警告对话框
        return false;
    }
    qDebug() << info.addresses();
    qDebug() << Port;
    //连接所有IP列表

    for (int i = 0; i < info.addresses().size(); i++) {
        this->sock->connectToHost(QHostAddress(info.addresses().at(i)), Port);
        if (!this->recvMsg())
            break; //接收数据
        if ("* OK" == buf.left(4)) {
            //      connect(sock, SIGNAL(readyRead()), this,
            //              SLOT(readMesg())); //连接槽函数，使得自动接受数据

            this->sendMsg("A001 LOGIN " + this->USERNAME + " " + this->PASSWORD + "\r\n");
            if (!this->recvMsg())
                break;
            return true;
        }
        sock->abort(); //中断本次连接
    }
    //连接服务器失败
    QMessageBox::warning(0, QObject::tr("警告！"), ("连接服务器失败！"),
        QMessageBox::Yes); //警告对话框
    return false;
}

void iMap::sendMsg(QString msg)
{
    sock->write(msg.toLatin1(), msg.toLatin1().size());
    this->updateLog("[C]: " + msg);
}

bool iMap::recvMsg()
{
    QString s;
    if (sock->waitForReadyRead(10000)) { //等待最多10秒-
        buf.clear();
        while (sock->canReadLine())
            buf.append(sock->readLine());
        s = "[S]: ";
        this->updateLog(s + buf);
        return true;
    } else {
        s = "Wait Timeout!";
        this->updateLog(s);
        return false;
    }
}

void iMap::updateLog(QString msg)
{
    QDateTime time = QDateTime::currentDateTime();
    QString text;
    text = time.toString("yyyy-MM-dd hh:mm:ss") + ": " + msg;
    log << text;
}

const QStringList& iMap::getLog()
{
    for (int i = 0; i < log.size(); i++) {
        qDebug() << log.at(i);
    }
    return this->log;
}

QStringList& iMap::getInboxMailList(bool &OK)
{
    this->sendMsg("A002 examine INBOX\r\n");
    if (this->recvMsg()) {
        QStringList A002_list;
        A002_list = buf.split("\r\n");
        qDebug() << A002_list;
        qDebug() << A002_list.size();
        if (8 != A002_list.size()){
            OK=false;
            return  this->InboxList;
        }
        //成功打开INBOX
        bool OK1;
        qint32 exists = A002_list.at(0).split(" ").at(1).toInt(&OK1, 10);
        qDebug() << OK1;
        if (OK1) {
            for (int i = 1; i <= exists; i++) {
                this->sendMsg("A003 fetch " + QString::number(i, 10) + " BODY[header]\r\n");
                if (this->recvMsg()) {
                    qDebug()<<buf;
                    this->InboxList << buf;
                } else {
                    qDebug() << this->InboxList;
                    OK= false;
                    return this->InboxList;
                }
            }
            OK= true;
        }
    }
    else OK= false;
    return this->InboxList;
}



void iMap::readMesg()
{
    buf.append(sock->readAll());
    qDebug() << log;
}

iMap::~iMap() { delete sock; }
