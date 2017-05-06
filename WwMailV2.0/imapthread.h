#ifndef IMAPTHREAD_H
#define IMAPTHREAD_H
#include "wwmail.h"
#include <QThread>
#include <QTcpSocket>
#include <QMutex>
#include <QMutexLocker>
#include <QString>
#include <QStringList>

class AccountInfo;
class iMap;
class imapThread : public QThread
{
  Q_OBJECT
public:

  explicit imapThread(const AccountInfo account,QObject * parent=0);
  QString getAccountname();
  ~imapThread();
protected:
  void run();
private:
  AccountInfo *account; //帐户信息
  iMap *imap; //imap连接
  QMutex mutex;
  bool sockcreated; //判断sock是否已经初始化
signals:
    void errorMsg(QString); //向GUI线程发送错误信息
public slots:
   void imaperrorMsg(QString msg);//转发来自imap的错误信息
};

namespace iMapClass {
class iMap;
}

class iMap : public QObject {
  Q_OBJECT
public:
  explicit iMap(QObject *parent = 0);
  void setUserName(QString USERNAME); //设置用户名，返回用户名长度
  void setPassWord(QString PASSWORD); //设置密码，返回密码字符串长度
  void setHost(QString Host); //设置邮件服务器地址
  void setPort(quint16 Port);   //设置邮件服务器端口号
//  bool login();                 //登陆imap服务器
//  bool logout();                //退出服务器并关闭sock
//  void sendMsg(QString msg);    //向服务器发送信息
//  bool recvMsg();               //获取服务器信息并更新缓冲区
//  void updateLog(QString msg);  //更新日志
//  const QStringList &getLog();  //获取日志信息
  ~iMap();

private:
  QString USERNAME;
  QString PASSWORD;
  QString Host;        //主机地址
  quint16 Port;        //主机端口
  QTcpSocket *sock;
  QString buf;           //读取数据缓冲区
  QStringList log;       //系统接收日志
  QStringList InboxList; //收件箱列表
  QString Mailbodytext;  //邮件正文
  qint32 Mailnum;        //邮件数目
  qint32 MailtextBytes;  //需要接受的邮件体字节数目
signals:
//  void readprogress(qint32, qint32);
  void errorMsg(QString);
//public slots:
//  QStringList &getMailList(QString BOXNAME,bool &OK); //获取邮箱邮件列表，并记录邮件数目
//  QString &getMailBody(qint32 index); //获取邮件体
//private slots:
};


#endif // IMAPTHREAD_H
