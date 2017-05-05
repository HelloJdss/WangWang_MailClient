#include "wwmail.h"
#include "ui_wwmail.h"
#define _version "V1.0"
#include <QDateTime>
#include <QTimer>
WwMail::WwMail(QWidget *parent) : QMainWindow(parent), ui(new Ui::WwMail) {
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
  connect(&addactDialog,&AddactDialog::addact,&accountManager,&AccountManager::addaccount);
  connect(this,&WwMail::updateActsManager,&accountManager,&AccountManager::updateManager);
  connect(this,&WwMail::editaccount,&accountManager,&AccountManager::editaccount);
  connect(&accountManager,&AccountManager::clearcomboBox,this,&WwMail::clearcomboBox);
  connect(&accountManager,&AccountManager::additemcomboBox,this,&WwMail::additemcomboBox);
  connect(this,&WwMail::saveaccounts,&accountManager,&AccountManager::saveaccounts);
  emit updateActsManager(); //更新一次帐户管理器，确保信息同步
}

WwMail::~WwMail() {
  emit saveaccounts();//退出之前先保存信息
  delete ui; }

void WwMail::timerupdate() {
  QDateTime time = QDateTime::currentDateTime();
  QString text = "本地时间: ";
  text += time.toString("yyyy-MM-dd hh:mm:ss");
  this->permanent->setText(text);
}

void WwMail::on_action_M_triggered()  //打开邮件帐户管理器
{
  emit updateActsManager();
  accountManager.show();
}

void WwMail::on_action_L_triggered() {  //打开帐户添加窗口
  addactDialog.setModal(true);
  addactDialog.show();
}

void WwMail::on_pushButton_6_clicked()
{
    //获取当前选择的帐户序号
  emit editaccount(ui->comboBox->currentIndex());
  accountManager.show();
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
