#include "smtp.h"
#include <QTcpSocket>
#include <QtNetwork>

#define SENDSPACE 50

SMTP::SMTP(QObject *parent) : QObject(parent) {
  BCCmodel = false;
  CCModel = false;
  textmodel = html;
}

void SMTP::readMesg() {
  // str.append(sock->readAll());
  // qDebug()<<str;
}

qint64 SMTP::WriteAndWait(QString &s, bool wait) { // write and wait for result
  qDebug() << "command: " << s;
  s += "\r\n";
  qint64 res = sock->write(s.toLatin1(), s.toLatin1().size());
  // qDebug() << sock->state();
  if (wait)
    return res;
  sock->waitForReadyRead(30000); //等待最多30秒
  // qDebug() << sock->bytesAvailable();
  str = sock->readAll();
  qDebug() << "reply: " << str;
  return res;
}

SMTP::~SMTP() { delete sock; }

bool SMTP::Connect(QString host, quint16 port) {
  sock = new QTcpSocket(); //建立一个Tcp sock
  Host = host;
  Port = port;
  qDebug()<<host;
  qDebug()<<port;
  QHostInfo info = QHostInfo::fromName(Host);
  if (0 == info.addresses().size()) {
    emit Msg(QString::fromLocal8Bit("SMTP服务器域名错误！"));
    return false;
  }
  qDebug() << "SMTP" << info.addresses();
  qDebug() << "SMTP" << Port;
  //连接所有IP列表
  // QString str;
  for (int i = 0; i < info.addresses().size(); i++) {
    this->sock->connectToHost(QHostAddress(info.addresses().at(i)), Port);
    qDebug() << sock->state();
    sock->waitForReadyRead(30000); //等待最多30秒
    qDebug() << sock->bytesAvailable();
    str = sock->readAll();
    qDebug() << str;
    if ("220" == str.left(3)) {
      // connect(sock,SIGNAL(readyRead()),this,SLOT(readMesg()));//连接槽函数，使得自动接受数据
      return true;
    }
    sock->abort(); //中断本次连接
  }
  //连接服务器失败
  emit Msg(QString::fromLocal8Bit("SMTP服务器连接失败！"));
  return false;
}

bool SMTP::Login(QString username, QString password) {
  USERNAME = username;
  PASSWORD = password;
  qDebug() << "USERNAME: " << USERNAME;
  QString s = "HELO "+act.smtpfield;
  qDebug()<<s;
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

bool SMTP::ReplyMail(QString Date, QString reply, QString Originalhead,
                     QString Originaltext, QString recipient) {
  QString res = reply + "\n在" + Date + recipient + "写道：\n" + Originaltext;
  QStringList rl = {recipient};
  return SendMail("Re:" + Originalhead, rl, res);
}

bool SMTP::SendMail(QString subject, QStringList recipient, QString content) {
  // wait to be modified
  QString s = "MAIL FROM: <" + act.accountname + ">", ans;
  WriteAndWait(s);
  if ("250" == str.left(3)) {
    qDebug() << "rsize:" << recipient.size() << "csize: " <<CCList.size()<<"BCCsize: " <<BCCList.size();
    for (int i = 0; i < recipient.size(); ++i) {
      s = "RCPT TO: <" + recipient[i] + ">";
      WriteAndWait(s);
      if ("250" == str.left(3))
        continue;
      else
        return false;
    }
    if(CCModel)
      for (int i = 0; i < CCList.size(); ++i) {
        s = "RCPT TO: <" + CCList[i] + ">";
        WriteAndWait(s);
        if ("250" == str.left(3))
          continue;
        else
          return false;
      }
    if(BCCmodel)
      for (int i = 0; i < BCCList.size(); ++i) {
        s = "RCPT TO: <" + BCCList[i] + ">";
        WriteAndWait(s);
        if ("250" == str.left(3))
          continue;
        else
          return false;
      }
    if ("250" == str.left(3)) {
      s = "DATA";
      WriteAndWait(s);
      if ("354" == str.left(3)) {
        QStringList sList;
        PrepareMail(sList, subject, recipient, content);
        for (int i = 0; i < sList.size(); ++i) {
          WriteAndWait(sList[i], true);
        }
        // WriteAndWait(s,true);
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

void SMTP::PrepareMail(QStringList &s, QString &subject, QStringList &recipient,
                       QString &content) {
  PrepareMailHead(s, subject, recipient);
  switch (textmodel) {
  case plain:
    SetPlainContent(s, content);
    break;
  case html:
    SetHtmlContent(s, content);
    break;
  case rtf:
    SetRtfContent(s, content);
    break;
  }
  SetBoundaryEnd(s);
}

void SMTP::PrepareTransmit(QString &content, QString date, QString from,
                           QStringList to, QString originalhead,
                           QString originaltext) {
  content += "\n\n\n\n";
  content += "----Transmit Infomation----";
  content += "Sender: " + from + "\n";
  content += "Date: " + date + "\n";
  content += "To:";
  for (int i = 0; i < to.size(); ++i) {
    content += to[i];
  }
  content += "\n";
  content += "Subject: " + originalhead + "\n";
  content += originaltext;
}

void SMTP::PrepareMailHead(QStringList &s, QString &subject,
                           QStringList &recipient) {
  for (int i = 0; i < recipient.size(); ++i) {
    recipient[i] = recipient[i] + "\"<" + recipient[i] + ">";
  }
  s << "From: \"=?UTF-8?B?" + BCCname.toUtf8().toBase64()+"?=\" " + "<" + act.accountname + ">" << "Sender: <" +act.accountname+">"
    << "To:\"" + recipient.join(',');
  if (BCCmodel) {
    QString string = "BCC: \"" + BCCList.join(',');
    s << string;
  }
  if (CCModel) {
    QString string = "CC: \"" + CCList.join(',');
    s << string;
  }
  s << "Subject: =?UTF-8?B?" + subject.toUtf8().toBase64() + "?="
    << "MIME-Version: 1.0"
    << "Content-Type: multipart/mixed;"
    << "  boundary=\"one\""
    << "";
}

void SMTP::SetTextModel(model m) { textmodel = m; }

void SMTP::SetPlainContent(QStringList &s, QString &content) {
  s << "--one"
    << "Content-Type: text/plain;"
    << "  charset=\"UTF-8\""
    << "Content-Transfer-Encoding: base64"
    << "";
  QString str = QObject::tr(content.toUtf8().toBase64());
  qint32 length = str.length();
  for (qint32 cur = 0; cur < length; emit progress(cur , length)) {
    s << str.mid(cur, SENDSPACE);
    cur += SENDSPACE;
  }
  emit progress(length,length);
  s << "";
}

void SMTP::SetHtmlContent(QStringList &s, QString &content) {
  s << "--one"
    << "Content-Type: text/html;"
    << "  charset=\"UTF-8\""
    << "Content-Transfer-Encoding: base64"
    << "";
  QString str1 = QObject::tr(content.toUtf8().toBase64());
  qint32 length1 = str1.length();
  for (qint32 cur = 0; cur < length1; emit progress(cur, length1)) {
    s << str1.mid(cur, SENDSPACE);
    cur += SENDSPACE;
  }
  emit progress(length1,length1);
  s << "";
}

void SMTP::SetRtfContent(QStringList &s, QString &content) {
  s << "--one"
    << "Content-Type: application/rtf;"
    << "  charset=\"UTF-8\""
    << "Content-Transfer-Encoding: base64"
    << "";
  QString str1 = QObject::tr(content.toUtf8().toBase64());
  qint32 length1 = str1.length();
  for (qint32 cur = 0; cur < length1; emit progress(cur ,length1)) {
    s << str1.mid(cur, SENDSPACE);
    cur += SENDSPACE;
  }
  emit progress(length1,length1);
  s << "";
}

void SMTP::SetBoundaryEnd(QStringList &s) { s << "--one--"; }

void smtpThread::run()
{
  smtp->SetAct(act);
  if(!smtp->Connect(act.smtpfield,act.smtpport)){
      delete smtp;
      return;
    }
  if(!smtp->Login(act.username,act.userpassword)){
      delete smtp;
      return;
    }
  smtp->SetTextModel(this->textmodel);
  smtp->SetCCModel(this->CCModel);
  smtp->SetBCCModel(this->BCCmodel);
  smtp->SetBCCName(this->BBCname);
  smtp->SetBCCList(this->BCCList);
  smtp->SetCCList(this->CCList);
  if(smtp->SendMail(this->Subject,this->To,this->Content)){
          emit smtp->iMsg(QString::fromLocal8Bit("邮件发送成功！"));

  }
  else emit smtp->Msg(QString::fromLocal8Bit("邮件发送失败！"));
  delete  smtp;
}

smtpThread::smtpThread(QObject *parent): QThread(parent)
{
  smtp=new SMTP();
}

smtpThread::~smtpThread()
{

}

