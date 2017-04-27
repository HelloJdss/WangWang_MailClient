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
        QMessageBox::critical(0, QObject::tr("错误！"), tr("服务器域名错误！"),
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
            this->sendMsg("A001 LOGIN " + this->USERNAME + " " + this->PASSWORD + "\r\n");
            if (this->recvMsg()) {
                if ("A001 OK" != buf.left(7))
                    break;
                else return true;
            }
            return false;
        }
        sock->abort(); //中断本次连接
    }
    //连接服务器失败
    QMessageBox::warning(0, QObject::tr("警告！"), tr("连接服务器失败！"),
        QMessageBox::Yes); //警告对话框
    return false;
}

bool iMap::logout()
{
    this->sendMsg("A100 LOGOUT\r\n");
    this->recvMsg();
    this->sock->close();
    return true;
}

void iMap::sendMsg(QString msg)
{
    sock->write(msg.toLatin1(), msg.toLatin1().size());
    this->updateLog("[C]: " + msg);
}

bool iMap::recvMsg()
{
    QString s;
    if (sock->waitForReadyRead(3000)) { //等待最多3秒
        buf.clear();
        bool first=true;
        this->MailtextBytes=0;
        while (sock->canReadLine()){
            if(first) {
                this->MailtextBytes+=sock-> bytesAvailable(); //读取本次可以读取的字节数
                first=false;
            }
            buf.append(sock->readLine());
        }
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
//    for (int i = 0; i < log.size(); i++) {
//        qDebug() << log.at(i);
//    }
//
    return this->log;
}


QStringList& iMap::getMailList(QString BOXNAME,bool& OK)
{
    this->sendMsg("A003 examine "+BOXNAME+"\r\n");
    this->InboxList.clear();
    if (this->recvMsg()) {
        QStringList A002_list;
        A002_list = buf.split("\r\n");
        A002_list.removeLast(); //去掉最后一个空字符串
        //成功打开INBOX
        bool OK1;
        qint32 exists = A002_list.at(0).split(" ").at(1).toInt(&OK1, 10);
        this->Mailnum=exists;
        if (OK1) {
            QString recvbuf;
            for (int i = exists; i >= 1;i--,
                 emit readprogress(exists-i,exists)) {//发送进度条信号
                this->sendMsg("A003 fetch " + QString::number(i, 10) + " BODY[header]\r\n");
                while ((OK1=this->recvMsg())) {//循环接收，因为可能会被拆成多个报文段
                    if(("* "==buf.left(2))&&(buf.split("\r\n").at(0).contains("FETCH"))){
                        //收到报文头，则将recvbuf内容推送，清空，重写,因此，第一次是脏数据，不推送
                        if(i<exists)this->InboxList<<recvbuf;
                        recvbuf.clear();
                        recvbuf.append(buf);
                        break;
                    }
                    else{
                        //剩余报文段继续组装
                        recvbuf.append(buf);
                    }
                }
                if(i==1) this->InboxList<<recvbuf;
                if(!OK1){
                    OK = false;
                    return this->InboxList;
                }
            }
            OK = true;
        }
    } else
        OK = false;
    return this->InboxList;
}

QString &iMap::getMailBody(qint32 index)
{
    this->sendMsg("A004 fetch " + QString::number(this->Mailnum-index, 10) + " BODY[text]\r\n");
    bool OK1=false;
    qint32 texttotal=0;
    this->Mailbodytext.clear();
    while ((OK1=this->recvMsg())) {//循环接收，因为可能会被拆成多个报文段
        texttotal+=this->MailtextBytes;
        qDebug()<<Mailbodytext.toLocal8Bit().size()<<texttotal;
        emit readprogress(this->Mailbodytext.toLocal8Bit().size(),texttotal);
        this->Mailbodytext.append(this->buf);
        if(this->Mailbodytext.toLocal8Bit().size()==texttotal) break; //完全接受数据则不再等待
    }
    qDebug()<<Mailbodytext.toLocal8Bit().size()<<texttotal;
    emit readprogress(this->Mailbodytext.toLatin1().size(),texttotal);
    return this->Mailbodytext;
}

iMap::~iMap()
{
    this->logout();
    delete sock;
}
