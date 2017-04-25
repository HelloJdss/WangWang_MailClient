#include "clientwindow.h"
#include "ui_clientwindow.h"
#include <QLabel>
#include <QStringList>
#include <QTimer>
#include <QTextCodec>
#define _version "0.1"

ClientWindow::ClientWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::ClientWindow)
    , Login_dialog(parent)
{
    ui->setupUi(this);
    this->imapLog_num = 0;
    this->loginsuccess = false;
    this->MailBoxTree = new QStandardItemModel(ui->MailBoxView);
    this->MailTable = new QStandardItemModel(ui->MailTable);
    this->on_action_relog_triggered();
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
        //        QObject::connect(ui->action_undo, SIGNAL(triggered()), ui->WriteMail,
        //            SLOT(undo()));
        //        QObject::connect(ui->action_redo, SIGNAL(triggered()), ui->WriteMail,
        //            SLOT(redo()));
        //        QObject::connect(ui->action_copy, SIGNAL(triggered()), ui->WriteMail,
        //            SLOT(copy()));
        //        QObject::connect(ui->action_paste, SIGNAL(triggered()), ui->WriteMail,
        //            SLOT(paste()));
        //        QObject::connect(ui->action_selectAll, SIGNAL(triggered()), ui->WriteMail,
        //            SLOT(selectAll()));
        //        QObject::connect(ui->action_cut, SIGNAL(triggered()), ui->WriteMail,
        //            SLOT(cut()));
        //从服务器加载报文
        initMailBoxListTree();
        initMailTableView();
    }
}

bool ClientWindow::isLogin() { return loginsuccess; }

ClientWindow::~ClientWindow() { delete ui; }

void ClientWindow::initMailBoxListTree()
{
    this->MailBoxTree->setHorizontalHeaderLabels(QStringList() << QString(tr("邮箱列表")));
    this->ui->MailBoxView->setModel(this->MailBoxTree);
    QStandardItem* item = new QStandardItem(QString(tr("我的邮箱")));
    this->MailBoxTree->appendRow(item);
    item->appendRow(new QStandardItem(QString(tr("收件箱"))));
    item->appendRow(new QStandardItem(QString(tr("已发送"))));
    item->appendRow(new QStandardItem(QString(tr("草稿箱"))));
    item->appendRow(new QStandardItem(QString(tr("已删除"))));
    item->appendRow(new QStandardItem(QString(tr("垃圾箱"))));
}

void ClientWindow::initMailTableView()
{
    this->MailTable->setHorizontalHeaderLabels(QStringList() << QString(tr("序号"))
                                               << QString(tr("发件人"))
                                               << QString(tr("主题"))
                                               << QString(tr("日期")));
    this->ui->MailTable->setModel(this->MailTable);
    this->ui->MailTable->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    this->ui->MailTable->verticalHeader()->hide();
    this->ui->MailTable->setColumnWidth(0,50);
    this->ui->MailTable->setColumnWidth(1,400);
    this->ui->MailTable->setColumnWidth(2,400);
    this->ui->MailTable->setColumnWidth(3,300);
}

void ClientWindow::updateMailTableView()
{
    for(int i=0;i<this->MaillistDataInTable->size();i++){
        this->MailTable->setItem(i,0,new QStandardItem(QString::number(i+1,10)));
        this->MailTable->item(i,0)->setTextAlignment(Qt::AlignCenter); //序号居中
        QStringList MailHeader = this->MaillistDataInTable->at(i).split("\r\n");
        for(int j=0;j<MailHeader.size();j++){
            if(MailHeader.at(j).left(8)=="Subject:"){
                //处理主题信息
                QString subject=MailHeader.at(j);
                subject=subject.remove("Subject:").remove(" ");
                if("=?"==subject.left(2)){
                    QStringList sub =subject.split("?");
                    qDebug()<<sub.at(1).toUpper().toLatin1();
                    QTextCodec *codec =QTextCodec::codecForName(sub.at(1).toUpper().toLatin1());
                    QString sub_utf = codec->toUnicode(QByteArray::fromBase64(sub.at(3).toLatin1()));
                    this->MailTable->setItem(i,2,new QStandardItem(sub_utf));
                    qDebug()<<sub;
                }
                else this->MailTable->setItem(i,2,new QStandardItem(subject));
                break;
            }
            if(MailHeader.at(j).left(5)=="Date:"){
                //处理时间
                QString date=MailHeader.at(j);
                date=date.remove("Date:");
                this->MailTable->setItem(i,3,new QStandardItem(date));
            }
            if(MailHeader.at(j).left(5)=="From:"){
                //处理发件人
                QString from=MailHeader.at(j);
                from=from.remove("From:").remove(" ");
                if("=?"==from.left(2)){
                    QStringList sub =from.split("?");
                    qDebug()<<sub.at(1).toUpper().toLatin1();
                    QTextCodec *codec =QTextCodec::codecForName(sub.at(1).toUpper().toLatin1());
                    QString sub_utf = codec->toUnicode(QByteArray::fromBase64(sub.at(3).toLatin1()));
                    this->MailTable->setItem(i,1,new QStandardItem(sub_utf));
                    qDebug()<<sub;
                }
                else this->MailTable->setItem(i,1,new QStandardItem(from));
            }
        }
    }
}

void ClientWindow::timerupdate()
{
    QDateTime time = QDateTime::currentDateTime();
    QString text = "本地时间: ";
    text += time.toString("yyyy-MM-dd hh:mm:ss");
    this->permanent->setText(text);
}

void ClientWindow::setimapLog()
{
    QStringList imapLog = this->imap.getLog();
    for (; this->imapLog_num < imapLog.size(); this->imapLog_num++) {
        ui->Logview->append(imapLog.at(this->imapLog_num));
    }
}

void ClientWindow::on_action_imapLog_triggered()
{
    setimapLog();
}

void ClientWindow::on_action_relog_triggered()
{
    Login_dialog.setModal(
        true); //设置为模态对话框，禁止在登陆之前与主窗口进行交互
    Login_dialog.show();
    Login_dialog.move(
        (QApplication::desktop()->width() - Login_dialog.width()) / 2,
        (QApplication::desktop()->height() - Login_dialog.height()) / 2); //调整窗口位到屏幕中央
    auto ret = Login_dialog.exec();
    if (ret == QDialog::Rejected) {
        if (!loginsuccess) //若已成功登录，则忽略
            loginsuccess = false; //如果拒绝登入，则设定登陆验证为失败
    } else if (ret == QDialog::Accepted) {
        if (loginsuccess) //若已经成功登录，则先退出
            imap.logout();
        imap.setHost("imap.qq.com");
        imap.setPort(143);
        imap.setUserName(Login_dialog.getUSERNAME());
        imap.setPassWord(Login_dialog.getPASSWORD());
        imap.setServerfield(Login_dialog.getServerfield());
        loginsuccess = imap.login(); //进行登陆验证
    }
}

void ClientWindow::on_MailBoxView_doubleClicked(const QModelIndex& index)
{
    qDebug() << index;
    qDebug() << index.column() << index.row() << index.parent().row();
    if (index.parent().row() == 0) {
        switch (index.row()) {
        case 0:
            bool OK;
            this->MaillistDataInTable = &this->imap.getInboxMailList(OK);
            qDebug()<<OK;
            if(OK) updateMailTableView();
            else {
                QMessageBox::warning(this, QObject::tr("警告！"), tr("获取邮件列表失败，请重试！"),
                    QMessageBox::Yes); //警告对话框
            }
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        }
    }
}
