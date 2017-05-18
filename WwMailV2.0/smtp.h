#ifndef SMTP_H
#define SMTP_H

#include "wwmail.h"
#include <QThread>
#include <QTcpSocket>
enum model { plain, html, rtf };

namespace SMTPClass {
class SMTP;
}
class smtpThread;

class SMTP : public QObject {
  Q_OBJECT
public:
  explicit SMTP(QObject *parent = 0);
  ~SMTP();
  qint64 WriteAndWait(QString &s, bool wait = false);
  bool Connect(QString host, quint16 port);
  bool Login(QString username, QString password);
  bool Logout();
  bool SendMail(QString subject, QStringList recipient, QString content);
  bool ReplyMail(QString Date, QString reply, QString Originalhead,
                 QString Originaltext, QString recipient);
  void PrepareTransmit(QString &content, QString date, QString from,
                       QStringList to, QString originalhead,
                       QString originaltext);
  void PrepareMail(QStringList &s, QString &subject, QStringList &recipient,
                   QString &content);
  void PrepareMailHead(QStringList &s, QString &subject,
                       QStringList &recipient);
  void SetTextModel(model m);
  void SetPlainContent(QStringList &s, QString &content);
  void SetHtmlContent(QStringList &s, QString &content);
  void SetBoundaryEnd(QStringList &s);
  void SetRtfContent(QStringList &s, QString &content);
  inline void SetBCCModel(bool model) {
    BCCmodel = model;
  }
  inline void SetBCCName(QString name) {
    BCCname = name;
  }
  inline void SetCCModel(bool model) { CCModel = model; }
  inline void SetBCCList(QStringList blist) { BCCList = blist; }
  inline void SetCCList(QStringList clist) { CCList = clist; }
  void SetAct(AccountInfo act) {this->act = act;}

private:
  AccountInfo act;
  QStringList BCCList, CCList;
  int textmodel; //文本发送格式
  QString str;   //读取数据缓冲区
  QString USERNAME;
  QString PASSWORD;
  QString Host; //主机地址
  quint16 Port; //主机端口
  QTcpSocket *sock;
  bool BCCmodel, CCModel; //是否是密送模式,抄送模式
  QString BCCname;
private slots:
  void readMesg();
signals:
  void progress(qint32 cur, qint32 length);
  void Msg(QString);             //向GUI线程发送错误信息
  void iMsg(QString);
};

class smtpThread: public QThread{
  Q_OBJECT
protected:
  void run();
public:
  explicit smtpThread(QObject *parent = 0);
  ~smtpThread();
  AccountInfo act;
  QString BBCname;
  bool BCCmodel;
  bool CCModel;
  QStringList BCCList,CCList;
  enum model textmodel;
  QStringList To;
  QString Subject;
  QString Content;
  SMTP* smtp;
};

#endif // SMTP_H
