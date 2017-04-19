#include "clientwindow.h"
#include "ui_clientwindow.h"

ClientWindow::ClientWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClientWindow)
{
    ui->setupUi(this);
    Dialog_login w(this);
    w.setModal(true); //设置为模态对话框，禁止在登陆之前与主窗口进行交互
    w.show();
    w.move((QApplication::desktop()->width()-w.width())/2,(QApplication::desktop()->height()-w.height())/2);//调整窗口位到屏幕中央
    auto ret=w.exec();
    if(ret==QDialog::Rejected) loginsuccess=false; //如果拒绝登入，则设定登陆验证为失败
    else if(ret==QDialog::Accepted) {
        iMap imap; //尝试建立imap连接
        imap.setHost("imap.qq.com");
        imap.setPort(143);
        loginsuccess=imap.login(); //进行登陆验证
    }
}

bool ClientWindow::isLogin()
{
    return loginsuccess;
}

ClientWindow::~ClientWindow()
{
    delete ui;
}

