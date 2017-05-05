#include "accountmanager.h"
#include "ui_accountmanager.h"

AccountManager::AccountManager(QWidget *parent)
    : QWidget(parent), ui(new Ui::AccountManager) {
  ui->setupUi(this);
  accounts.clear();            //清空帐户链
  QFile file("accounts.data"); //如果已有帐户，则自动读取
  QFileInfo info(file);
  if (info.exists()) { //判断文件是否存在
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);
    int accountsNum = 0;
    in >> accountsNum;
    for (int i = 0; i < accountsNum; i++) {
      AccountInfo act;
      in >> act.accountname;
      in >> act.username;
      in >> act.userpassword;
      in >> act.imapfield;
      in >> act.imapport;
      in >> act.smtpfield;
      in >> act.smtpport;
      accounts.append(act);
    }
    file.close();
    QMessageBox::warning(0, QObject::tr("提示！"),
                         QObject::tr("已从文件加载帐户信息！(*^__^*) "),
                         QMessageBox::Yes); //警告对话框
  }
  ui->lineEdit_3->setValidator(
      new QIntValidator(1, 65535, this)); //限定端口号输入范围
  ui->lineEdit_4->setValidator(new QIntValidator(1, 65535, this));
}

AccountManager::~AccountManager() { delete ui; }

void AccountManager::addaccount(QString username, QString userpassword) {
  AccountInfo newAccount;
  if (username.contains(
          "@")) { //如果输入的是完整的用户名xxx@xxx.com 则按照@拆分
    for (int i = 0; i < accounts.size(); i++) { //遍历查重
      if (accounts.at(i).accountname == username) {
        QMessageBox::critical(0, QObject::tr("错误！"),
                              QObject::tr("帐户信息已录入！请勿重复添加！"),
                              QMessageBox::Yes);
        return;
      }
    }
    QStringList strlist = username.split("@");
    qDebug() << strlist;
    if (2 == strlist.size()) { //如果不是两部分，则输入格式有误
      newAccount.accountname = username;
      newAccount.username = strlist.at(0);
      newAccount.userpassword = userpassword;
      // http://www.cnblogs.com/shangdawei/p/4305989.html常用邮箱地址(未验证)
      if (strlist.at(1).toLower() == "qq.com") { // qq邮箱
        newAccount.imapfield = "imap.qq.com";
        newAccount.imapport = 143;
        newAccount.smtpfield = "smtp.qq.com";
        newAccount.smtpport = 25;
      } else if (strlist.at(1).toLower() == "163.com") { // 163邮箱
        newAccount.imapfield = "imap.163.com";
        newAccount.imapport = 143;
        newAccount.smtpfield = "smtp.163.com";
        newAccount.smtpport = 25;
      } else if (strlist.at(1).toLower() == "126.com") { // 126邮箱
        newAccount.imapfield = "imap.126.com";
        newAccount.imapport = 143;
        newAccount.smtpfield = "smtp.126.com";
        newAccount.smtpport = 25;
      } else if (strlist.at(1).toLower() == "sina.com") { // sina邮箱
        newAccount.imapfield = "imap.sina.com";
        newAccount.imapport = 143;
        newAccount.smtpfield = "smtp.sina.com";
        newAccount.smtpport = 25;
      } else if (strlist.at(1).toLower() == "netease.com") { // 网易邮箱
        newAccount.imapfield = "imap.netease.com";
        newAccount.imapport = 143;
        newAccount.smtpfield = "smtp.netease.com";
        newAccount.smtpport = 25;
      } else { //未知邮箱,设为默认值
        newAccount.imapfield = "imap." + strlist.at(1).toLower();
        newAccount.imapport = 143;
        newAccount.smtpfield = "smtp." + strlist.at(1).toLower();
        newAccount.smtpport = 25;
        QMessageBox::warning(
            0, QObject::tr("警告！"),
            QObject::tr(
                "邮箱类型未知！如无法连接请在帐号管理中手动配置服务器！"),
            QMessageBox::Yes);
      }
      accounts.append(newAccount);
      qDebug() << "account num: " + QString::number(accounts.size(), 10);
      QMessageBox::warning(0, QObject::tr("提示！"),
                           QObject::tr("帐号已成功录入！(*^__^*)"),
                           QMessageBox::Yes);
      updateManager();
      return;
    }
  }
  QMessageBox::warning(0, QObject::tr("警告！"),
                       QObject::tr("用户名输入有误！"), QMessageBox::Yes);
}

void AccountManager::updateManager() {
  ui->comboBox->clear();
  ui->lineEdit->clear();
  ui->lineEdit_2->clear();
  ui->lineEdit_3->clear();
  ui->lineEdit_4->clear();
  ui->lineEdit_5->clear();
  emit clearcomboBox(); //使主界面下拉菜单同步更新
  if (accounts.size() == 0) {
    ui->pushButton_3->setEnabled(false);
    return;
  }
  ui->pushButton_3->setEnabled(true);
  for (int i = 0; i < accounts.size(); i++) {
    ui->comboBox->addItem(accounts.at(i).accountname);
    emit additemcomboBox(accounts.at(i).accountname);
  }
}

void AccountManager::editaccount(int index) {
  this->on_comboBox_currentIndexChanged(index);
}

void AccountManager::saveaccounts()
{
  this->on_pushButton_clicked();
}

qint32 AccountManager::findaccount(QString accountname) {
  for (int i = 0; i < accounts.size(); i++) {
    if (accounts.at(i).accountname == accountname)
      return i;
  }
  return -1;
}

void AccountManager::on_pushButton_clicked() //保存
{
  if (ui->checkBox->isChecked()) {
    QFile file("accounts.data");
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    out << accounts.size(); //保存帐户数量
    for (int i = 0; i < accounts.size(); i++) {
      out << accounts.at(i).accountname;
      out << accounts.at(i).username;
      out << accounts.at(i).userpassword;
      out << accounts.at(i).imapfield;
      out << accounts.at(i).imapport;
      out << accounts.at(i).smtpfield;
      out << accounts.at(i).smtpport;
    }
    file.close();
    QMessageBox::warning(0, QObject::tr("提示！"), QObject::tr("本地帐户信息保存成功！(*^__^*) ……"),
                         QMessageBox::Yes); //警告对话框
  }

  this->hide();
}

void AccountManager::on_comboBox_currentIndexChanged(int index) {
  if (index < accounts.size() && index >= 0) {
    ui->comboBox->setCurrentIndex(index);
    ui->lineEdit->setText(accounts.at(index).userpassword);
    ui->lineEdit_2->setText(accounts.at(index).imapfield);
    ui->lineEdit_3->setText(QString::number(accounts.at(index).imapport, 10));
    ui->lineEdit_4->setText(accounts.at(index).smtpfield);
    ui->lineEdit_5->setText(QString::number(accounts.at(index).smtpport, 10));
  }
}

void AccountManager::on_pushButton_3_clicked() //删除帐户
{
  qint32 index = ui->comboBox->currentIndex();
  if (index < accounts.size() && index >= 0) {
    auto ret = QMessageBox::warning(
        0, QObject::tr("警告！"), QObject::tr("您确定要删除该帐户？"),
        QMessageBox::Yes | QMessageBox::Cancel); //警告对话框
    if (ret == QMessageBox::Yes) {
      accounts.removeAt(index);
      QMessageBox::warning(0, QObject::tr("提示！"),
                           QObject::tr("删除成功！(ˇˍˇ) "),
                           QMessageBox::Yes); //警告对话框
      updateManager();
    }
  }
}
