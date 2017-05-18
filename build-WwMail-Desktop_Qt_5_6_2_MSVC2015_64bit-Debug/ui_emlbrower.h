/********************************************************************************
** Form generated from reading UI file 'emlbrower.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EMLBROWER_H
#define UI_EMLBROWER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_emlBrower
{
public:
    QVBoxLayout *verticalLayout_4;
    QSplitter *splitter_2;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit_date;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLineEdit *lineEdit_from;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QLineEdit *lineEdit_to;
    QHBoxLayout *horizontalLayout;
    QLabel *label_4;
    QLineEdit *lineEdit_subject;
    QSplitter *splitter;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_3;
    QWidget *MiMEWidget;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *pushButton_5;
    QPushButton *pushButton_4;
    QPushButton *pushButton_3;
    QPushButton *pushButton_6;
    QSpacerItem *horizontalSpacer;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_6;
    QListView *listView;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QWidget *emlBrower)
    {
        if (emlBrower->objectName().isEmpty())
            emlBrower->setObjectName(QStringLiteral("emlBrower"));
        emlBrower->setWindowModality(Qt::NonModal);
        emlBrower->resize(1024, 576);
        emlBrower->setAutoFillBackground(true);
        verticalLayout_4 = new QVBoxLayout(emlBrower);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        splitter_2 = new QSplitter(emlBrower);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        splitter_2->setOrientation(Qt::Vertical);
        layoutWidget = new QWidget(splitter_2);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setMinimumSize(QSize(60, 0));
        label_2->setMaximumSize(QSize(60, 16777215));
        label_2->setFrameShape(QFrame::NoFrame);

        horizontalLayout_2->addWidget(label_2);

        lineEdit_date = new QLineEdit(layoutWidget);
        lineEdit_date->setObjectName(QStringLiteral("lineEdit_date"));
        lineEdit_date->setReadOnly(true);

        horizontalLayout_2->addWidget(lineEdit_date);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(60, 0));
        label->setMaximumSize(QSize(60, 16777215));
        label->setFrameShape(QFrame::NoFrame);

        horizontalLayout_3->addWidget(label);

        lineEdit_from = new QLineEdit(layoutWidget);
        lineEdit_from->setObjectName(QStringLiteral("lineEdit_from"));
        lineEdit_from->setReadOnly(true);

        horizontalLayout_3->addWidget(lineEdit_from);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setMinimumSize(QSize(60, 0));
        label_3->setMaximumSize(QSize(60, 16777215));
        label_3->setFrameShape(QFrame::NoFrame);

        horizontalLayout_4->addWidget(label_3);

        lineEdit_to = new QLineEdit(layoutWidget);
        lineEdit_to->setObjectName(QStringLiteral("lineEdit_to"));
        lineEdit_to->setReadOnly(true);

        horizontalLayout_4->addWidget(lineEdit_to);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        label_4->setMinimumSize(QSize(60, 0));
        label_4->setMaximumSize(QSize(60, 16777215));

        horizontalLayout->addWidget(label_4);

        lineEdit_subject = new QLineEdit(layoutWidget);
        lineEdit_subject->setObjectName(QStringLiteral("lineEdit_subject"));
        lineEdit_subject->setReadOnly(true);

        horizontalLayout->addWidget(lineEdit_subject);


        verticalLayout->addLayout(horizontalLayout);

        splitter_2->addWidget(layoutWidget);
        splitter = new QSplitter(splitter_2);
        splitter->setObjectName(QStringLiteral("splitter"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(9);
        sizePolicy1.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy1);
        splitter->setOrientation(Qt::Horizontal);
        layoutWidget1 = new QWidget(splitter);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        verticalLayout_3 = new QVBoxLayout(layoutWidget1);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        MiMEWidget = new QWidget(layoutWidget1);
        MiMEWidget->setObjectName(QStringLiteral("MiMEWidget"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(9);
        sizePolicy2.setHeightForWidth(MiMEWidget->sizePolicy().hasHeightForWidth());
        MiMEWidget->setSizePolicy(sizePolicy2);
        MiMEWidget->setMinimumSize(QSize(800, 0));

        verticalLayout_3->addWidget(MiMEWidget);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        pushButton_5 = new QPushButton(layoutWidget1);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        horizontalLayout_5->addWidget(pushButton_5);

        pushButton_4 = new QPushButton(layoutWidget1);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        horizontalLayout_5->addWidget(pushButton_4);

        pushButton_3 = new QPushButton(layoutWidget1);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        horizontalLayout_5->addWidget(pushButton_3);

        pushButton_6 = new QPushButton(layoutWidget1);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));

        horizontalLayout_5->addWidget(pushButton_6);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);


        verticalLayout_3->addLayout(horizontalLayout_5);

        splitter->addWidget(layoutWidget1);
        layoutWidget2 = new QWidget(splitter);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        verticalLayout_2 = new QVBoxLayout(layoutWidget2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(layoutWidget2);
        label_6->setObjectName(QStringLiteral("label_6"));

        verticalLayout_2->addWidget(label_6);

        listView = new QListView(layoutWidget2);
        listView->setObjectName(QStringLiteral("listView"));
        listView->setEditTriggers(QAbstractItemView::NoEditTriggers);

        verticalLayout_2->addWidget(listView);

        pushButton = new QPushButton(layoutWidget2);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout_2->addWidget(pushButton);

        pushButton_2 = new QPushButton(layoutWidget2);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        verticalLayout_2->addWidget(pushButton_2);

        splitter->addWidget(layoutWidget2);
        splitter_2->addWidget(splitter);

        verticalLayout_4->addWidget(splitter_2);


        retranslateUi(emlBrower);

        QMetaObject::connectSlotsByName(emlBrower);
    } // setupUi

    void retranslateUi(QWidget *emlBrower)
    {
        emlBrower->setWindowTitle(QApplication::translate("emlBrower", "EmlBrower", 0));
        label_2->setText(QApplication::translate("emlBrower", "Date\357\274\232", 0));
        label->setText(QApplication::translate("emlBrower", "From\357\274\232", 0));
        label_3->setText(QApplication::translate("emlBrower", "To\357\274\232", 0));
        label_4->setText(QApplication::translate("emlBrower", "Subject\357\274\232", 0));
        pushButton_5->setText(QApplication::translate("emlBrower", "\350\275\254\345\217\221\351\202\256\344\273\266", 0));
        pushButton_4->setText(QApplication::translate("emlBrower", "\345\277\253\351\200\237\345\233\236\345\244\215", 0));
        pushButton_3->setText(QApplication::translate("emlBrower", "\346\240\207\350\256\260\345\210\240\351\231\244", 0));
        pushButton_6->setText(QApplication::translate("emlBrower", "\344\277\235\345\255\230\351\202\256\344\273\266", 0));
        label_6->setText(QApplication::translate("emlBrower", "\351\231\204\344\273\266\345\210\227\350\241\250\357\274\232", 0));
        pushButton->setText(QApplication::translate("emlBrower", "\346\211\223\345\274\200", 0));
        pushButton_2->setText(QApplication::translate("emlBrower", "\345\217\246\345\255\230\344\270\272", 0));
    } // retranslateUi

};

namespace Ui {
    class emlBrower: public Ui_emlBrower {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EMLBROWER_H
