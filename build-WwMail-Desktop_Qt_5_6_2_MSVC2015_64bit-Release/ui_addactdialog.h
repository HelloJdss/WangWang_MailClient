/********************************************************************************
** Form generated from reading UI file 'addactdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDACTDIALOG_H
#define UI_ADDACTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AddactDialog
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QPushButton *pushButton_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton_4;
    QFrame *line_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *AddactDialog)
    {
        if (AddactDialog->objectName().isEmpty())
            AddactDialog->setObjectName(QStringLiteral("AddactDialog"));
        AddactDialog->resize(400, 200);
        gridLayout = new QGridLayout(AddactDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label = new QLabel(AddactDialog);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setFamily(QString::fromUtf8("\346\226\271\346\255\243\345\247\232\344\275\223"));
        font.setPointSize(13);
        label->setFont(font);
        label->setFrameShape(QFrame::StyledPanel);
        label->setFrameShadow(QFrame::Plain);
        label->setMargin(0);

        verticalLayout_3->addWidget(label);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_2 = new QLabel(AddactDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setMinimumSize(QSize(50, 0));
        label_2->setMaximumSize(QSize(50, 16777215));
        label_2->setFrameShape(QFrame::NoFrame);

        horizontalLayout_3->addWidget(label_2);

        lineEdit = new QLineEdit(AddactDialog);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setFocusPolicy(Qt::StrongFocus);
        lineEdit->setClearButtonEnabled(false);

        horizontalLayout_3->addWidget(lineEdit);

        pushButton_3 = new QPushButton(AddactDialog);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_3->addWidget(pushButton_3);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 5);
        horizontalLayout_3->setStretch(2, 1);

        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_3 = new QLabel(AddactDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setMinimumSize(QSize(50, 0));
        label_3->setMaximumSize(QSize(50, 16777215));
        label_3->setFrameShape(QFrame::NoFrame);

        horizontalLayout_2->addWidget(label_3);

        lineEdit_2 = new QLineEdit(AddactDialog);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setEchoMode(QLineEdit::Password);

        horizontalLayout_2->addWidget(lineEdit_2);

        pushButton_4 = new QPushButton(AddactDialog);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setMaximumSize(QSize(50, 16777215));
        pushButton_4->setFocusPolicy(Qt::StrongFocus);

        horizontalLayout_2->addWidget(pushButton_4);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 5);
        horizontalLayout_2->setStretch(2, 1);

        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(verticalLayout);

        line_2 = new QFrame(AddactDialog);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(50);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(40, -1, 40, -1);
        pushButton = new QPushButton(AddactDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMouseTracking(false);

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(AddactDialog);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setFocusPolicy(Qt::StrongFocus);

        horizontalLayout->addWidget(pushButton_2);


        verticalLayout_2->addLayout(horizontalLayout);


        verticalLayout_3->addLayout(verticalLayout_2);


        gridLayout->addLayout(verticalLayout_3, 0, 0, 1, 1);


        retranslateUi(AddactDialog);
        QObject::connect(pushButton_2, SIGNAL(clicked()), AddactDialog, SLOT(reject()));

        pushButton->setDefault(true);


        QMetaObject::connectSlotsByName(AddactDialog);
    } // setupUi

    void retranslateUi(QDialog *AddactDialog)
    {
        AddactDialog->setWindowTitle(QApplication::translate("AddactDialog", "\346\267\273\345\212\240\345\270\220\346\210\267", 0));
        label->setText(QApplication::translate("AddactDialog", "\346\254\242\350\277\216\344\275\277\347\224\250\346\261\252\346\261\252\351\202\256\347\256\261\357\274\201\350\257\267\346\267\273\345\212\240\346\202\250\347\232\204\351\202\256\347\256\261\345\270\220\346\210\267\357\274\232", 0));
        label_2->setText(QApplication::translate("AddactDialog", "\345\270\220\346\210\267\345\220\215\357\274\232", 0));
        pushButton_3->setText(QApplication::translate("AddactDialog", "\346\270\205\347\251\272", 0));
        label_3->setText(QApplication::translate("AddactDialog", "\345\257\206\347\240\201\357\274\232", 0));
        pushButton_4->setText(QApplication::translate("AddactDialog", "\346\230\276\347\244\272", 0));
        pushButton->setText(QApplication::translate("AddactDialog", "\346\267\273\345\212\240(*^__^*)", 0));
        pushButton_2->setText(QApplication::translate("AddactDialog", "\345\206\215\346\203\263\346\203\263~(>_<)~", 0));
    } // retranslateUi

};

namespace Ui {
    class AddactDialog: public Ui_AddactDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDACTDIALOG_H
