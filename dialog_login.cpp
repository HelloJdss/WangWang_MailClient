#include "dialog_login.h"
#include "ui_dialog_login.h"

Dialog_login::Dialog_login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_login)
{
    ui->setupUi(this);
    ui->lineEdit_2->setEchoMode(QLineEdit::Password); //隐藏密码显示
}

Dialog_login::~Dialog_login()
{
    delete ui;
}


void Dialog_login::on_pushButton_clicked()
{
    accept();
}

void Dialog_login::on_pushButton_2_clicked()
{
    reject();
}
