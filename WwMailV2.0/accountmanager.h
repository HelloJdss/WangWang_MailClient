#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QList>
#include <QMessageBox>
#include <QRegExp>
#include <QWidget>
namespace Ui {
class AccountManager;
}

class AccountInfo {
  //帐户信息
public:
  QString accountname; //完整帐户名，相当于accounts的索引，该列唯一
  QString username;
  QString userpassword;
  QString imapfield; //服务器域名
  qint32 imapport;
  QString smtpfield;
  qint32 smtpport;
};

class AccountManager : public QWidget {
  Q_OBJECT

public:
  explicit AccountManager(QWidget *parent = 0);
  ~AccountManager();
  qint32 findaccount(QString accountname); //查找帐户序号，不存在则返回-1
private slots:
  void on_pushButton_clicked(); //保存
  void on_comboBox_currentIndexChanged(int index);

  void on_pushButton_3_clicked(); //删除

public slots:
  void addaccount(QString username, QString userpassword); //添加帐户
  void updateManager();        //刷新管理器信息
  void editaccount(int index); //编辑发送帐号
  void saveaccounts();//保存帐户信息到本地
private:
  Ui::AccountManager *ui;
  QList<AccountInfo> accounts; //帐户列表
signals:
  void clearcomboBox();
  void additemcomboBox(QString);
};

#endif // ACCOUNTMANAGER_H
