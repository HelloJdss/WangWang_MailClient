#include "clientwindow.h"
#include "ui_clientwindow.h"
#include <QLabel>
#include <QTimer>
#define _version "0.1"

ClientWindow::ClientWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::ClientWindow)
{
    ui->setupUi(this);
    ui->WriteMail->hide(); //隐藏
    ui->WriteMail->setReadOnly(true); //禁止写入
    Dialog_login Login_dialog(this);
    Login_dialog.setModal(
        true); //设置为模态对话框，禁止在登陆之前与主窗口进行交互
    Login_dialog.show();
    Login_dialog.move(
        (QApplication::desktop()->width() - Login_dialog.width()) / 2,
        (QApplication::desktop()->height() - Login_dialog.height()) / 2); //调整窗口位到屏幕中央
    auto ret = Login_dialog.exec();
    if (ret == QDialog::Rejected)
        loginsuccess = false; //如果拒绝登入，则设定登陆验证为失败
    else if (ret == QDialog::Accepted) {
        imap.setHost("imap.qq.com");
        imap.setPort(143);
        imap.setUserName(Login_dialog.getUSERNAME());
        imap.setPassWord(Login_dialog.getPASSWORD());
        imap.setServerfield(Login_dialog.getServerfield());
        loginsuccess = imap.login(); //进行登陆验证
    }

    if (isLogin()) {
        //若成功登陆，则加载资源
        QString version = _version;
        QString Welcome = "欢迎使用汪汪邮箱(*^__^*) ~~";
        ui->statusBar->showMessage(Welcome);
        //设定当前时钟
        this->permanent = new QLabel(this);
        QTimer* localtimer = new QTimer(this);
        connect(localtimer, &QTimer::timeout, this, &ClientWindow::timerupdate);
        ui->statusBar->addPermanentWidget(this->permanent);
        localtimer->start(1000);
        //绑定操作信号
        QObject::connect(ui->action_undo, SIGNAL(triggered()), ui->WriteMail,
            SLOT(undo()));
        QObject::connect(ui->action_redo, SIGNAL(triggered()), ui->WriteMail,
            SLOT(redo()));
        QObject::connect(ui->action_copy, SIGNAL(triggered()), ui->WriteMail,
            SLOT(copy()));
        QObject::connect(ui->action_paste, SIGNAL(triggered()), ui->WriteMail,
            SLOT(paste()));
        QObject::connect(ui->action_selectAll, SIGNAL(triggered()), ui->WriteMail,
            SLOT(selectAll()));
        QObject::connect(ui->action_cut, SIGNAL(triggered()), ui->WriteMail,
            SLOT(cut()));
        //从服务器加载报文
    }
}

bool ClientWindow::isLogin() { return loginsuccess; }

ClientWindow::~ClientWindow() { delete ui; }

void ClientWindow::timerupdate()
{
    QDateTime time = QDateTime::currentDateTime();
    QString text = "本地时间: ";
    text += time.toString("yyyy-MM-dd hh:mm:ss");
    this->permanent->setText(text);
}

void ClientWindow::on_NewMail_clicked()
{
    ui->WriteMail->show();
    ui->WriteMail->setReadOnly(false); //允许写入
}

void ClientWindow::on_RecvMail_clicked()
{
    ui->WriteMail->hide(); //隐藏
    ui->WriteMail->setReadOnly(true); //禁止写入
    bool OK;
    qDebug()<<imap.getInboxMailList(OK);
    if(OK) qDebug()<<imap.getLog();
}

void ClientWindow::on_action_triggered()
{

}
