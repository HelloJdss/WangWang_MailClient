#include "clientwindow.h"
#include "ui_clientwindow.h"
#include <QLabel>
#include <QRegExp>
#include <QStringList>
#include <QTextCodec>
#include <QTimer>
#define _version "0.1"

ClientWindow::ClientWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::ClientWindow), Login_dialog(parent) {
  ui->setupUi(this);
  this->imapLog_num = 0;
  this->loginsuccess = false;
  this->MailBoxTree = new QStandardItemModel(ui->MailBoxView);
  this->MailTable = new QStandardItemModel(ui->MailTable);
  this->on_action_relog_triggered();
  if (isLogin()) {
    //若成功登陆，则加载资源
    QString version = _version;
    QString Welcome = "欢迎使用汪汪邮箱(*^__^*) ~~";
    ui->statusBar->showMessage(Welcome);
    //设定当前时钟
    this->permanent = new QLabel(this);
    QTimer *localtimer = new QTimer(this);
    connect(localtimer, &QTimer::timeout, this, &ClientWindow::timerupdate);
    ui->statusBar->addPermanentWidget(this->permanent);
    localtimer->start(1000);
    //绑定操作信号
    connect(&this->imap, &iMap::readprogress, this,
            &ClientWindow::updateProgressbar_read); //绑定读取邮件进度条信号
    //        QObject::connect(ui->action_undo, SIGNAL(triggered()),
    //        ui->WriteMail,
    //            SLOT(undo()));
    //        QObject::connect(ui->action_redo, SIGNAL(triggered()),
    //        ui->WriteMail,
    //            SLOT(redo()));
    //        QObject::connect(ui->action_copy, SIGNAL(triggered()),
    //        ui->WriteMail,
    //            SLOT(copy()));
    //        QObject::connect(ui->action_paste, SIGNAL(triggered()),
    //        ui->WriteMail,
    //            SLOT(paste()));
    //        QObject::connect(ui->action_selectAll, SIGNAL(triggered()),
    //        ui->WriteMail,
    //            SLOT(selectAll()));
    //        QObject::connect(ui->action_cut, SIGNAL(triggered()),
    //        ui->WriteMail,
    //            SLOT(cut()));
    //从服务器加载报文
    initMailBoxListTree();
    initMailTableView();
  }
}

bool ClientWindow::isLogin() { return loginsuccess; }

ClientWindow::~ClientWindow() { delete ui; }

void ClientWindow::initMailBoxListTree() {
  this->MailBoxTree->setHorizontalHeaderLabels(QStringList()
                                               << QString(tr("邮箱列表")));
  this->ui->MailBoxView->setModel(this->MailBoxTree);
  QStandardItem *item = new QStandardItem(QString(tr("我的邮箱")));
  this->MailBoxTree->appendRow(item);
  item->appendRow(new QStandardItem(QString(tr("收件箱"))));
  item->appendRow(new QStandardItem(QString(tr("已发送"))));
  item->appendRow(new QStandardItem(QString(tr("草稿箱"))));
  item->appendRow(new QStandardItem(QString(tr("已删除"))));
  item->appendRow(new QStandardItem(QString(tr("垃圾箱"))));
}

void ClientWindow::initMailTableView() {
  this->MailTable->clear();
  this->MailTable->setHorizontalHeaderLabels(
      QStringList() << QString(tr("序号")) << QString(tr("发件人"))
                    << QString(tr("收件人")) << QString(tr("主题"))
                    << QString(tr("日期")));
  this->ui->MailTable->setModel(this->MailTable);
  this->ui->MailTable->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
  this->ui->MailTable->verticalHeader()->hide();
  this->ui->MailTable->setColumnWidth(0, 50);
  this->ui->MailTable->setColumnWidth(1, 225);
  this->ui->MailTable->setColumnWidth(2, 225);
  this->ui->MailTable->setColumnWidth(3, 400);
  this->ui->MailTable->setColumnWidth(4, 250);
}

void ClientWindow::updateMailTableView() {
  initMailTableView();
  for (int i = 0; i < this->MaillistDataInTable->size(); i++) {
    this->MailTable->setItem(i, 0,
                             new QStandardItem(QString::number(i + 1, 10)));
    this->MailTable->item(i, 0)->setTextAlignment(Qt::AlignCenter); //序号居中
    QStringList MailHeader = this->MaillistDataInTable->at(i).split("\r\n");
    QRegExp spacec("\\s");
    for (int k = 0; k < MailHeader.size(); k++) {
      int j = k + 1;
      while (1) { //将同一段落合并
        if ((j < MailHeader.size()) &&
            (spacec.exactMatch(MailHeader.at(j).left(1)))) {
          MailHeader[k].append(MailHeader.at(j));
          MailHeader.removeAt(j);
        } else
          break;
      }
    }
    for (int j = 0; j < MailHeader.size(); j++) {
      if (MailHeader.at(j).left(5) == "From:") {
        //处理发件人
        QString from = MailHeader.at(j);
        QString from1 = from.remove("From:").remove(" ");
        QRegExp Base64c("=(.*)="); //提取加密部分
        int pos = 0;
        pos = Base64c.indexIn(from1, pos);
        if (pos != -1) {
          from1 = Base64c.cap(0);
          QStringList sub = from1.split("?");
          if (sub.size() < 3) {
            //异常
            QMessageBox::warning(this, QObject::tr("警告！"),
                                 tr("邮件发件人解析失败，请重试！"),
                                 QMessageBox::Yes); //警告对话框
            return;
          }
          QTextCodec *codec =
              QTextCodec::codecForName(sub.at(1).toUpper().toLatin1());
          QString sub_utf;
          if (sub.at(2).toUpper() == "B")
            sub_utf =
                codec->toUnicode(QByteArray::fromBase64(sub.at(3).toLatin1()));
          else if (sub.at(2).toUpper() == "Q")
            sub_utf =
                codec->toUnicode(DecodequotedPrintable(sub.at(3).toLatin1()));
          this->MailTable->setItem(i, 1, new QStandardItem(sub_utf));
        } else
          this->MailTable->setItem(i, 1, new QStandardItem(from));
      } else if (MailHeader.at(j).left(3) == "To:") {
        //处理收件人
        QString to = MailHeader.at(j);
        QString to1 = to.remove("To:").remove(" ");
        QRegExp Base64c("=(.*)="); //提取加密部分
        int pos = 0;
        pos = Base64c.indexIn(to1, pos);
        if (pos != -1) {
          to1 = Base64c.cap(0);
          QStringList sub = to1.split("?");
          if (sub.size() < 3) {
            //异常
            QMessageBox::warning(this, QObject::tr("警告！"),
                                 tr("邮件收件人解析失败，请重试！"),
                                 QMessageBox::Yes); //警告对话框
            return;
          }
          QTextCodec *codec =
              QTextCodec::codecForName(sub.at(1).toUpper().toLatin1());
          QString sub_utf;
          if (sub.at(2).toUpper() == "B")
            sub_utf =
                codec->toUnicode(QByteArray::fromBase64(sub.at(3).toLatin1()));
          else if (sub.at(2).toUpper() == "Q")
            sub_utf =
                codec->toUnicode(DecodequotedPrintable(sub.at(3).toLatin1()));
          this->MailTable->setItem(i, 2, new QStandardItem(sub_utf));
        } else
          this->MailTable->setItem(i, 2, new QStandardItem(to));
      } else if (MailHeader.at(j).left(8) == "Subject:") {
        //处理主题信息
        QString subject;
        QString subject1 = QString(MailHeader.at(j)).remove("Subject:");
        QRegExp c("\\s");
        while (c.exactMatch(subject1.left(1))) {
          subject1.remove(0, 1); //若首字符为空，则移除
        }
        QStringList CodeList = subject1.split(" ");
        bool find = 0;
        for (int Codesub = 0; Codesub < CodeList.size(); Codesub++) {
          if ("=?" == CodeList.at(Codesub).left(2)) {
            QStringList sub = CodeList.at(Codesub).split("?");
            if (sub.size() < 3) {
              //异常
              QMessageBox::warning(this, QObject::tr("警告！"),
                                   tr("邮件主题解析失败，请重试！"),
                                   QMessageBox::Yes); //警告对话框
              return;
            }
            QTextCodec *codec =
                QTextCodec::codecForName(sub.at(1).toUpper().toLatin1());
            QString sub_utf;
            if (sub.at(2).toUpper() == "B")
              sub_utf = codec->toUnicode(
                  QByteArray::fromBase64(sub.at(3).toLatin1()));
            else if (sub.at(2).toUpper() == "Q")
              sub_utf =
                  codec->toUnicode(DecodequotedPrintable(sub.at(3).toLatin1()));
            subject.append(sub_utf);
            find = 1; //说明存在待解析的编码
          }
        }
        if (find)
          this->MailTable->setItem(i, 3, new QStandardItem(subject));
        else
          this->MailTable->setItem(i, 3, new QStandardItem(subject1));
      } else if (MailHeader.at(j).left(5) == "Date:") {
        //处理时间
        QString date = MailHeader.at(j);
        date = date.remove("Date:");
        QRegExp c("\\s");
        while (c.exactMatch(date.left(1))) {
          date.remove(0, 1); //若首字符为空，则移除
        }
        this->MailTable->setItem(i, 4, new QStandardItem(date));
      }
    }
  }
  QMessageBox::warning(0, QObject::tr("提示！"), tr("接收完成！"),
                       QMessageBox::Yes); //提示对话框
}

QByteArray ClientWindow::DecodequotedPrintable(const QByteArray &code) {
  //论手写解码函数一次成功是怎样的愉悦体验
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
  decode.append('\0');
  return decode;
}

void ClientWindow::timerupdate() {
  QDateTime time = QDateTime::currentDateTime();
  QString text = "本地时间: ";
  text += time.toString("yyyy-MM-dd hh:mm:ss");
  this->permanent->setText(text);
}

void ClientWindow::setimapLog() {
  QStringList imapLog = this->imap.getLog();
  for (; this->imapLog_num < imapLog.size(); this->imapLog_num++) {
    ui->Logview->append(imapLog.at(this->imapLog_num));
  }
}

void ClientWindow::on_action_imapLog_triggered() { setimapLog(); }

void ClientWindow::on_action_relog_triggered() {
  Login_dialog.setModal(
      true); //设置为模态对话框，禁止在登陆之前与主窗口进行交互
  Login_dialog.show();
  Login_dialog.move(
      (QApplication::desktop()->width() - Login_dialog.width()) / 2,
      (QApplication::desktop()->height() - Login_dialog.height()) /
          2); //调整窗口位到屏幕中央
  auto ret = Login_dialog.exec();
  if (ret == QDialog::Rejected) {
    if (!loginsuccess)      //若已成功登录，则忽略
      loginsuccess = false; //如果拒绝登入，则设定登陆验证为失败
  } else if (ret == QDialog::Accepted) {
    if (loginsuccess) //若已经成功登录，则先退出
      imap.logout();
    imap.setHost("imap.qq.com");
    imap.setPort(143);
    imap.setUserName(Login_dialog.getUSERNAME());
    imap.setPassWord(Login_dialog.getPASSWORD());
    imap.setServerfield(Login_dialog.getServerfield());
    loginsuccess = imap.login(); //进行登陆验证
  }
}

void ClientWindow::on_MailBoxView_doubleClicked(const QModelIndex &index) {
  if (index.parent().row() == 0) {
    bool OK = false;
    switch (index.row()) {
    case 0:
      this->MaillistDataInTable = &this->imap.getMailList("\"INBOX\"", OK);
      break;
    case 1:
      this->MaillistDataInTable =
          &this->imap.getMailList("\"Sent Messages\"", OK);
      break;
    case 2:
      this->MaillistDataInTable = &this->imap.getMailList("\"Drafts\"", OK);
      break;
    case 3:
      this->MaillistDataInTable =
          &this->imap.getMailList("\"Deleted Messages\"", OK);
      break;
    case 4:
      this->MaillistDataInTable = &this->imap.getMailList("\"Junk\"", OK);
      break;
    }
    if (OK)
      updateMailTableView();
    else {
      QMessageBox::warning(this, QObject::tr("警告！"),
                           tr("获取邮件列表失败，请重试！"),
                           QMessageBox::Yes); //警告对话框
    }
  }
}

void ClientWindow::on_MailTable_doubleClicked(const QModelIndex &index) {

  QString src = imap.getMailBody(index.row());
  QStringList srclist = src.split("\r\n");

  QStringList fullcode;
  QString partcode;
  QString charset;
  for (int i = 0; i < srclist.size(); i++) {
    if (srclist.at(i).contains("NextPart")) {
      //对上一分段进行处理
      fullcode << partcode;
      partcode.clear();
    }
    partcode.append(srclist.at(i) + "\r\n");
    if (srclist.at(i).left(2) == "* ")
      continue; //
  }
  fullcode << partcode;
  for (int i = 0; i < fullcode.size(); i++) {
    qDebug() << fullcode.at(i).split("\r\n");
    QStringList a = fullcode.at(i).split("\r\n");
  }
  // ui->MailText->setText();
}

void ClientWindow::updateProgressbar_read(qint32 readnum, qint32 maxnum) {
  ui->progressBar_read->setMaximum(maxnum);
  ui->progressBar_read->setValue(readnum);
}
