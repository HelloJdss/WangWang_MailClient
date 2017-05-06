#include "wwmail.h"
#include "ui_wwmail.h"
#include <QDateTime>
#include <QTimer>
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
  ui->splitter_3->setStretchFactor(0,7);
  ui->splitter_3->setStretchFactor(1,3);
  ui->pushButton_6->setEnabled(false);
  accountManager = new AccountManager;
  connect(&addactDialog,&AddactDialog::addact,accountManager,&AccountManager::addaccount);
  connect(this,&WwMail::updateActsManager,accountManager,&AccountManager::updateManager);
  connect(this,&WwMail::editaccount,accountManager,&AccountManager::editaccount);
  connect(accountManager,&AccountManager::clearcomboBox,this,&WwMail::clearcomboBox);
  connect(accountManager,&AccountManager::additemcomboBox,this,&WwMail::additemcomboBox);
  connect(this,&WwMail::saveaccounts,accountManager,&AccountManager::saveaccounts);

  connect(accountManager,&AccountManager::createimap,this,&WwMail::createimapThread);
  connect(accountManager,&AccountManager::destroyimap,this,&WwMail::destoryimapThread);
  accountManager->initialize();
  emit updateActsManager(); //更新一次帐户管理器，确保信息同步
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
  QString text = "本地时间: ";
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

void WwMail::on_pushButton_6_clicked()
{
    //获取当前选择的帐户序号
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
  qDebug()<<"已添加新imap线程！GUI ID: "<<QThread::currentThreadId();
  connect(newThread,&imapThread::errorMsg,this,&WwMail::criticalMessageBox);
  newThread->start();
}

void WwMail::destoryimapThread(AccountInfo account)
{
  for(int i=0;i<imapList.size();i++){//搜索该线程
      if(imapList.at(i)->getAccountname()==account.accountname){
          imapList.at(i)->quit();
          imapList.at(i)->wait();
          delete imapList.at(i);
          imapList.removeAt(i);
          return;
        }
    }
  qDebug()<<"未找到线程实例！";
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
