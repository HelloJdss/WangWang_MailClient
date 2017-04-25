#include "dialog_login.h"
#include "ui_dialog_login.h"

Dialog_login::Dialog_login(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::Dialog_login)
{
    ui->setupUi(this);
    ui->lineEdit_2->setEchoMode(QLineEdit::Password); //隐藏密码显示
}

const QString Dialog_login::getUSERNAME() { return this->USERNAME; }

const QString Dialog_login::getPASSWORD() { return this->PASSWORD; }

const QString Dialog_login::getServerfield() { return this->Serverfield; }

Dialog_login::~Dialog_login() { delete ui; }

void Dialog_login::on_pushButton_clicked()
{
    //读取字符串内容
    this->USERNAME = ui->lineEdit->text();
    this->PASSWORD = ui->lineEdit_2->text();
    qDebug() << USERNAME;
    if (this->USERNAME.contains("@")) {
        //如果输入的是完整的用户名xxx@xxx.com 则按照@拆分
        QStringList strlist = this->USERNAME.split("@");
        qDebug() << strlist;
        if (2 == strlist.size()) { //如果不是两部分，则输入格式有误
            this->USERNAME = strlist.at(0);
            this->Serverfield = strlist.at(1);
            accept();
            return;
        }
        QMessageBox::warning(this, QObject::tr("警告！"), tr("用户名输入错误！"),
            QMessageBox::Yes); //警告对话框
    }
    reject();
}

void Dialog_login::on_pushButton_2_clicked() { reject(); }
