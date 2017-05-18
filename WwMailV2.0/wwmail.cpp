#include "wwmail.h"
#include "smtp.h"
#include "ui_wwmail.h"
#include <QAction>
#include <QDateTime>
#include <QFileDialog>
#include <QMenu>
#include <QStringListModel>
#include <QTimer>
#include <QDataStream>
#define _version "V2.0"
WwMail::WwMail(QWidget *parent) : QMainWindow(parent), ui(new Ui::WwMail) {
  ui->setupUi(this);
  QString version = _version;
  QString Welcome = QString::fromLocal8Bit("欢迎使用汪汪邮箱 ") + version +
                    QString::fromLocal8Bit(" (*^__^*) ~~");
  ui->statusBar->showMessage(Welcome);
  //设定当前时钟
  {
    this->permanent = new QLabel(this);
    QTimer *localtimer = new QTimer(this);
    connect(localtimer, &QTimer::timeout, this, &WwMail::timerupdate);
    ui->statusBar->addPermanentWidget(this->permanent);
    localtimer->start(1000);
  }
  ui->label_12->hide();
  ui->label_13->hide();
  ui->lineEdit_3->hide();
  ui->lineEdit_4->hide();
  ui->lineEdit_3->setEnabled(false);
  ui->lineEdit_4->setEnabled(false);
  ui->label->hide();
  ui->listView_2->hide();
  ui->splitter->setStretchFactor(0, 2);
  ui->splitter->setStretchFactor(1, 8);
  ui->splitter_2->setStretchFactor(0, 8);
  ui->splitter_2->setStretchFactor(1, 2);
  ui->pushButton_6->setEnabled(false);
  ui->comboBox_2->addItems(QStringList()<<"plain"<<"html"<<"rtf");
  QStandardItemModel *MailFolderTree =
      new QStandardItemModel(ui->treeView); //父对象为ui->treeView，智能释放
  MailFolderTree->setHorizontalHeaderLabels(
      QStringList() << QString::fromLocal8Bit("邮箱列表"));
  this->ui->treeView->header()->setDefaultAlignment(Qt::AlignCenter);
  this->ui->treeView->setModel(MailFolderTree);

  QStandardItemModel *RecentContactPerson =
      new QStandardItemModel(ui->listView);
  RecentContactPerson->setHorizontalHeaderLabels(
      QStringList() << QString::fromLocal8Bit(
          "双击帐号信息添加至收件人(*^__^*)"));
  this->ui->listView->setModel(RecentContactPerson);

  QStandardItemModel *MailHeaderTable = new QStandardItemModel(ui->Mailtable);
  MailHeaderTable->setColumnCount(5);
  MailHeaderTable->setHorizontalHeaderLabels(QStringList()
                                             << QString::fromLocal8Bit("序号")
                                             << QString::fromLocal8Bit("日期")
                                             << QString::fromLocal8Bit("发件人")
                                             << QString::fromLocal8Bit("收件人")
                                             << QString::fromLocal8Bit("主题"));
  this->ui->Mailtable->setModel(MailHeaderTable);
  this->ui->Mailtable->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
  this->ui->Mailtable->horizontalHeader()->setStretchLastSection(true);
  this->ui->Mailtable->horizontalHeader()->setSectionResizeMode(
      0, QHeaderView::ResizeToContents); // 序号设为固定宽度
  this->ui->Mailtable->setColumnWidth(1, 250);
  this->ui->Mailtable->setColumnWidth(2, 160);
  this->ui->Mailtable->setColumnWidth(3, 160);
  // this->ui->Mailtable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  // //设定为自适应宽度
  this->ui->Mailtable->verticalHeader()->hide();
  this->ui->Mailtable->setSelectionBehavior(
      QAbstractItemView::SelectRows); //整行选中
  // this->ui->Mailtable->resizeColumnsToContents();

  treeview_itemMenu = new QMenu(this);
  QAction *ac = nullptr;
  ac = new QAction(QString::fromLocal8Bit("断开连接"), this);
  treeview_itemMenu->addAction(ac);

  accountManager = new AccountManager;
  addactDialog.setWindowFlags(Qt::WindowCloseButtonHint);
  connect(&addactDialog, &AddactDialog::addact, accountManager,
          &AccountManager::addaccount);
  connect(this, &WwMail::updateActsManager, accountManager,
          &AccountManager::updateManager);
  connect(this, &WwMail::editaccount, accountManager,
          &AccountManager::editaccount);
  connect(accountManager, &AccountManager::clearcomboBox, this,
          &WwMail::clearcomboBox);
  connect(accountManager, &AccountManager::additemcomboBox, this,
          &WwMail::additemcomboBox);
  connect(this, &WwMail::saveaccounts, accountManager,
          &AccountManager::saveaccounts);

  connect(accountManager, &AccountManager::createimapThread, this,
          &WwMail::createimapThread);
  connect(accountManager, &AccountManager::updateimapThread, this,
          &WwMail::updateimapThread);
  connect(accountManager, &AccountManager::destroyimapThread, this,
          &WwMail::destoryimapThread);
  accountManager->initialize();
  emit updateActsManager(); //更新一次帐户管理器，确保信息同步
  on_action_R_triggered();  //开启所有imap连接
}

WwMail::~WwMail() {
  emit saveaccounts();                        //退出之前先保存信息
  for (int i = 0; i < imapList.size(); i++) { //退出所有子线程
    imapList.at(i)->quit();
    imapList.at(i)->wait();
    delete imapList.at(i);
  }
  qDebug() << "~Thread";
  for (int i = 0; i < emlWindow.size(); i++) {
    delete emlWindow.at(i);
  }
  for(int i=0;i<smtpList.size();i++){
      delete smtpList.at(i);
    }
  qDebug() << "~emlWindow";
  delete accountManager;
  delete ui;
}

void WwMail::timerupdate() //状态栏显示本地时间
{
  QDateTime time = QDateTime::currentDateTime();
  QString text = QString::fromLocal8Bit("本地时间: ");
  text += time.toString("yyyy-MM-dd hh:mm:ss");
  this->permanent->setText(text);
}

void WwMail::on_action_M_triggered() //打开邮件帐户管理器
{
  emit updateActsManager();
  accountManager->show();
}

void WwMail::on_action_L_triggered() //打开帐户添加窗口
{
  addactDialog.setModal(true);
  addactDialog.show();
}

void WwMail::on_pushButton_6_clicked() //获取当前选择的帐户序号
{
  emit editaccount(ui->comboBox->currentIndex());
  accountManager->show();
}

void WwMail::clearcomboBox() {
  ui->comboBox->clear();
  ui->pushButton_6->setEnabled(false);
}

void WwMail::additemcomboBox(QString useraccount) {
  ui->pushButton_6->setEnabled(true);
  ui->comboBox->addItem(useraccount);
}

void WwMail::createimapThread(AccountInfo account) {
  imapThread *newThread = new imapThread(account, this);
  imapList << newThread;
  qDebug() << "Created New Thread! GUI-Thread pid: "
           << QThread::currentThreadId();
  newThread->start();
  newThread->imap->moveToThread(newThread);
  connect(newThread, &imapThread::errorMsg, this, &WwMail::criticalMessageBox);
  connect(this, &WwMail::updateimapact, newThread, &imapThread::setimapact);
  connect(newThread->imap, &iMap::errorMsg, this, &WwMail::criticalMessageBox);
  connect(newThread->imap, &iMap::warningMsg, this, &WwMail::warningMessageBox);
  connect(newThread, &imapThread::setimapAccount, newThread->imap,
          &iMap::setAccount);
  connect(this, &WwMail::imapConnect, newThread->imap,
          &iMap::startConnect); //完成不同线程之间的信号连接
  connect(newThread->imap, &iMap::addMailFolderlist, this,
          &WwMail::addMailFolderView);
  connect(this, &WwMail::rqstimapHeaderList, newThread->imap,
          &iMap::getHeaderList);
  connect(newThread->imap, &iMap::addMailHeaderlist, this,
          &WwMail::addMailHeaderView);
  connect(newThread->imap, &iMap::StartProgressDialog, this,
          &WwMail::StartShowProgressdialog);
  connect(newThread->imap, &iMap::SetProgress, this, &WwMail::SetProgress);
  connect(newThread->imap, &iMap::CloseProgressDialog, this,
          &WwMail::CloseProgressdialog);
  connect(this, &WwMail::rqstimapBody, newThread->imap, &iMap::getBody);
  connect(newThread->imap, &iMap::CreateEmlWindow, this,
          &WwMail::CreateNewEmlWindow);
}

void WwMail::updateimapThread(AccountInfo account) {
  for (int i = 0; i < imapList.size(); i++) {
    if (imapList.at(i)->getAccountname() == account.accountname) {
      imapList.at(i)->setAccount(account);
      return;
    }
  }
  qDebug() << "Can\'t find the thread！";
}

void WwMail::destoryimapThread(AccountInfo account) {
  for (int i = 0; i < imapList.size(); i++) { //搜索该线程
    if (imapList.at(i)->getAccountname() == account.accountname) {
      imapList.at(i)->quit();
      imapList.at(i)->wait();
      delete imapList.at(i);
      imapList.removeAt(i);
      removeMailBox(account.accountname); //从TreeView中去除
      return;
    }
  }
  qDebug() << "Can\'t find the thread！";
}

void WwMail::criticalMessageBox(QString msg) {
  QMessageBox::critical(0, QString::fromLocal8Bit("错误！"), msg,
                        QMessageBox::Yes);
  emit imapConnect(); //重新连接
  QStandardItemModel *root =
      qobject_cast<QStandardItemModel *>(ui->Mailtable->model());
  for (int i = 0; i < root->rowCount();) { //先清除原有条目
    root->removeRow(i);
  }
  root = qobject_cast<QStandardItemModel *>(ui->treeView->model());
  for (int i = 0; i < root->rowCount();) { //先清除原有条目
    root->removeRow(i);
  }
}

void WwMail::warningMessageBox(QString msg) {
  QMessageBox::warning(0, QString::fromLocal8Bit("警告！"), msg,
                       QMessageBox::Yes);
}

void WwMail::informationMessageBox(QString msg)
{
  QMessageBox::information(0,QString::fromLocal8Bit("提示！"),msg,QMessageBox::Yes);
}

void WwMail::addMailFolderView(QString useraccount,
                               QStringList mailFolderlist) {
  QStandardItem *item = new QStandardItem(useraccount);
  QStandardItemModel *root =
      qobject_cast<QStandardItemModel *>(ui->treeView->model());
  removeMailBox(useraccount); //先移除重复项
  root->appendRow(item);
  for (int i = 0; i < mailFolderlist.size(); i++) {
    item->appendRow(new QStandardItem(mailFolderlist.at(i)));
  }
}

void WwMail::removeMailBox(QString useraccount) {
  QStandardItemModel *root =
      qobject_cast<QStandardItemModel *>(ui->treeView->model());
  for (int i = 0; i < root->rowCount();) {
    if (root->item(i)->text() == useraccount) {
      qDebug() << useraccount;
      root->removeRow(i); //删除重复项,会导致rowCount--
      ui->treeView->update();
    } else
      i++;
  }
}

void WwMail::addMailHeaderView(const QList<MimeData> &MimeList) {
  QStandardItemModel *root =
      qobject_cast<QStandardItemModel *>(ui->Mailtable->model());
  for (int i = 0; i < root->rowCount();) { //先清除原有条目
    root->removeRow(i);
  }
  for (int i = 0; i < MimeList.size(); i++) {
    root->setItem(i, 0, new QStandardItem(QString::number(i + 1, 10)));
    root->item(i, 0)->setTextAlignment(Qt::AlignCenter);
    root->setItem(i, 1, new QStandardItem(MimeList.at(i).getDate()));
    root->setItem(i, 2, new QStandardItem(MimeList.at(i).getFrom()));
    root->setItem(i, 3, new QStandardItem(MimeList.at(i).getTo()));
    root->setItem(i, 4, new QStandardItem(MimeList.at(i).getSubject()));

    //      root->appendRow(item);
  }
  // this->ui->listView->update();
}

void WwMail::StartShowProgressdialog() {
  this->Progressdialog = new QProgressDialog(this);
  Progressdialog->setWindowTitle(QString::fromLocal8Bit("接收进度"));
  Progressdialog->setFixedWidth(this->width() / 2);
  Progressdialog->setFixedHeight(100);
  Progressdialog->setWindowFlags(windowFlags() & ~Qt::WindowCloseButtonHint);
  Progressdialog->setCancelButton(0);
  Progressdialog->setModal(true);
  Progressdialog->setLabelText(QString::fromLocal8Bit("获取数据中..."));
  Progressdialog->setMaximum(1);
  Progressdialog->setValue(0);
  this->Progressdialog->show();
}

void WwMail::SetProgress(qint32 value, qint32 max) {
  this->Progressdialog->setMaximum(max);
  this->Progressdialog->setValue(value);
}

void WwMail::CloseProgressdialog() {
  this->Progressdialog->hide();
  delete this->Progressdialog;
}

void WwMail::CreateNewEmlWindow(const MimeData &eml, const iMap *imapObject) {
  emlBrower *newEml = new emlBrower();
  connect(newEml, &emlBrower::deleteMail, imapObject, &iMap::imapDelete);
  connect(newEml, &emlBrower::reply, this, &WwMail::reply);
  this->emlWindow << newEml;
  newEml->setData(eml);
  newEml->show();
}

void WwMail::reply(const QString &From, const QString &To,
                   const QString &Subject, const QString Content) {
  bool find = 0;
  for (int i = 0; i < ui->comboBox->count(); i++) {
    if (From.contains(ui->comboBox->itemText(i))) {
      ui->comboBox->setCurrentIndex(i);
      find = 1;
    }
  }
  if (!find)
    warningMessageBox(
        QString::fromLocal8Bit("未发现发送帐号，请登录后再回复！"));
  else {
    ui->lineEdit->setText(To);
    ui->lineEdit_2->setText(Subject);
    ui->textEdit->setText(Content);
    ui->tabWidget->setCurrentIndex(1);
    }
}

void WwMail::ProgressBar_send(qint32 s, qint32 m)
{
  ui->progressBar->setMaximum(m);
  ui->progressBar->setValue(s);
}

void WwMail::on_action_R_triggered() //重新连接所有imap
{
  emit updateimapact(); //更新帐户信息
  emit
  imapConnect(); //不同线程之间的通信要使用信号和槽来完成，使用xx.xx或xx->xx来调用，依旧是在调用该函数的线程中执行
  QStandardItemModel *root =
      qobject_cast<QStandardItemModel *>(ui->Mailtable->model());
  for (int i = 0; i < root->rowCount();) { //先清除原有条目
    root->removeRow(i);
  }
}

void WwMail::on_treeView_customContextMenuRequested(
    const QPoint &pos) //右击菜单
{
  qDebug() << pos;
  treeview_itemMenu->exec(QCursor::pos());
}

void WwMail::on_treeView_doubleClicked(const QModelIndex &index) {
  QStandardItemModel *root =
      qobject_cast<QStandardItemModel *>(ui->treeView->model());
  if (index.parent().row() >= 0) {
    emit rqstimapHeaderList(root->item(index.parent().row())->text(),
                            index.row());
    this->ListMailAccount = root->item(index.parent().row())->text();
  }
}

void WwMail::on_comboBox_currentIndexChanged(const QString &arg1) {
  qDebug() << arg1;
}

void WwMail::addItemToRecentContactPersonList(
    const QList<MimeData> &SendMimeData) {

  QStandardItemModel *root =
      qobject_cast<QStandardItemModel *>(ui->listView->model());
  root->clear(); //先清除原有条目
  for (int i = 0; i < SendMimeData.size(); i++) {
    QStandardItem *item = new QStandardItem(SendMimeData.at(i).getTo());
    root->appendRow(item);
  }
}

void WwMail::on_pushButton_5_clicked() //添加附件
{
  ui->label->show();
  ui->listView_2->show();
  QFileDialog *fileDialog = new QFileDialog(this);
  fileDialog->setWindowTitle(QString::fromLocal8Bit("选择文件"));
  fileDialog->setDirectory(".");
  if (fileDialog->exec() == QDialog::Accepted) {
    for (int i = 0; i < fileDialog->selectedFiles().size(); i++) {
      QString path = fileDialog->selectedFiles().at(i);
      QMessageBox::information(0, QString::fromLocal8Bit("Path"),
                               QString::fromLocal8Bit("You selected ") + path);
    }
  } else {
    QMessageBox::information(
        0, QString::fromLocal8Bit("Path"),
        QString::fromLocal8Bit("You didn't select any files."));
  }
  QMessageBox::information(0,QString::fromLocal8Bit("However!"),QString::fromLocal8Bit("这是一个待实现的feature/(ㄒoㄒ)/~~"));
}

void WwMail::on_Mailtable_doubleClicked(const QModelIndex &index) {
  emit rqstimapBody(this->ListMailAccount, index.row());
}

void WwMail::on_pushButton_3_clicked() {
  if (ui->lineEdit_3->isEnabled()) {
    ui->pushButton_3->setText(QString::fromLocal8Bit("添加抄送"));
    ui->lineEdit_3->setEnabled(false);
    ui->lineEdit_3->hide();
    ui->label_12->hide();
  } else {
    ui->lineEdit_3->clear();
    ui->lineEdit_3->setEnabled(true);
    ui->label_12->show();
    ui->lineEdit_3->show();
    ui->pushButton_3->setText(QString::fromLocal8Bit("取消抄送"));
  }
}

void WwMail::on_pushButton_4_clicked()
{
  if (ui->lineEdit_4->isEnabled()) {
    ui->pushButton_4->setText(QString::fromLocal8Bit("添加密送"));
    ui->lineEdit_4->setEnabled(false);
    ui->lineEdit_4->hide();
    ui->label_13->hide();
  } else {
    ui->lineEdit_4->clear();
    ui->lineEdit_4->setEnabled(true);
    ui->label_13->show();
    ui->lineEdit_4->show();
    ui->pushButton_4->setText(QString::fromLocal8Bit("取消密送"));
  }
}

void WwMail::on_pushButton_9_clicked()
{
  smtpThread* s=new smtpThread(this);
  smtpList<<s;
  QRegularExpression rx("[a-zA-Z0-9]+@[a-zA-Z0-9]+(\\.[a-zA-Z0-9]+)+");
  QRegularExpressionMatch match;
  QString str =ui->lineEdit->text();
  QStringList strlist;
  match=rx.match(str);
  while(match.hasMatch()){
      strlist<<match.captured(0);
      match=rx.match(str.remove(match.captured(0)));
    }
  s->To=strlist;
  s->Subject=ui->lineEdit_2->text();
  s->BBCname=ui->lineEdit_5->text();

  str=ui->lineEdit_3->text();
  strlist.clear();
  match=rx.match(str);
  while(match.hasMatch()){
      strlist<<match.captured(0);
      match=rx.match(str.remove(match.captured(0)));
    }
  s->CCList=strlist;

  str=ui->lineEdit_4->text();
  strlist.clear();
  match=rx.match(str);
  while(match.hasMatch()){
      strlist<<match.captured(0);
      match=rx.match(str.remove(match.captured(0)));
    }
  s->BCCList=strlist;

  s->CCModel=ui->lineEdit_3->isEnabled();
  qDebug()<<"CCmodel"<<s->CCModel;
  s->BCCmodel=ui->lineEdit_4->isEnabled();
  s->Content=ui->textEdit->toPlainText();
  s->act=this->accountManager->findaccount(ui->comboBox->currentText());
  switch(ui->comboBox_2->currentIndex()){
    case 0:
      s->textmodel=plain;
      break;
    case 1:
      s->textmodel=html;
      break;
    case 2:
      s->textmodel=rtf;
      break;
    }
  connect(s->smtp,&SMTP::Msg,this,&WwMail::warningMessageBox);
  connect(s->smtp,&SMTP::iMsg,this,&WwMail::informationMessageBox);
  connect(s->smtp,&SMTP::progress,this,&WwMail::ProgressBar_send);
     qDebug()<<ui->comboBox_2->currentIndex();
  s->smtp->moveToThread(s);
  s->start();
}

void WwMail::on_pushButton_8_clicked()
{
  QFileDialog *fileDialog = new QFileDialog(this);
  fileDialog->setWindowTitle(QString::fromLocal8Bit("选择文件"));
  fileDialog->setDirectory(".");
  fileDialog->selectFile("newMail.dft");
  if (fileDialog->exec() == QDialog::Accepted) {
      QString path = fileDialog->selectedFiles().at(0);
      QFile file(path);
      if(file.open(QIODevice::WriteOnly)){
          QDataStream out(&file);
          out<<ui->lineEdit->text();
          out<<ui->lineEdit_2->text();
          out<<ui->lineEdit_5->text();
          out<<ui->textEdit->toPlainText();
          file.close();
          informationMessageBox(QString::fromLocal8Bit("保存成功！"));
        }
  }
}

void WwMail::on_pushButton_7_clicked()
{
  QFileDialog *fileDialog = new QFileDialog(this);
  fileDialog->setWindowTitle(QString::fromLocal8Bit("选择文件"));
  fileDialog->setDirectory(".");
  fileDialog->selectFile("newMail.dft");
  if (fileDialog->exec() == QDialog::Accepted) {
      QString path = fileDialog->selectedFiles().at(0);
      qDebug()<<path;
      QFile file(path);
      if(file.open(QIODevice::ReadOnly)){
          QDataStream in(&file);
          QString s;
          in>>s;
          ui->lineEdit->setText(s);
          in>>s;
          ui->lineEdit_2->setText(s);
          in>>s;
          ui->lineEdit_5->setText(s);
          in>>s;
          ui->textEdit->setText(s);
          file.close();
          informationMessageBox(QString::fromLocal8Bit("读取成功！"));
        }
  }
}

void WwMail::on_action_A_triggered()
{
    QMessageBox::information(0,QString::fromLocal8Bit("关于"),
                             QString::fromLocal8Bit("本产品由华中科技大学计算机1401班覃宇骁&朱珺合作开发完成！如有疑问或者bug，请联系邮箱382825415@qq.com"),
                             QMessageBox::Ok);
}
