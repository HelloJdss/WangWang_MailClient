#include "accountmanager.h"
#include "ui_accountmanager.h"

AccountManager::AccountManager(QWidget *parent)
    : QWidget(parent), ui(new Ui::AccountManager) {
  ui->setupUi(this);
}

void AccountManager::initialize() {
  accounts.clear();            //清空帐户链
  QFile file("accounts.data"); //如果已有帐户，则自动读取
  QFileInfo info(file);
  if (info.exists()) { //判断文件是否存在
    if (!file.open(QIODevice::ReadOnly)) {
      qDebug() << file.fileName() << " Read Failed!";
      return;
    }
    QDataStream in(&file);
    int accountsNum = 0;
    in >> accountsNum;
    for (int i = 0; i < accountsNum; i++) {
      AccountInfo act;
      in >> act.accountname;
      in >> act.username;
      QByteArray ps;
      in >> ps;
      QByteArray cipher("FLZX3000cY4yhl9day");//18char
      QByteArray pswd(QByteArray::fromBase64(ps));
      for(int j=0;j<pswd.size();j++){
          pswd[j]=char(int(pswd[j])-int(cipher.at(j%18))); //对密码简单加密
        }
      act.userpassword=pswd;
      in >> act.imapfield;
      in >> act.imapport;
      in >> act.smtpfield;
      in >> act.smtpport;
      accounts.append(act);
      emit createimapThread(act); //请求主线程增加imap连接线程
    }
    file.close();
//    QMessageBox::warning(0, QObject::tr("提示！"),
//                         QObject::tr("已从文件加载帐户信息！(*^__^*) "),
//                         QMessageBox::Yes); //警告对话框
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
        QMessageBox::critical(0, QString::fromLocal8Bit("错误！"),
                              QString::fromLocal8Bit("帐户信息已录入！请勿重复添加！"),
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
            0, QString::fromLocal8Bit("警告！"),
            QString::fromLocal8Bit(
                "邮箱类型未知！如无法连接请在帐号管理中手动配置服务器！"),
            QMessageBox::Yes);
      }
      accounts.append(newAccount);
      QMessageBox::information(0, QString::fromLocal8Bit("提示！"),
                           QString::fromLocal8Bit("帐号已成功录入！(*^__^*)"));
      emit createimapThread(newAccount); //请求主线程增加imap连接线程
      updateManager();
      return;
    }
  }
  QMessageBox::warning(0, QString::fromLocal8Bit("警告！"),
                       QString::fromLocal8Bit("用户名输入有误！"), QMessageBox::Yes);
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
    emit updateimapThread(accounts.at(i));
  }
}

void AccountManager::editaccount(int index) {
  this->on_comboBox_currentIndexChanged(index);
}

void AccountManager::saveaccounts() //退出之前写入文件保存
{
  if (ui->checkBox->isChecked()) {
    QFile file("accounts.data");
    if (file.open(QIODevice::WriteOnly)) {
      QDataStream out(&file);
      out << accounts.size(); //保存帐户数量
      for (int i = 0; i < accounts.size(); i++) {
        out << accounts.at(i).accountname;
        out << accounts.at(i).username;
        QByteArray cipher("FLZX3000cY4yhl9day");//18char
        QByteArray pswd(accounts.at(i).userpassword.toLatin1());
        for(int j=0;j<pswd.size();j++){
            pswd[j]=char(int(pswd[j])+int(cipher.at(j%18))); //对密码简单加密
          }
        out << pswd.toBase64();
        out << accounts.at(i).imapfield;
        out << accounts.at(i).imapport;
        out << accounts.at(i).smtpfield;
        out << accounts.at(i).smtpport;
      }
      file.close();
    } else
      qDebug() << file.fileName() << " Write Failed!";
  }
}

AccountInfo AccountManager::findaccount(QString accountname) {
  for (int i = 0; i < accounts.size(); i++) {
    if (accounts.at(i).accountname == accountname)
      return accounts.at(i);
  }
  return AccountInfo();
}

void AccountManager::on_pushButton_clicked() //保存
{
  int index = ui->comboBox->currentIndex();
  if (index < accounts.size() && index >= 0) {
    if (accounts.at(index).accountname == ui->comboBox->currentText()) {
      accounts[index].userpassword=ui->lineEdit->text();
      accounts[index].imapfield=ui->lineEdit_2->text();
      accounts[index].imapport=ui->lineEdit_3->text().toUShort();
      accounts[index].smtpfield=ui->lineEdit_4->text();
      accounts[index].smtpport=ui->lineEdit_5->text().toUShort();
      QMessageBox::information(0, QString::fromLocal8Bit("提示！"),
                           QString::fromLocal8Bit("保存成功！(*^__^*) ……")); //提示对话框
      updateManager();
      on_comboBox_currentIndexChanged(index);
      return;
    }
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
        0, QString::fromLocal8Bit("警告！"), QString::fromLocal8Bit("您确定要删除该帐户？"),
        QMessageBox::Yes | QMessageBox::Cancel); //警告对话框
    if (ret == QMessageBox::Yes) {
      emit destroyimapThread(accounts.at(index)); //请求主进程销毁imap连接线程
      accounts.removeAt(index);
      QMessageBox::information(0, QString::fromLocal8Bit("提示！"),
                           QString::fromLocal8Bit("删除成功！~(T_T)~")); //提示对话框
      updateManager();
    }
  }
}
