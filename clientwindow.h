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
  explicit ClientWindow(QWidget *parent = 0);
  bool isLogin(); //是否登陆成功z
  ~ClientWindow();

private:
  Ui::ClientWindow *ui;
  bool loginsuccess;
  iMap imap; //尝试建立imap连接
  QLabel *permanent;
private slots:
  void timerupdate();
  void on_NewMail_clicked();
  void on_RecvMail_clicked();
};
#endif // CLIENTWINDOW_H
