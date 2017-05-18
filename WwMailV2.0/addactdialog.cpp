#include "addactdialog.h"
#include <QDebug>
#include <QMessageBox>
#include <QRegExp>
#include <QValidator>
#include "ui_addactdialog.h"

AddactDialog::AddactDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::AddactDialog) {
  ui->setupUi(this);
  this->button4changed = false;
}

AddactDialog::~AddactDialog() { delete ui; }

void AddactDialog::on_pushButton_clicked()  //按下确认
{
  QString username = ui->lineEdit->text();
  qDebug() << "Goingto add: " + username;
  QRegExp nameExp(
      "[a-zA-Z0-9]+@[a-zA-Z0-9]+(\\.[a-zA-Z0-9]+)+");  //必须是标准邮箱名xx@xx.xx类型
  if (nameExp.exactMatch(username)) {
    qDebug() << "Password: " + ui->lineEdit_2->text();
    emit addact(username, ui->lineEdit_2->text());  //发送帐户密码信号
    ui->lineEdit_2->clear();
    return;
  }
  QMessageBox::warning(this, QString::fromLocal8Bit("警告！"),
                       QString::fromLocal8Bit("输入用户名不合法！请重新输入！/(ㄒoㄒ)/~~"),
                       QMessageBox::Yes);
}

void AddactDialog::on_pushButton_3_clicked() { ui->lineEdit->clear(); }

void AddactDialog::on_pushButton_4_clicked() {
  if (button4changed) {
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    ui->pushButton_4->setText("显示");
    button4changed=false;
  } else {
    ui->lineEdit_2->setEchoMode(QLineEdit::Normal);
    ui->pushButton_4->setText("隐藏");
    button4changed=true;
  }
}
