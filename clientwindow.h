#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include "dialog_login.h"
#include "imap.h"
#include "stdafx.h"

namespace Ui {
class ClientWindow;
}

class ClientWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit ClientWindow(QWidget* parent = 0);
    bool isLogin(); //是否登陆成功
    ~ClientWindow();

private:
    Ui::ClientWindow* ui;
    bool loginsuccess;
    iMap imap; //尝试建立imap连接
    int imapLog_num; //记录已经输出的imapLog数目，下一次从指定位置添加
    QLabel* permanent;
private slots:
    void timerupdate();
    void setimapLog(); //设置并显示日志信息
    void on_action_triggered();
};
#endif // CLIENTWINDOW_H
