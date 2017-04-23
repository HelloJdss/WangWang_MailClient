#ifndef DIALOG_LOGIN_H
#define DIALOG_LOGIN_H

#include "imap.h"
#include "stdafx.h"

namespace Ui {
class Dialog_login;
}

class Dialog_login : public QDialog {
    Q_OBJECT
public:
    explicit Dialog_login(QWidget* parent = 0);
    const QString getUSERNAME();
    const QString getPASSWORD();
    const QString getServerfield();
    ~Dialog_login();

private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Dialog_login* ui;
    QString USERNAME;
    QString Serverfield;
    QString PASSWORD;
};
#endif // DIALOG_LOGIN_H
