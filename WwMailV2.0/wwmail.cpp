#include "wwmail.h"
#include "ui_wwmail.h"
#include <QDateTime>
#include <QTimer>
#include <QStringListModel>
#include <QMenu>
#include <QFileDialog>
#include <QAction>
#define _version "V2.0"
WwMail::WwMail(QWidget *parent) : QMainWindow(parent), ui(new Ui::WwMail)
{
  ui->setupUi(this);
  QString version = _version;
  QString Welcome = "欢迎使用汪汪邮箱 " + version + " (*^__^*) ~~";
  ui->statusBar->showMessage(Welcome);
  //设定当前时钟
  {
    this->permanent = new QLabel(this);
    QTimer *localtimer = new QTimer(this);
    connect(localtimer, &QTimer::timeout, this, &WwMail::timerupdate);
    ui->statusBar->addPermanentWidget(this->permanent);
    localtimer->start(1000);
  }
  ui->splitter->setStretchFactor(0,2);
  ui->splitter->setStretchFactor(1,8);
  ui->splitter_3->setStretchFactor(0,7);
  ui->splitter_3->setStretchFactor(1,3);
  ui->pushButton_6->setEnabled(false);
  QStandardItemModel* MailFolderTree = new QStandardItemModel(ui->treeView); //父对象为ui->treeView，智能释放
  MailFolderTree->setHorizontalHeaderLabels(QStringList()<<QString(tr("邮箱列表")));
  this->ui->treeView->header()->setDefaultAlignment(Qt::AlignCenter);
  this->ui->treeView->setModel(MailFolderTree);

  QStandardItemModel* RecentContactPerson = new QStandardItemModel(ui->listView);
  RecentContactPerson->setHorizontalHeaderLabels(QStringList()<<QString(tr("双击帐号信息添加至收件人(*^__^*)")));
  this->ui->listView->setModel(RecentContactPerson);

  QStandardItemModel* MailHeaderTable = new QStandardItemModel(ui->Mailtable);
  MailHeaderTable->setColumnCount(5);
  MailHeaderTable->setHorizontalHeaderLabels(QStringList()<<QString(tr("序号"))
                                             << QString(tr("日期"))
                                             << QString(tr("发件人"))
                                             << QString(tr("收件人"))
                                             << QString(tr("主题")));
  this->ui->Mailtable->setModel(MailHeaderTable);
  this->ui->Mailtable->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
  this->ui->Mailtable->horizontalHeader()->setStretchLastSection(true);
  this->ui->Mailtable->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents); // 序号设为固定宽度
  this->ui->Mailtable->setColumnWidth(1,230);
  this->ui->Mailtable->setColumnWidth(2,160);
  this->ui->Mailtable->setColumnWidth(3,160);
  //this->ui->Mailtable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //设定为自适应宽度
  this->ui->Mailtable->verticalHeader()->hide();
  this->ui->Mailtable->setSelectionBehavior(QAbstractItemView::SelectRows); //整行选中
  //this->ui->Mailtable->resizeColumnsToContents();


  treeview_itemMenu = new QMenu(this);
  QAction* ac = nullptr;
  ac = new QAction(QString(tr("断开连接")),this);
  treeview_itemMenu->addAction(ac);

  accountManager = new AccountManager;
  addactDialog.setWindowFlags(Qt::WindowCloseButtonHint);
  connect(&addactDialog,&AddactDialog::addact,accountManager,&AccountManager::addaccount);
  connect(this,&WwMail::updateActsManager,accountManager,&AccountManager::updateManager);
  connect(this,&WwMail::editaccount,accountManager,&AccountManager::editaccount);
  connect(accountManager,&AccountManager::clearcomboBox,this,&WwMail::clearcomboBox);
  connect(accountManager,&AccountManager::additemcomboBox,this,&WwMail::additemcomboBox);
  connect(this,&WwMail::saveaccounts,accountManager,&AccountManager::saveaccounts);

  connect(accountManager,&AccountManager::createimapThread,this,&WwMail::createimapThread);
  connect(accountManager,&AccountManager::updateimapThread,this,&WwMail::updateimapThread);
  connect(accountManager,&AccountManager::destroyimapThread,this,&WwMail::destoryimapThread);
  accountManager->initialize();
  emit updateActsManager(); //更新一次帐户管理器，确保信息同步
  on_action_R_triggered(); //开启所有imap连接
}

WwMail::~WwMail()
{
  emit saveaccounts();//退出之前先保存信息
  for(int i=0;i<imapList.size();i++){ //退出所有子线程
      imapList.at(i)->quit();
      imapList.at(i)->wait();
      delete imapList.at(i);
    }
  delete accountManager;
  delete ui;
}

void WwMail::timerupdate() //状态栏显示本地时间
{
  QDateTime time = QDateTime::currentDateTime();
  QString text = tr("本地时间: ");
  text += time.toString("yyyy-MM-dd hh:mm:ss");
  this->permanent->setText(text);
}

void WwMail::on_action_M_triggered()  //打开邮件帐户管理器
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

void WwMail::clearcomboBox()
{
  ui->comboBox->clear();
  ui->pushButton_6->setEnabled(false);
}

void WwMail::additemcomboBox(QString useraccount)
{
  ui->pushButton_6->setEnabled(true);
  ui->comboBox->addItem(useraccount);
}

void WwMail::createimapThread(AccountInfo account)
{
  imapThread* newThread = new imapThread(account,this);
  imapList<<newThread;
  qDebug()<<"Created New Thread！GUI-Thread pid: "<<QThread::currentThreadId();
  newThread->start();
  newThread->imap->moveToThread(newThread);
  connect(newThread,&imapThread::errorMsg,this,&WwMail::criticalMessageBox);
  connect(this,&WwMail::updateimapact,newThread,&imapThread::setimapact);
  connect(newThread->imap,&iMap::errorMsg,this,&WwMail::criticalMessageBox);
  connect(newThread->imap,&iMap::warningMsg,this,&WwMail::warningMessageBox);
  connect(newThread,&imapThread::setimapAccount,newThread->imap,&iMap::setAccount);
  connect(this,&WwMail::imapConnect,newThread->imap,&iMap::startConnect); //完成不同线程之间的信号连接
  connect(newThread->imap,&iMap::addMailFolderlist,this,&WwMail::addMailFolderView);
  connect(this,&WwMail::rqstimapHeaderList,newThread->imap,&iMap::getHeaderList);
  connect(newThread->imap,&iMap::addMailHeaderlist,this,&WwMail::addMailHeaderView);
  connect(newThread->imap,&iMap::StartProgressDialog,this,&WwMail::StartShowProgressdialog);
  connect(newThread->imap,&iMap::SetProgress,this,&WwMail::SetProgress);
  connect(newThread->imap,&iMap::CloseProgressDialog,this,&WwMail::CloseProgressdialog);
  connect(this,&WwMail::rqstimapBody,newThread->imap,&iMap::getBody);
}

void WwMail::updateimapThread(AccountInfo account)
{
  for(int i=0;i<imapList.size();i++){
      if(imapList.at(i)->getAccountname()==account.accountname){
          imapList.at(i)->setAccount(account);
          return;
        }
    }
  qDebug()<<"Can\'t find the thread！";
}

void WwMail::destoryimapThread(AccountInfo account)
{
  for(int i=0;i<imapList.size();i++){//搜索该线程
      if(imapList.at(i)->getAccountname()==account.accountname){
          imapList.at(i)->quit();
          imapList.at(i)->wait();
          delete imapList.at(i);
          imapList.removeAt(i);
          removeMailBox(account.accountname); //从TreeView中去除
          return;
        }
    }
  qDebug()<<"Can\'t find the thread！";
}

void WwMail::criticalMessageBox(QString msg)
{
  QMessageBox::critical(0, QObject::tr("错误！"), msg,
                        QMessageBox::Yes);
}

void WwMail::warningMessageBox(QString msg)
{
  QMessageBox::warning(0, QObject::tr("警告！"), msg,
                       QMessageBox::Yes);
}

void WwMail::addMailFolderView(QString useraccount, QStringList mailFolderlist)
{
  QStandardItem *item = new QStandardItem(useraccount);
  QStandardItemModel* root = qobject_cast<QStandardItemModel*>(ui->treeView->model());
  removeMailBox(useraccount); //先移除重复项
  root->appendRow(item);
  for(int i=0;i<mailFolderlist.size();i++){
      item->appendRow(new QStandardItem(mailFolderlist.at(i)));
    }
}

void WwMail::removeMailBox(QString useraccount)
{
  QStandardItemModel* root = qobject_cast<QStandardItemModel*>(ui->treeView->model());
  for(int i=0;i<root->rowCount();){
      if(root->item(i)->text()==useraccount){
          qDebug()<<useraccount;
          root->removeRow(i); //删除重复项,会导致rowCount--
          ui->treeView->update();
        }
      else i++;
    }
}

void WwMail::addMailHeaderView(const QList<MimeData> &MimeList)
{
  QStandardItemModel* root = qobject_cast<QStandardItemModel*>(ui->Mailtable->model());
  for(int i=0;i<root->rowCount();){//先清除原有条目
      root->removeRow(i);
    }
  for(int i=0;i<MimeList.size();i++){
        root->setItem(i,0,new QStandardItem(QString::number(i+1,10)));
        root->item(i,0)->setTextAlignment(Qt::AlignCenter);
        root->setItem(i,1,new QStandardItem(MimeList.at(i).getDate()));
        root->setItem(i,2,new QStandardItem(MimeList.at(i).getFrom()));
        root->setItem(i,3,new QStandardItem(MimeList.at(i).getTo()));
        root->setItem(i,4,new QStandardItem(MimeList.at(i).getSubject()));

//      root->appendRow(item);
    }
  // this->ui->listView->update();
}

void WwMail::StartShowProgressdialog()
{
  this->Progressdialog = new QProgressDialog(this);
  Progressdialog->setWindowTitle(tr("接收进度"));
  Progressdialog->setFixedWidth(this->width()/2);
  Progressdialog->setFixedHeight(100);
  Progressdialog->setWindowFlags(windowFlags() &~ Qt::WindowCloseButtonHint);
  Progressdialog->setCancelButton(0);
  Progressdialog->setModal(true);
  Progressdialog->setLabelText(tr("获取数据中..."));
  Progressdialog->setMaximum(1);
  Progressdialog->setValue(0);
  this->Progressdialog->show();
}

void WwMail::SetProgress(qint32 value, qint32 max)
{
  this->Progressdialog->setMaximum(max);
  this->Progressdialog->setValue(value);
}

void WwMail::CloseProgressdialog()
{
  this->Progressdialog->hide();
  delete this->Progressdialog;
}

void WwMail::on_action_R_triggered() //重新连接所有imap
{
  emit updateimapact(); //更新帐户信息
  emit imapConnect(); //不同线程之间的通信要使用信号和槽来完成，使用xx.xx或xx->xx来调用，依旧是在调用该函数的线程中执行
}

void WwMail::on_treeView_customContextMenuRequested(const QPoint &pos) //右击菜单
{
  qDebug()<<pos;
  treeview_itemMenu->exec(QCursor::pos());
}

void WwMail::on_treeView_doubleClicked(const QModelIndex &index)
{
  QStandardItemModel* root = qobject_cast<QStandardItemModel*>(ui->treeView->model());
  if(index.parent().row()>=0){
      emit rqstimapHeaderList(root->item(index.parent().row())->text(),index.row());
      this->ListMailAccount=root->item(index.parent().row())->text();
    }
}



void WwMail::on_comboBox_currentIndexChanged(const QString &arg1){
  qDebug()<<arg1;
}

void WwMail::addItemToRecentContactPersonList(const QList<MimeData> &SendMimeData)
{

  QStandardItemModel* root = qobject_cast<QStandardItemModel*>(ui->listView->model());
  root->clear();//先清除原有条目
  for(int i=0;i<SendMimeData.size();i++){
      QStandardItem *item = new QStandardItem(SendMimeData.at(i).getTo());
      root->appendRow(item);
    }
}

void WwMail::on_pushButton_5_clicked() //添加附件
{
  QFileDialog *fileDialog = new QFileDialog(this);
  fileDialog->setWindowTitle(tr("Open File"));
  fileDialog->setDirectory(".");
  if(fileDialog->exec() == QDialog::Accepted) {
      for(int i=0;i<fileDialog->selectedFiles().size();i++){
      QString path = fileDialog->selectedFiles().at(i);
      QMessageBox::information(0, tr("Path"), tr("You selected ") + path);
        }
      } else {
              QMessageBox::information(0, tr("Path"), tr("You didn't select any files."));
      }
}

void WwMail::on_Mailtable_doubleClicked(const QModelIndex &index)
{
    emit rqstimapBody(this->ListMailAccount,index.row());
}
