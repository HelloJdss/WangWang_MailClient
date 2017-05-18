#ifndef IMAPTHREAD_H
#define IMAPTHREAD_H
#include "wwmail.h"
#include <QMutex>
#include <QMutexLocker>
#include <QString>
#include <QStringList>
#include <QTcpSocket>
#include <QThread>

class AccountInfo;
namespace iMapClass {
class iMap;
}
class iMap;                     //前置声明

class imapThread
    : public QThread // imapthread管理函数，此函数中的各类槽函数均为创建imapThread实例的线程调用
{
  Q_OBJECT
public:
  explicit imapThread(const AccountInfo account, QObject *parent = 0);
  void setAccount(const AccountInfo account);
  QString getAccountname(); //记录了线程承载的帐户名，作为线程的唯一标识
  iMap *imap;               // imap连接,因为iMap为前置声明，只能用指针或引用，imap对象成员未知
  Qt::HANDLE getThreadID();

  ~imapThread();

protected:
  void run();

private:
  AccountInfo *account; //帐户信息
  QMutex mutex;
  Qt::HANDLE runtimeThreadID; //运行时线程PID
signals:
  void errorMsg(QString);             //向GUI线程发送错误信息
  void setimapAccount(AccountInfo *); //向子线程发送设定帐号信息信号
public slots:
  void imaperrorMsg(QString msg); //转发来自imap的错误信息
  void imapstatus(qint32 status);
  void setimapact(); //接收来自主进程的消息，更新imap socket帐号信息
};


#define Logout_ 0
#define Login_ 1
#define SELECTED_ 2 //已选择邮箱
#define GetHeader_ 3
#define GetBody_ 4
#define Delete_ 5 //删除邮件

class MimeData { //邮件体解析类
private:
  QString From;
  QString To;
  QString Subject;
  QString Date;
  QString Header;
  QString Body;
  QString ContentType;
  QString ContentEncoding;
  QString Boundary;
  qint32 Size;
  qint32 Folderindex; //位于哪个邮箱
  qint32 Headerindex; //位于第几个
  QString Account; //收取信息的帐号
public:
  void setAccount(QString Account);
  bool setHeader(QString HeaderText);
  void setBody(QString BodyText);
  void setHeaderindex(qint32 index); //设置处于邮箱中的序号
  void setFolderindex(qint32 index); //设置邮箱的编号
  bool SaveAsEML(QString); //保存为email文件
  QByteArray DecodequotedPrintable(const QByteArray &code);
  QString DecodeHeaderText(QString Text);
  const QString getAccount() const{return this->Account;}
  const qint32& getFolderindex() const{return this->Folderindex;}
  const qint32& getHeaderindex() const{return this->Headerindex;}
  const QString& getFrom() const{ return this->From; }
  const QString& getTo() const{ return this->To; }
  const QString& getSubject() const{ return this->Subject; }
  const QString& getDate() const{ return this->Date; }
  const QString& getHeader() const{return this->Header;}
  const QString& getHeaderType() const{return this->ContentType;}
  const QString& getHeaderEncoding() const{return this->ContentEncoding;}
  const QString& getHeaderBoundary() const{return this->Boundary;}
  const QString& getBody() const{return this->Body;}
  qint32 size() const{ return this->Size; }
};

class iMap : public QObject {
  Q_OBJECT
public:
  explicit iMap(QObject *parent = 0);
  bool isConnected() const; //判断是否已经连接
  int base64Amendcharcode(char); //修正的base64解码，用于utf-7解码
  QString utf7Decode(QByteArray);
  //  const QStringList &getLog();  //获取日志信息
  ~iMap();

private:
  QString useraccount;
  QString USERNAME;
  QString PASSWORD;
  QString Host; //主机地址
  quint16 Port; //主机端口
  QTcpSocket *sock;
  QString buf;                //读取数据缓冲区
  QStringList log;            //系统接收日志
  QString logfilename;        //日志文件名称
  QStringList FolderList; //邮箱列表
  QStringList HeaderList;     //收件箱列表
  QList<MimeData> MimeDataList;   //经处理后的邮件列表
//  QString Mailbodytext;       //邮件正文
//  qint32 Mailnum;             //邮件数目
  qint32 hasRecvBytes;       //已接受的邮件体字节数目
  qint32 totalRecvBytes;      //须接受的总长度
  bool iscreated;
  qint32 status;
  qint32 exists;
  qint32 currentSelected; //当前选择的邮箱序号
  void changestate(qint32 state);
  bool login();              //登陆imap服务器
  bool logout();             //退出服务器并关闭sock
  void sendMsg(QString msg); //向服务器发送信息
  bool recvMsg();            //获取服务器信息并更新缓冲区
  QStringList imapMailFolderList(QStringList &display); //获取邮箱列表
  bool imapMailHeaderList(QString foldername); //获取邮箱邮件列表
  bool imapMailBody(int index); //获取邮件完整信息
  void updateLog(QString msg); //更新日志
  void saveLog();              //保存日志
  mutable QMutex mutex;
signals:
  void StartProgressDialog();
  void SetProgress(qint32, qint32);
  void CloseProgressDialog();
  void errorMsg(QString);
  void warningMsg(QString);
  void changedstatus(qint32);
  void addMailFolderlist(QString, QStringList); //请求GUI进程添加邮箱名列表
  void addMailHeaderlist(QList<MimeData>&);          //反馈给GUI线程,引用类型防止复制，减少开销
  void CreateEmlWindow(const MimeData&,const iMap*);
  // public slots:
  //  QString &getMailBody(qint32 index); //获取邮件体
  // private slots:
public slots:
  void startConnect();                         //开启sock连接
  void setAccount(const AccountInfo *account); //设置帐户信息
  void getHeaderList(QString useraccount, int index); //获取指定邮箱邮件头列表
  void getBody(QString useraccount,int index); //获取指定邮件正文
  void imapDelete(qint32 Folderindex,qint32 Headerindex); //删除邮件
};

#endif // IMAPTHREAD_H
