#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include "stdafx.h"
#include "dialog_login.h"
#include "imap.h"

namespace Ui {
class ClientWindow;
}

class ClientWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ClientWindow(QWidget *parent = 0);
    bool isLogin(); //是否登陆成功
    ~ClientWindow();

private:
    Ui::ClientWindow *ui;
    bool loginsuccess;
    QLabel *permanent;
private slots:
    void timerupdate();
    void on_NewMail_clicked();
    void on_RecvMail_clicked();
};
#endif // CLIENTWINDOW_H
