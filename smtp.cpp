#include "smtp.h"

#include <QDebug>


#define SENDSPACE 50

SMTP::SMTP(QObject* parent)
    : QObject(parent)
{
    USERNAME = "18040506495@163.com";
    PASSWORD = "wz19965050318";
    Host = "smtp.163.com"; //初始化为本地ip
    Port = 25;
    sock = new QTcpSocket(); //建立一个Tcp sock
    BCCmodel = false;
    textmodel = html;
}

void SMTP::readMesg()
{
    //str.append(sock->readAll());
    //qDebug()<<str;
}

qint32 SMTP::WriteAndWait(QString &s,bool wait)
{ //write and wait for result
    qDebug() << "command: " << s;
    s += "\r\n";
    qint64 res = sock->write(s.toLatin1(), s.toLatin1().size());
    //qDebug() << sock->state();
    if(wait)return res;
    sock->waitForReadyRead(30000); //等待最多30秒
    //qDebug() << sock->bytesAvailable();
    str = sock->readAll();
    qDebug() << "reply: " << str;
    return res;
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

bool SMTP::Logout() {
    QString s = "QUIT";
    WriteAndWait(s);
    if ("235" == str.left(3)) {
        qDebug() << "LOOUT SUCCESSFULLY.";
        return true;
    }
    return false;
}



bool SMTP::ReplyMail(QString Date, QString reply, QString Originalhead, QString Originaltext, QString recipient) {
    QString res = reply + "\n在" + Date + recipient + "写道：\n" + Originaltext;
    QStringList rl = {recipient};
    return SendMail("Re:" + Originalhead, rl, res);
}

bool SMTP::SendMail(QString subject, QStringList recipient,QString content) {
    //wait to be modified
    QString s = "MAIL FROM: <" + USERNAME + "@163.com" + ">",ans;
    WriteAndWait(s);
    if ("250" == str.left(3)) {
        for(int i = 0; i < recipient.size(); ++i) {
            s = "RCPT TO: <" + recipient[i] + ">";
            WriteAndWait(s);
            if ("250" == str.left(3)) continue;
            else return false;
        }  
        for(int i = 0; i < CCList.size(); ++i) {
            s = "RCPT TO: " + CCList[i] + "";
            WriteAndWait(s);
            if ("250" == str.left(3)) continue;
            else return false;
        }  
        for(int i = 0; i < BCCList.size(); ++i) {
            s = "RCPT TO: " + BCCList[i] + "";
            WriteAndWait(s);
            if ("250" == str.left(3)) continue;
            else return false;
        }                        
        if ("250" == str.left(3)) {
            s = "DATA";
            WriteAndWait(s);
            if ("354" == str.left(3)) {
                QStringList sList;
                PrepareMail(sList,subject,recipient,content);
                for(int i = 0; i < sList.size(); ++i) {
                    WriteAndWait(sList[i], true);
                }
                //WriteAndWait(s,true);
                s = ".";
                WriteAndWait(s);
                if ("250" == str.left(3)) {
                    qDebug() << "SendMail SUCCESSFULLY!";
                    return true;
                }
            }
        }
    }
    return false;
}

void SMTP::PrepareMail(QStringList &s,QString &subject, QStringList &recipient,QString &content){
    PrepareMailHead(s, subject, recipient);
    switch(textmodel) {
        case plain:
            SetPlainContent(s,content);
            break;
        case html:
            SetHtmlContent(s,content);
            break;
        case rtf:
            SetRtfContent(s,content);
            break;
    }
    SetBoundaryEnd(s);
}

void SMTP::PrepareTransmit(QString &content, QString date, QString from, QStringList to, QString originalhead, QString originaltext) {
    content += "\n\n\n\n";
    content += "----Transmit Infomation----";
    content += "Sender: " + from + "\n";
    content += "Date: " + date + "\n";
    content += "To:";
    for(int i = 0; i < to.size(); ++i) {
        content += to[i];
    }
    content += "\n";
    content += "Subject: " + originalhead + "\n";
    content += originaltext;
}

void SMTP::PrepareMailHead(QStringList &s,QString &subject, QStringList &recipient) {
    for(int i = 0; i < recipient.size(); ++i) {
        recipient[i] = recipient[i] + "\"<" + recipient[i] + ">";
    }
    s << "From: "+ BCCname
        << "Sender: <" + USERNAME + "@163.com>" 
        << "To:\"" + recipient.join(',');
    if(BCCmodel) {
        QString string = "BCC: \"" + BCCList.join(',');
        s << string;
    } 
    if(CCModel) {
        QString string = "CC: \"" + CCList.join(',');
        s << string;            
    }
    s << "Subject: =?UTF-8?B?" + subject.toUtf8().toBase64() + "?="
        << "MIME-Version: 1.0"
        << "Content-Type: multipart/mixed;"
        << "  boundary=\"one\""
        << "";
}

void SMTP::SetTextModel(model m) {
    textmodel = m;
}


void SMTP::SetPlainContent(QStringList &s,QString &content) {
    s << "--one"
        << "Content-Type: text/plain;"
        << "  charset=\"UTF-8\""
        << "Content-Transfer-Encoding: base64"
        << "";
    QString str = QObject::tr(content.toUtf8().toBase64());
    qint64 length = str.length();
    for(qint64 cur = 0; cur < length; emit progress(cur*100/length,100)){
        s << str.mid(cur,SENDSPACE);
        cur += SENDSPACE;
    }
    s << "";
}

void SMTP::SetHtmlContent(QStringList &s,QString &content) {
    s << "--one"
        << "Content-Type: text/html;"
        << "  charset=\"UTF-8\""
        << "Content-Transfer-Encoding: base64"
        << "";
    QString str1 = QObject::tr(content.toUtf8().toBase64());
    qint64 length1 = str1.length();
    for(qint64 cur = 0; cur < length1; emit progress(cur*100/length1,100)){
        s << str1.mid(cur,SENDSPACE);
        cur += SENDSPACE;
    }
    s << "";
}

void SMTP::SetRtfContent(QStringList &s,QString &content) {
    s << "--one"
        << "Content-Type: application/rtf;"
        << "  charset=\"UTF-8\""
        << "Content-Transfer-Encoding: base64"
        << "";
    QString str1 = QObject::tr(content.toUtf8().toBase64());
    qint64 length1 = str1.length();
    for(qint64 cur = 0; cur < length1; emit progress(cur*100/length1,100)){
        s << str1.mid(cur,SENDSPACE);
        cur += SENDSPACE;
    }
    s << "";
}

void SMTP::SetBoundaryEnd(QStringList &s) {
    s << "--one--";
}
