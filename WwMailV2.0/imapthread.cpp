#include "imapthread.h"
#include <QtNetwork>

imapThread::imapThread(const AccountInfo account, QObject *parent)
  : QThread (parent),sockcreated(false)
{
  this->account=new AccountInfo(account);
}

QString imapThread::getAccountname()
{
  return this->account->accountname;
}

imapThread::~imapThread()
{
  delete this->account;
  if(sockcreated) delete this->imap;
  qDebug()<<"子进程已退出！";
}

void imapThread::run()
{
  this->imap=new iMap;
  this->sockcreated=true;
  qDebug()<<"子进程已启动！ ID："<<this->currentThreadId();
  connect(this->imap,&iMap::errorMsg,this,&imapThread::imaperrorMsg);
  exec();
}

void imapThread::imaperrorMsg(QString msg)
{
  emit errorMsg(msg);
}

iMap::iMap(QObject *parent)
  :QObject (parent)
{
  sock = new QTcpSocket(); //建立一个Tcp sock
}

void iMap::setUserName(QString USERNAME)
{
  this->USERNAME=USERNAME;
}

void iMap::setPassWord(QString PASSWORD)
{
  this->PASSWORD=PASSWORD;
}

void iMap::setHost(QString Host)
{
  this->Host=Host;
}

void iMap::setPort(quint16 Port)
{
  this->Port=Port;
}

iMap::~iMap()
{
  delete sock;
}

