#ifndef WWMAIL_H
#define WWMAIL_H

#include <QLabel>
#include <QMainWindow>
#include "accountmanager.h"
#include "addactdialog.h"
#include "imapthread.h"
#include <QList>

namespace Ui {
class WwMail;
}
class AccountManager;
class AddactDialog;
class imapThread;

class WwMail : public QMainWindow {
  Q_OBJECT

 public:
  explicit WwMail(QWidget *parent = 0);
  ~WwMail();

 private:
  Ui::WwMail *ui;
  QLabel *permanent;              //用于状态栏输出当前时间
  AccountManager* accountManager;  //帐户管理器窗口
  AddactDialog addactDialog;      //添加帐户窗口
  QList<imapThread*> imapList;     //imap连接进程列表
 private slots:
  void timerupdate();
  void on_action_M_triggered();
  void on_action_L_triggered();
  void on_pushButton_6_clicked();
public slots:
  void clearcomboBox();
  void additemcomboBox(QString useraccount);
  void createimapThread(AccountInfo account);//创建imap子线程
  void destoryimapThread(AccountInfo account);//销毁imap子线程，依据accountname为索引
  void criticalMessageBox(QString msg);//错误信息提示框
  void warningMessageBox(QString msg); //警告信息提示框
signals:
  void updateActsManager();  //更新帐号管理器窗口信息
  void editaccount(int); //编辑发送帐号
  void saveaccounts();//保存帐号信息
};

#endif  // WWMAIL_H
