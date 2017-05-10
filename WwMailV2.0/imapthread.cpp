#include "imapthread.h"
#include <QDateTime>
#include <QFile>
#include <QMutexLocker>
#include <QRegularExpression>
#include <QStringList>
#include <QTextCodec>
#include <QtNetwork>


imapThread::imapThread(const AccountInfo account, QObject *parent)
    : QThread(parent) {
  this->account = new AccountInfo(account);
  this->imap = new iMap;
  //在imapThread中不能调用delete
  // this->imap，因为在GUI线程中，已经将iMap对象移至新线程,而iMap中的socket是事件驱动的
  //"Cannot send events to objects owned by a different thread.
  // Current thread 19bb30d8. Receiver '' (of type 'QNativeSocketEngine') was
  // created in thread 19add9d0"
  emit setimapact();
}

void imapThread::setAccount(const AccountInfo account) {
  delete this->account;
  this->account = new AccountInfo(account);
}

QString imapThread::getAccountname() { return this->account->accountname; }

Qt::HANDLE imapThread::getThreadID() { return this->runtimeThreadID; }

imapThread::~imapThread() {
  delete this->account;
  qDebug() << "thread quit！ pid: " << this->getThreadID();
}

void imapThread::run() {
  this->runtimeThreadID = this->currentThreadId();
  qDebug() << "thread run！ pid：" << this->getThreadID();
  connect(this->imap, &iMap::changedstatus, this, &imapThread::imapstatus);
  exec();
  delete this->imap;
}

void imapThread::imaperrorMsg(QString msg) { emit errorMsg(msg); }

void imapThread::imapstatus(qint32 status) {
  qDebug() << getThreadID() << "status: " << status;
}

void imapThread::setimapact() { emit setimapAccount(this->account); }

iMap::iMap(QObject *parent) : QObject(parent) {
  iscreated = false;
  status = 0;
}

void iMap::setAccount(const AccountInfo *account) {
  QMutexLocker locker(&mutex);
  useraccount = account->accountname;
  USERNAME = account->username;
  PASSWORD = account->userpassword;
  Host = account->imapfield;
  Port = account->imapport;
}

void iMap::getHeaderList(QString useraccount, int index) {
  if (this->useraccount == useraccount) { //如果是针对本线程的，则接受
    emit StartProgressDialog();
    if (imapMailHeaderList(this->FolderList.at(index))) {
      this->MimeDataList.clear();
      for (int i = 0; i < this->HeaderList.size(); i++) {
        MimeData mail;
        mail.setHeader(this->HeaderList.at(i));
        this->MimeDataList << mail;
      }
    }
    emit addMailHeaderlist(this->MimeDataList);
    emit CloseProgressDialog();
    // qDebug()<<this->HeaderList;
    }
}

void iMap::getBody(QString useraccount, int index)
{
 if(this->useraccount==useraccount){
     if((index>=0)&&(index<=this->MimeDataList.size()))
       qDebug()<<index;
       imapMailBody(index);
   }
}

void iMap::startConnect() {
  if (!iscreated) {
    sock = new QTcpSocket(); //建立一个Tcp sock
    qDebug() << "create tcp socket in pid " << QThread::currentThreadId();
    iscreated = true;
    //    QDateTime time = QDateTime::currentDateTime();
    QString text;
    //    text = "LogFile-imap-" + time.toString("yyyy_MM_dd_hh_mm_ss") +
    //           "-thread_0x" +
    //           QString::number(qint64(QThread::currentThreadId()), 16) +
    //           ".log";
    text = "LogFile_imap_" + useraccount + ".log";
    logfilename = text;
    QFile file(logfilename);
    if (file.open(QFile::Append)) {
      QTextStream out(&file);
      //本次连接的分隔符
      out << "\niMap "
             "================================================================="
             "=========>> New Connected:";
      file.close();
    }
  } else
    logout();
  if (login()) {
    QStringList display;
    FolderList = imapMailFolderList(display);
    emit addMailFolderlist(useraccount, display);
  }
}

bool iMap::isConnected() const { return iscreated; }

int iMap::base64Amendcharcode(char c) {
  if (c == '&')
    return 62;
  if (c == '-')
    return 63;
  if (c >= 'a' && c <= 'z')
    return c - 71;
  else if (c >= 'A' && c <= 'Z')
    return c - 65;
  else
    return c + 4;
}

QString iMap::utf7Decode(QByteArray s) {
  int len = 0, code = 0, need, base64;
  int slen = s.length();
  QString t;
  for (int i = 0; i < slen; i++) {
    base64 = base64Amendcharcode(s.at(i));
    if (len + 6 < 16) {
      code = (code << 6) | base64;
      len += 6;
    } else {
      need = 16 - len;
      code = (code << need) | (base64 >> (6 - need)); //高位凑足16位
      t.append(QChar(code));
      // t.append(char((code&(0xFF00))>>8));
      // t.append(char(code&0x00FF));
      code = ((1 << (6 - need)) - 1) & base64; //低位留作下一次继续
      len = 6 - need;
    }
  }
  return t;
}

bool iMap::login() {
  QHostInfo info = QHostInfo::fromName(Host);
  if (0 == info.addresses().size()) {
    emit errorMsg("帐户：" + useraccount + "\nimap服务器域名错误！");
    return false;
  }
  //连接所有IP列表

  for (int i = 0; i < info.addresses().size(); i++) {
    this->sock->connectToHost(QHostAddress(info.addresses().at(i)), Port);
    changestate(Login_);
    if (!this->recvMsg())
      break; //接收数据
    if ("* OK" == buf.left(4)) {
      this->sendMsg("A001 LOGIN " + this->USERNAME + " " + this->PASSWORD +
                    "\r\n");
      if (this->recvMsg()) {
        if ("A001 OK" != buf.left(7))
          break;
        else
          return true;
      }
      return false;
    }
    sock->abort(); //中断本次连接
  }
  //连接服务器失败
  emit warningMsg("帐户：" + useraccount + "\n连接服务器失败！");
  return false;
}

bool iMap::logout() {
  sendMsg("A100 LOGOUT\r\n");
  recvMsg();
  sock->close();
  changestate(Logout_);
  return true;
}

void iMap::sendMsg(QString msg) {
  sock->write(msg.toLatin1(), msg.toLatin1().size());
  updateLog("[C]:\n" + msg);
}

bool iMap::recvMsg() {
  if (!sock->waitForReadyRead(3000)) { //最多等待3秒
    QString s("Wait Timeout!");
    updateLog(s);
    return false;
  }
  buf.clear();
  qint64 readlength = 0;
  QRegularExpression rx("(\\*|.{4}) OK");
  QRegularExpressionMatch match;
  while ((readlength = sock->bytesAvailable()) ||
         (sock->waitForReadyRead(
             500))) { //检测可以读取的字节数,，如果不可读，则尝试获取新的数据
    QString recv = sock->read(readlength);
    buf.append(recv);
    if(this->status==GetBody_){
        this->hasRecvBytes+=recv.size();
        emit SetProgress(this->hasRecvBytes,this->totalRecvBytes);
      }
    match = rx.match(recv);
    if(match.hasMatch()) break; //如果收到反馈OK，则立即结束
  }
  updateLog("[S]:\n" + buf);
  return true;
}

QStringList iMap::imapMailFolderList(QStringList &display) {
  sendMsg("A002 LIST \"\" *\r\n");
  QStringList ret;
  display.clear();
  if (recvMsg()) {
    QStringList BOXList = buf.split("\r\n");
    for (int i = 0; i < BOXList.size(); i++) {
      QRegularExpression rx(".*LIST (\\(.*\\)) (\".*\") (\".*\")");
      QRegularExpressionMatch match, matchutf_7;
      QRegularExpression utf_7("&(.*?)-");
      match = rx.match(BOXList.at(i));
      if (match.hasMatch()) {
        if (match.captured(1).contains("NoSelect"))
          continue; //跳过本次
        QString str = match.captured(3);
        ret << str; //返回原始信箱名
        matchutf_7 = utf_7.match(str);
        QTextCodec *codec = QTextCodec::codecForName("utf-8");
        while (matchutf_7.hasMatch()) {
          QString unic = utf7Decode(matchutf_7.captured(1).toLocal8Bit());
          str = str.replace(matchutf_7.capturedStart(0),
                            matchutf_7.capturedLength(0),
                            codec->toUnicode(unic.toUtf8()));
          matchutf_7 = utf_7.match(str);
        }
        display << str.remove("\""); //显示名称解码处理
      }
    }
  }
  return ret;
}

bool iMap::imapMailHeaderList(QString foldername) {
  if(status==SELECTED_){ //已选择的话，先退出
      this->sendMsg("A200 CLOSE\r\n");
      this->recvMsg();
    }
  this->sendMsg("A003 SELECT " + foldername + "\r\n");
  this->HeaderList.clear();
  if (this->recvMsg()) {
    //QStringList A003_list;
    //A003_list = buf.split("\r\n");
    //A003_list.removeLast(); //去掉最后一个空字符串
    //成功打开INBOX
    changestate(SELECTED_);

    QRegularExpression reExists("\\* (\\d+) EXISTS\r\n");
    QRegularExpressionMatch match;
    match=reExists.match(buf);
    bool OK=false;
  //  qint32 exists = A003_list.at(0).split(" ").at(1).toInt(&OK, 10);
    qint32 exists=0;
    if(match.hasMatch()){
        exists=match.captured(1).toInt(&OK,10);
      }
    changestate(GetHeader_);
    if (OK) {
      for (int i = exists; i >= 1;
           i--, emit SetProgress(exists - i, exists)) { //发送进度条信号
        this->sendMsg("A003 fetch " + QString::number(i, 10) +
                      //" (RFC822.SIZE BODY[HEADER.FIELDS(from to subject date)])\r\n");
                      " (RFC822.SIZE BODY[HEADER])\r\n");
                      //" BODY[HEADER]\r\n");
        if ((OK = this->recvMsg())) {
          this->HeaderList << buf;
        } else {
          qDebug() << this->useraccount << "recv Header Failed!";
          return false;
        }
      }
    }
    changestate(SELECTED_);
  } else {
    qDebug() << this->useraccount << "recv Header Failed!";
    return false;
  }
  return true;
}

bool iMap::imapMailBody(int index)
{
  if(this->status!=SELECTED_) return false;
  changestate(GetBody_);
  this->hasRecvBytes=this->MimeDataList.at(index).getHeader().size();
  this->totalRecvBytes=this->MimeDataList.at(index).size();
  this->sendMsg("A004 fetch " +
                QString::number(this->MimeDataList.size() - index, 10) +
                " BODY[text]\r\n");
  emit StartProgressDialog();
  if(this->recvMsg()){
      this->MimeDataList[index].setBody(buf);
      qDebug()<<this->MimeDataList[index].SaveAsEML("test.eml");
    }
  emit CloseProgressDialog();
  changestate(SELECTED_);
  return true;
}

void iMap::updateLog(QString msg) {
  QDateTime time = QDateTime::currentDateTime();
  QString text;
  text = "\n" + time.toString("yyyy-MM-dd hh:mm:ss") +
         " =======================================>> " + msg;
  if (log.size() > 25) { //每25条保存一次
    saveLog();
  }
  log << text;
}

void iMap::saveLog() {
  QFile file(logfilename);
  if (file.open(QFile::Append)) {
    QTextStream out(&file);
    for (int i = 0; i < log.size(); i++) {
      out << log.at(i);
    }
    log.clear();
    file.close();
  }
}

iMap::~iMap() {
  if (status > 0)
    logout();
  if (iscreated)
    delete sock;
  qDebug() << "delete iMap";
  saveLog();
}

void iMap::changestate(qint32 state) {
  QMutexLocker locker(&mutex); //局部变量，生命周期结束后自动解锁
  this->status = state;
  emit changedstatus(this->status);
}

bool MimeData::setHeader(QString HeaderText) {

//  qDebug()<<this->Header;
  QRegularExpression rxSize("\\*.*RFC822.SIZE (\\d+).*");
  QRegularExpressionMatch match;
  bool OK = false;
  match=rxSize.match(HeaderText);
  if(match.hasMatch()) {
      this->Size=match.captured(1).toInt(&OK,10);
      if(!OK) return false;
    }
  HeaderText.remove(QRegularExpression("(\\*.*\r\n)?"));
  HeaderText.remove(QRegularExpression("(A003.*\r\n)?")); //去除服务器命令信息即为原始Header;
  this->Header = HeaderText;
  QStringList part=this->Header.split("\r\n");
  QRegularExpression rxSpace("\\s");
  for(int i=0;i<part.size();){
      if((i+1)<part.size()){
          if(rxSpace.match(part.at(i+1).left(1)).hasMatch()){
              part[i].append("\r"+part.at(i+1)); //\r作为切分标志，注意，在QRegularExpression中.不能匹配\n
              part.removeAt(i+1);
              continue; //此处无需i++，因为part.size()--
            }
        }
      i++;
    }
  for(int i=0;i<part.size();i++){
      QRegularExpression rx("^Date:\\s*(.*?((\\d*)\\s*(\\w*)\\s*(\\d*)\\s*(\\d*:\\d*:\\d*)(.*)))");
      match=rx.match(part.at(i));
      if(match.hasMatch()) {
          QDateTime s;
          QString Month=match.captured(4);
          if(Month=="Jan") Month="1";
          else if(Month=="Feb") Month="2";
          else if(Month=="Mar") Month="3";
          else if(Month=="Apr") Month="4";
          else if(Month=="May") Month="5";
          else if(Month=="Jun") Month="6";
          else if(Month=="Jul") Month="7";
          else if(Month=="Aug") Month="8";
          else if(Month=="Sep") Month="9";
          else if(Month=="Oct") Month="10";
          else if(Month=="Nov") Month="11";
          else if(Month=="Dec") Month="12";
         // qDebug()<<s.fromString(match.captured(3),).toString("yyyy M dd hh:mm:ss");//fromString("9 Dec 2014 11:11:11","d MMM yyyy hh:mm:ss")).date();//.toString("yyyy M dd hh:mm:ss");
          this->Date=(match.captured(5)+"-"+Month+"-"+QString::number(match.captured(3).toInt(&OK,10),10)+"\t"+match.captured(6)+" "+match.captured(7));
          OK=true;
          //qDebug()<<this->Date;
          continue;
        }
      rx.setPattern("^From:\\s*(.*)");
      match=rx.match(part.at(i));
      if(match.hasMatch()) {
          this->From=DecodeHeaderText(match.captured(1));
          OK=true;
          //qDebug()<<this->From;
          continue;
        }
      rx.setPattern("^To:\\s*(.*)");
      match=rx.match(part.at(i));
      if(match.hasMatch()) {
          this->To=DecodeHeaderText(match.captured(1));
          OK=true;
          //qDebug()<<this->To;
          continue;
        }
      rx.setPattern("^Subject:\\s*(.*)");
      match=rx.match(part.at(i));
      if(match.hasMatch()) {
          this->Subject=DecodeHeaderText(match.captured(1));
          OK=true;
          //qDebug()<<this->Subject;
          continue;
        }
    }
  return OK;
}

void MimeData::setBody(QString BodyText)
{
  BodyText.remove(QRegularExpression("(\\*.*\r\n)?"));
  BodyText.remove(QRegularExpression("(A004.*\r\n)?")); //去除服务器命令信息即为原始Body;
  this->Body=BodyText;
}

bool MimeData::SaveAsEML(QString filename)
{
  QFile file(filename);
  if(file.open(QFile::WriteOnly)){
      QTextStream out(&file);
      out<<this->Header;
      out<<this->Body;
      file.close();
      return true;
    }
  return false;
}

QByteArray MimeData::DecodequotedPrintable(const QByteArray &code) {
  int pos = 0;
  QByteArray decode;
  while ((pos < code.size()) && ('\0' != code.at(pos))) {
    if (code.mid(pos, 3) == "=\r\n") {
      pos += 3; //跳过
    } else {
      if (code.at(pos) == '=') {
        QByteArray c = code.mid(pos + 1, 2);
        decode.append(QByteArray::fromHex(c));
        pos += 3;
      } else {
        decode.append(code.at(pos));
        pos++;
      }
    }
  }
  return decode;
}

QString MimeData::DecodeHeaderText(QString Text)
{
  QRegularExpression unDecode("=\\?(.*)\\?="); //替换加密部分
  QRegularExpressionMatch match;
  QString ret;
  QStringList unDecodeList = Text.split("\r");
  for(int i=0;i<unDecodeList.size();i++){
    //from1 = unDecode.cap(0);
      QRegExp c("\\s");
      while (c.exactMatch(unDecodeList[i].left(1))) {
        unDecodeList[i].remove(0, 1); //若首字符为空，则移除
      }
      int pos=0;
      pos = unDecodeList.at(i).indexOf(unDecode);
    match=unDecode.match(unDecodeList.at(i));
    if(match.hasMatch()){
         QString matchPart = match.captured(1);
         QStringList sub = matchPart.split("?");
         if (sub.size() == 3) {
           QTextCodec *codec = QTextCodec::codecForName(sub.at(0).toUpper().toLatin1());
           QString sub_utf;
           if (sub.at(1).toUpper() == "B") sub_utf = codec->toUnicode(QByteArray::fromBase64(sub.at(2).toLatin1()));
           else if (sub.at(1).toUpper() == "Q")  sub_utf = codec->toUnicode(DecodequotedPrintable(sub.at(2).toLatin1()));
           ret.append(QString(unDecodeList.at(i)).replace(pos,match.captured(0).size(),sub_utf)); //添加替换后的文本
           continue;
           }
      }
    ret.append(unDecodeList.at(i));
  }
  return ret;
}
