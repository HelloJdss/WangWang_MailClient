#ifndef ADDACTDIALOG_H
#define ADDACTDIALOG_H

#include <QDialog>

namespace Ui {
  class AddactDialog;
}

class AddactDialog : public QDialog
{
  Q_OBJECT

public:
  explicit AddactDialog(QWidget *parent = 0);
  ~AddactDialog();

private slots:
  void on_pushButton_clicked();

  void on_pushButton_3_clicked();

  void on_pushButton_4_clicked();

private:
  Ui::AddactDialog *ui;
  bool button4changed;
signals:
  void addact(QString,QString);
};

#endif // ADDACTDIALOG_H
