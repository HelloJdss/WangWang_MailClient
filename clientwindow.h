#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include "dialog_login.h"
#include "imap.h"
#include "stdafx.h"
#include <QStandardItemModel>

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
    Dialog_login Login_dialog; //记录登录信息，包括登录用户名以及密码等信息
    iMap imap; //尝试建立imap连接
    void initMailBoxListTree();
    QStandardItemModel *MailBoxTree;
    void initMailTableView();
    void updateMailTableView();
    QStringList AnalyzeMailHeader(int order); //分析邮件头
    QStringList* MaillistDataInTable; //记录邮件的头部
    QStandardItemModel *MailTable;
    int imapLog_num; //记录已经输出的imapLog数目，下一次从指定位置添加
    QLabel* permanent; //用于状态栏输出当前时间
private slots:
    void timerupdate();
    void setimapLog(); //设置并显示日志信息
    void on_action_imapLog_triggered();
    void on_action_relog_triggered();
    void on_MailBoxView_doubleClicked(const QModelIndex &index);
};
#endif // CLIENTWINDOW_H
