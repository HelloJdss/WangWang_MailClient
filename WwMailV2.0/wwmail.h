#ifndef WWMAIL_H
#define WWMAIL_H

#include <QLabel>
#include <QMainWindow>
#include "accountmanager.h"
#include "addactdialog.h"
#include "imapthread.h"
#include <QList>
#include <QStandardItemModel>
#include <QMetaType>
#include <QProgressDialog>
namespace Ui {
class WwMail;
}
class AccountManager;
class AddactDialog;
class imapThread;
class MimeData;

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
  QMenu* treeview_itemMenu; //右键tree项目的菜单
  QProgressDialog* Progressdialog;
  QString ListMailAccount; //目前正显示的帐号名称
//  QStandardItemModel* MailBoxTree; //各帐号邮箱列表
 private slots:
  void timerupdate();
  void on_action_M_triggered();
  void on_action_L_triggered();
  void on_pushButton_6_clicked();
  void on_action_R_triggered();

  void on_treeView_customContextMenuRequested(const QPoint &pos);

  void on_treeView_doubleClicked(const QModelIndex &index);

  void on_comboBox_currentIndexChanged(const QString &arg1);
  void addItemToRecentContactPersonList(const QList<MimeData>& SendMimeData); //发件箱列表

  void on_pushButton_5_clicked();

  void on_Mailtable_doubleClicked(const QModelIndex &index);

public slots:
  void clearcomboBox();
  void additemcomboBox(QString useraccount);
  void createimapThread(AccountInfo account);//创建imap子线程
  void updateimapThread(AccountInfo account); //刷新子线程管理器中的帐号信息
  void destoryimapThread(AccountInfo account);//销毁imap子线程，依据accountname为索引
  void criticalMessageBox(QString msg);//错误信息提示框
  void warningMessageBox(QString msg); //警告信息提示框
  void addMailFolderView(QString useraccount,QStringList mailboxlist); //向treeview中添加帐户信息
  void removeMailBox(QString useracoount); //从treeview中移除相应帐号信息
  void addMailHeaderView(const QList<MimeData>& MimeList); //收到来自线程的数据后，向TableView中添加邮件头信息
  void StartShowProgressdialog(); //显示进度条
  void SetProgress(qint32 value,qint32 max);
  void CloseProgressdialog();//
  //
signals:
  void updateActsManager();  //更新帐号管理器窗口信息
  void editaccount(int); //编辑发送帐号
  void saveaccounts();//保存帐号信息
  void imapConnect();//连接所有imap连接
  void updateimapact(); //请求imapThread更新imap线程中的帐号信息
  void rqstimapHeaderList(QString,int);//请求imap连接的邮件头部信息
  void rqstimapBody(QString,int); //请求imap获取邮件体
};

#endif  // WWMAIL_H
