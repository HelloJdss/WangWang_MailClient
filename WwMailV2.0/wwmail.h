#ifndef WWMAIL_H
#define WWMAIL_H

#include <QLabel>
#include <QMainWindow>
#include "accountmanager.h"
#include "addactdialog.h"

namespace Ui {
class WwMail;
}
class AccountManager;
class AddactDialog;

class WwMail : public QMainWindow {
  Q_OBJECT

 public:
  explicit WwMail(QWidget *parent = 0);
  ~WwMail();

 private:
  Ui::WwMail *ui;
  QLabel *permanent;              //用于状态栏输出当前时间
  AccountManager accountManager;  //帐户管理器窗口
  AddactDialog addactDialog;      //添加帐户窗口
 private slots:
  void timerupdate();
  void on_action_M_triggered();
  void on_action_L_triggered();
  void on_pushButton_6_clicked();
public slots:
  void clearcomboBox();
  void additemcomboBox(QString useraccount);

signals:
  void updateActsManager();  //更新帐号管理器窗口信息
  void editaccount(int); //编辑发送帐号
  void saveaccounts();//保存帐号信息
};

#endif  // WWMAIL_H
