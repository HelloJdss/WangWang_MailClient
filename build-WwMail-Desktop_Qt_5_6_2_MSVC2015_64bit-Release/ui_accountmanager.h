/********************************************************************************
** Form generated from reading UI file 'accountmanager.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACCOUNTMANAGER_H
#define UI_ACCOUNTMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AccountManager
{
public:
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QComboBox *comboBox;
    QPushButton *pushButton_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLineEdit *lineEdit;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_7;
    QLineEdit *lineEdit_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_8;
    QLineEdit *lineEdit_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_10;
    QLineEdit *lineEdit_4;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_9;
    QLineEdit *lineEdit_5;
    QFrame *line;
    QHBoxLayout *horizontalLayout_9;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *pushButton;
    QCheckBox *checkBox;
    QPushButton *pushButton_2;

    void setupUi(QWidget *AccountManager)
    {
        if (AccountManager->objectName().isEmpty())
            AccountManager->setObjectName(QStringLiteral("AccountManager"));
        AccountManager->resize(500, 300);
        AccountManager->setAutoFillBackground(false);
        verticalLayout_4 = new QVBoxLayout(AccountManager);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(AccountManager);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFrameShape(QFrame::NoFrame);

        horizontalLayout->addWidget(label_2);

        comboBox = new QComboBox(AccountManager);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        horizontalLayout->addWidget(comboBox);

        pushButton_3 = new QPushButton(AccountManager);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        horizontalLayout->addWidget(pushButton_3);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 9);

        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_3 = new QLabel(AccountManager);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFrameShape(QFrame::NoFrame);

        horizontalLayout_2->addWidget(label_3);

        lineEdit = new QLineEdit(AccountManager);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setEchoMode(QLineEdit::Password);

        horizontalLayout_2->addWidget(lineEdit);


        verticalLayout_3->addLayout(horizontalLayout_2);


        verticalLayout_4->addLayout(verticalLayout_3);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_4 = new QLabel(AccountManager);
        label_4->setObjectName(QStringLiteral("label_4"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        label_4->setMinimumSize(QSize(0, 20));
        label_4->setFrameShape(QFrame::StyledPanel);
        label_4->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_4);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_7 = new QLabel(AccountManager);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setFrameShape(QFrame::NoFrame);

        horizontalLayout_4->addWidget(label_7);

        lineEdit_2 = new QLineEdit(AccountManager);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        horizontalLayout_4->addWidget(lineEdit_2);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_8 = new QLabel(AccountManager);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setFrameShape(QFrame::NoFrame);

        horizontalLayout_3->addWidget(label_8);

        lineEdit_3 = new QLineEdit(AccountManager);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setInputMethodHints(Qt::ImhDigitsOnly);
        lineEdit_3->setDragEnabled(false);

        horizontalLayout_3->addWidget(lineEdit_3);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 1);
        verticalLayout->setStretch(2, 1);

        horizontalLayout_7->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_5 = new QLabel(AccountManager);
        label_5->setObjectName(QStringLiteral("label_5"));
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);
        label_5->setMinimumSize(QSize(0, 20));
        label_5->setFrameShape(QFrame::StyledPanel);
        label_5->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_10 = new QLabel(AccountManager);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setFrameShape(QFrame::NoFrame);

        horizontalLayout_6->addWidget(label_10);

        lineEdit_4 = new QLineEdit(AccountManager);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setInputMethodHints(Qt::ImhDigitsOnly);

        horizontalLayout_6->addWidget(lineEdit_4);


        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_9 = new QLabel(AccountManager);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setFrameShape(QFrame::NoFrame);

        horizontalLayout_5->addWidget(label_9);

        lineEdit_5 = new QLineEdit(AccountManager);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));

        horizontalLayout_5->addWidget(lineEdit_5);


        verticalLayout_2->addLayout(horizontalLayout_5);

        verticalLayout_2->setStretch(0, 1);
        verticalLayout_2->setStretch(1, 1);
        verticalLayout_2->setStretch(2, 1);

        horizontalLayout_7->addLayout(verticalLayout_2);


        verticalLayout_4->addLayout(horizontalLayout_7);

        line = new QFrame(AccountManager);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_4->addWidget(line);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        pushButton = new QPushButton(AccountManager);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setAutoDefault(true);

        horizontalLayout_8->addWidget(pushButton);

        checkBox = new QCheckBox(AccountManager);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(checkBox->sizePolicy().hasHeightForWidth());
        checkBox->setSizePolicy(sizePolicy1);
        checkBox->setChecked(true);
        checkBox->setTristate(false);

        horizontalLayout_8->addWidget(checkBox);


        horizontalLayout_9->addLayout(horizontalLayout_8);

        pushButton_2 = new QPushButton(AccountManager);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_9->addWidget(pushButton_2);


        verticalLayout_4->addLayout(horizontalLayout_9);

        verticalLayout_4->setStretch(0, 1);
        verticalLayout_4->setStretch(1, 1);

        retranslateUi(AccountManager);
        QObject::connect(pushButton_2, SIGNAL(clicked()), AccountManager, SLOT(hide()));

        pushButton->setDefault(false);


        QMetaObject::connectSlotsByName(AccountManager);
    } // setupUi

    void retranslateUi(QWidget *AccountManager)
    {
        AccountManager->setWindowTitle(QApplication::translate("AccountManager", "\345\270\220\345\217\267\347\256\241\347\220\206\345\231\250", 0));
        label_2->setText(QApplication::translate("AccountManager", "\351\200\211\346\213\251\345\270\220\345\217\267", 0));
        pushButton_3->setText(QApplication::translate("AccountManager", "\345\210\240\351\231\244\345\270\220\345\217\267", 0));
        label_3->setText(QApplication::translate("AccountManager", "\345\257\206\347\240\201\347\274\226\350\276\221", 0));
        lineEdit->setText(QString());
        label_4->setText(QApplication::translate("AccountManager", "IMAP\346\234\215\345\212\241\345\231\250\350\256\276\347\275\256", 0));
        label_7->setText(QApplication::translate("AccountManager", "\345\234\260\345\235\200\357\274\232", 0));
        label_8->setText(QApplication::translate("AccountManager", "\347\253\257\345\217\243\357\274\232", 0));
        label_5->setText(QApplication::translate("AccountManager", "SMTP\346\234\215\345\212\241\345\231\250\350\256\276\347\275\256", 0));
        label_10->setText(QApplication::translate("AccountManager", "\345\234\260\345\235\200\357\274\232", 0));
        label_9->setText(QApplication::translate("AccountManager", "\347\253\257\345\217\243\357\274\232", 0));
        pushButton->setText(QApplication::translate("AccountManager", "\344\277\235\345\255\230", 0));
        checkBox->setText(QApplication::translate("AccountManager", "\346\234\254\345\234\260\351\225\277\346\234\237\344\277\235\345\255\230", 0));
        pushButton_2->setText(QApplication::translate("AccountManager", "\345\217\226\346\266\210", 0));
    } // retranslateUi

};

namespace Ui {
    class AccountManager: public Ui_AccountManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACCOUNTMANAGER_H
