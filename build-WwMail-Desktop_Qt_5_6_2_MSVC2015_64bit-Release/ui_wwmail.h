/********************************************************************************
** Form generated from reading UI file 'wwmail.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WWMAIL_H
#define UI_WWMAIL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WwMail
{
public:
    QAction *action_Q;
    QAction *action_M;
    QAction *action_L;
    QAction *action_A;
    QAction *action_R;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_3;
    QTreeView *treeView;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QTableView *Mailtable;
    QWidget *tab_2;
    QGridLayout *gridLayout_2;
    QSplitter *splitter_2;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_9;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_5;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_6;
    QLineEdit *lineEdit;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_12;
    QLineEdit *lineEdit_3;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_13;
    QLineEdit *lineEdit_4;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_7;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton_5;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_8;
    QLineEdit *lineEdit_5;
    QComboBox *comboBox;
    QPushButton *pushButton_6;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_9;
    QVBoxLayout *verticalLayout_4;
    QComboBox *comboBox_2;
    QTextEdit *textEdit;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_11;
    QProgressBar *progressBar;
    QWidget *layoutWidget3;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout_7;
    QLabel *label;
    QListView *listView_2;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_10;
    QListView *listView;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QMenuBar *menuBar;
    QMenu *menu_M;
    QMenu *menu_A;
    QMenu *menu_H;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *WwMail)
    {
        if (WwMail->objectName().isEmpty())
            WwMail->setObjectName(QStringLiteral("WwMail"));
        WwMail->resize(1200, 720);
        action_Q = new QAction(WwMail);
        action_Q->setObjectName(QStringLiteral("action_Q"));
        action_M = new QAction(WwMail);
        action_M->setObjectName(QStringLiteral("action_M"));
        action_L = new QAction(WwMail);
        action_L->setObjectName(QStringLiteral("action_L"));
        action_A = new QAction(WwMail);
        action_A->setObjectName(QStringLiteral("action_A"));
        action_R = new QAction(WwMail);
        action_R->setObjectName(QStringLiteral("action_R"));
        centralWidget = new QWidget(WwMail);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setAutoFillBackground(false);
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout = new QGridLayout(tab);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setHorizontalSpacing(6);
        gridLayout->setContentsMargins(2, 1, 2, 2);
        splitter = new QSplitter(tab);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        verticalLayout_3 = new QVBoxLayout(layoutWidget);
        verticalLayout_3->setSpacing(1);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        treeView = new QTreeView(layoutWidget);
        treeView->setObjectName(QStringLiteral("treeView"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(treeView->sizePolicy().hasHeightForWidth());
        treeView->setSizePolicy(sizePolicy);
        treeView->setContextMenuPolicy(Qt::CustomContextMenu);
        treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);

        verticalLayout_3->addWidget(treeView);

        splitter->addWidget(layoutWidget);
        layoutWidget1 = new QWidget(splitter);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setSpacing(2);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        Mailtable = new QTableView(layoutWidget1);
        Mailtable->setObjectName(QStringLiteral("Mailtable"));
        Mailtable->setEditTriggers(QAbstractItemView::NoEditTriggers);

        verticalLayout->addWidget(Mailtable);

        splitter->addWidget(layoutWidget1);

        gridLayout->addWidget(splitter, 0, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        gridLayout_2 = new QGridLayout(tab_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        splitter_2 = new QSplitter(tab_2);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        splitter_2->setOrientation(Qt::Horizontal);
        layoutWidget2 = new QWidget(splitter_2);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        verticalLayout_9 = new QVBoxLayout(layoutWidget2);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(0, 0, 0, 0);
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_6 = new QLabel(layoutWidget2);
        label_6->setObjectName(QStringLiteral("label_6"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy1);
        label_6->setMinimumSize(QSize(60, 0));
        label_6->setMaximumSize(QSize(60, 16777215));
        label_6->setFrameShape(QFrame::NoFrame);

        horizontalLayout_4->addWidget(label_6);

        lineEdit = new QLineEdit(layoutWidget2);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout_4->addWidget(lineEdit);


        horizontalLayout_5->addLayout(horizontalLayout_4);

        pushButton_3 = new QPushButton(layoutWidget2);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        horizontalLayout_5->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(layoutWidget2);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        horizontalLayout_5->addWidget(pushButton_4);


        verticalLayout_5->addLayout(horizontalLayout_5);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_12 = new QLabel(layoutWidget2);
        label_12->setObjectName(QStringLiteral("label_12"));
        sizePolicy1.setHeightForWidth(label_12->sizePolicy().hasHeightForWidth());
        label_12->setSizePolicy(sizePolicy1);
        label_12->setMinimumSize(QSize(60, 0));
        label_12->setMaximumSize(QSize(60, 16777215));
        label_12->setFrameShape(QFrame::NoFrame);

        horizontalLayout_8->addWidget(label_12);

        lineEdit_3 = new QLineEdit(layoutWidget2);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));

        horizontalLayout_8->addWidget(lineEdit_3);


        verticalLayout_5->addLayout(horizontalLayout_8);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_13 = new QLabel(layoutWidget2);
        label_13->setObjectName(QStringLiteral("label_13"));
        sizePolicy1.setHeightForWidth(label_13->sizePolicy().hasHeightForWidth());
        label_13->setSizePolicy(sizePolicy1);
        label_13->setMinimumSize(QSize(60, 0));
        label_13->setMaximumSize(QSize(60, 16777215));
        label_13->setFrameShape(QFrame::NoFrame);

        horizontalLayout_10->addWidget(label_13);

        lineEdit_4 = new QLineEdit(layoutWidget2);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));

        horizontalLayout_10->addWidget(lineEdit_4);


        verticalLayout_5->addLayout(horizontalLayout_10);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_7 = new QLabel(layoutWidget2);
        label_7->setObjectName(QStringLiteral("label_7"));
        sizePolicy1.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy1);
        label_7->setMinimumSize(QSize(60, 0));
        label_7->setMaximumSize(QSize(60, 16777215));
        label_7->setFrameShape(QFrame::NoFrame);

        horizontalLayout_6->addWidget(label_7);

        lineEdit_2 = new QLineEdit(layoutWidget2);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        horizontalLayout_6->addWidget(lineEdit_2);

        pushButton_5 = new QPushButton(layoutWidget2);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        horizontalLayout_6->addWidget(pushButton_5);


        verticalLayout_5->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_8 = new QLabel(layoutWidget2);
        label_8->setObjectName(QStringLiteral("label_8"));
        sizePolicy1.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy1);
        label_8->setMinimumSize(QSize(60, 0));
        label_8->setMaximumSize(QSize(60, 16777215));
        label_8->setFrameShape(QFrame::NoFrame);

        horizontalLayout_7->addWidget(label_8);

        lineEdit_5 = new QLineEdit(layoutWidget2);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));

        horizontalLayout_7->addWidget(lineEdit_5);

        comboBox = new QComboBox(layoutWidget2);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        horizontalLayout_7->addWidget(comboBox);

        pushButton_6 = new QPushButton(layoutWidget2);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));

        horizontalLayout_7->addWidget(pushButton_6);

        horizontalLayout_7->setStretch(0, 1);
        horizontalLayout_7->setStretch(2, 5);

        verticalLayout_5->addLayout(horizontalLayout_7);


        verticalLayout_9->addLayout(verticalLayout_5);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_9 = new QLabel(layoutWidget2);
        label_9->setObjectName(QStringLiteral("label_9"));
        sizePolicy1.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy1);
        label_9->setMinimumSize(QSize(60, 0));
        label_9->setMaximumSize(QSize(60, 16777215));
        label_9->setFrameShape(QFrame::NoFrame);
        label_9->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label_9);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(2);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        comboBox_2 = new QComboBox(layoutWidget2);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));

        verticalLayout_4->addWidget(comboBox_2);

        textEdit = new QTextEdit(layoutWidget2);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        verticalLayout_4->addWidget(textEdit);


        horizontalLayout_2->addLayout(verticalLayout_4);


        verticalLayout_8->addLayout(horizontalLayout_2);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_11 = new QLabel(layoutWidget2);
        label_11->setObjectName(QStringLiteral("label_11"));
        sizePolicy1.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy1);
        label_11->setMinimumSize(QSize(60, 0));
        label_11->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_9->addWidget(label_11);

        progressBar = new QProgressBar(layoutWidget2);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(progressBar->sizePolicy().hasHeightForWidth());
        progressBar->setSizePolicy(sizePolicy2);
        progressBar->setValue(0);

        horizontalLayout_9->addWidget(progressBar);


        verticalLayout_8->addLayout(horizontalLayout_9);


        verticalLayout_9->addLayout(verticalLayout_8);

        splitter_2->addWidget(layoutWidget2);
        layoutWidget3 = new QWidget(splitter_2);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        verticalLayout_2 = new QVBoxLayout(layoutWidget3);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        label = new QLabel(layoutWidget3);
        label->setObjectName(QStringLiteral("label"));
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setMinimumSize(QSize(60, 0));
        label->setMaximumSize(QSize(60, 16777215));
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_7->addWidget(label);

        listView_2 = new QListView(layoutWidget3);
        listView_2->setObjectName(QStringLiteral("listView_2"));

        verticalLayout_7->addWidget(listView_2);


        verticalLayout_2->addLayout(verticalLayout_7);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        label_10 = new QLabel(layoutWidget3);
        label_10->setObjectName(QStringLiteral("label_10"));
        sizePolicy1.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy1);
        label_10->setMinimumSize(QSize(60, 20));
        label_10->setMaximumSize(QSize(60, 16777215));
        label_10->setFrameShape(QFrame::NoFrame);
        label_10->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_6->addWidget(label_10);

        listView = new QListView(layoutWidget3);
        listView->setObjectName(QStringLiteral("listView"));
        listView->setEditTriggers(QAbstractItemView::NoEditTriggers);

        verticalLayout_6->addWidget(listView);


        verticalLayout_2->addLayout(verticalLayout_6);

        pushButton_7 = new QPushButton(layoutWidget3);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));

        verticalLayout_2->addWidget(pushButton_7);

        pushButton_8 = new QPushButton(layoutWidget3);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));

        verticalLayout_2->addWidget(pushButton_8);

        pushButton_9 = new QPushButton(layoutWidget3);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(pushButton_9->sizePolicy().hasHeightForWidth());
        pushButton_9->setSizePolicy(sizePolicy3);

        verticalLayout_2->addWidget(pushButton_9);

        splitter_2->addWidget(layoutWidget3);

        gridLayout_2->addWidget(splitter_2, 0, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());

        horizontalLayout->addWidget(tabWidget);

        WwMail->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(WwMail);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1200, 22));
        menu_M = new QMenu(menuBar);
        menu_M->setObjectName(QStringLiteral("menu_M"));
        menu_A = new QMenu(menuBar);
        menu_A->setObjectName(QStringLiteral("menu_A"));
        menu_H = new QMenu(menuBar);
        menu_H->setObjectName(QStringLiteral("menu_H"));
        WwMail->setMenuBar(menuBar);
        statusBar = new QStatusBar(WwMail);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        statusBar->setFont(font);
        WwMail->setStatusBar(statusBar);

        menuBar->addAction(menu_M->menuAction());
        menuBar->addAction(menu_A->menuAction());
        menuBar->addAction(menu_H->menuAction());
        menu_M->addAction(action_Q);
        menu_A->addAction(action_L);
        menu_A->addAction(action_R);
        menu_A->addSeparator();
        menu_A->addAction(action_M);
        menu_H->addAction(action_A);

        retranslateUi(WwMail);
        QObject::connect(action_Q, SIGNAL(triggered()), WwMail, SLOT(close()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(WwMail);
    } // setupUi

    void retranslateUi(QMainWindow *WwMail)
    {
        WwMail->setWindowTitle(QApplication::translate("WwMail", "WwMail", 0));
        action_Q->setText(QApplication::translate("WwMail", "\351\200\200\345\207\272(&Q)", 0));
        action_M->setText(QApplication::translate("WwMail", "\345\270\220\345\217\267\347\256\241\347\220\206(&M)", 0));
        action_L->setText(QApplication::translate("WwMail", "\346\267\273\345\212\240\345\270\220\345\217\267(&A)", 0));
        action_A->setText(QApplication::translate("WwMail", "\345\205\263\344\272\216(&A)", 0));
        action_R->setText(QApplication::translate("WwMail", "\351\207\215\346\226\260\350\277\236\346\216\245(&R)", 0));
#ifndef QT_NO_TOOLTIP
        treeView->setToolTip(QApplication::translate("WwMail", "\345\217\214\345\207\273\345\261\225\345\274\200\346\210\226\346\217\220\345\217\226\351\202\256\344\273\266\345\210\227\350\241\250", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        treeView->setStatusTip(QApplication::translate("WwMail", "\351\200\211\346\213\251\351\202\256\347\256\261", 0));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_TOOLTIP
        Mailtable->setToolTip(QApplication::translate("WwMail", "\345\217\214\345\207\273\346\237\245\347\234\213\345\256\214\346\225\264\344\277\241\346\201\257", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        Mailtable->setStatusTip(QApplication::translate("WwMail", "\346\237\245\347\234\213\351\202\256\344\273\266\345\210\227\350\241\250", 0));
#endif // QT_NO_STATUSTIP
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("WwMail", "\346\224\266\351\202\256\344\273\266", 0));
        label_6->setText(QApplication::translate("WwMail", "\346\224\266\344\273\266\344\272\272\357\274\232", 0));
        pushButton_3->setText(QApplication::translate("WwMail", "\346\267\273\345\212\240\346\212\204\351\200\201", 0));
        pushButton_4->setText(QApplication::translate("WwMail", "\346\267\273\345\212\240\345\257\206\351\200\201", 0));
        label_12->setText(QApplication::translate("WwMail", "\346\212\204\351\200\201\357\274\232", 0));
        label_13->setText(QApplication::translate("WwMail", "\345\257\206\351\200\201\357\274\232", 0));
        label_7->setText(QApplication::translate("WwMail", "\344\270\273\351\242\230\357\274\232", 0));
        pushButton_5->setText(QApplication::translate("WwMail", "\346\267\273\345\212\240\351\231\204\344\273\266", 0));
        label_8->setText(QApplication::translate("WwMail", "\345\217\221\344\273\266\344\272\272\357\274\232", 0));
        lineEdit_5->setText(QString());
        pushButton_6->setText(QApplication::translate("WwMail", "\347\274\226\350\276\221\345\270\220\345\217\267", 0));
        label_9->setText(QApplication::translate("WwMail", "\346\255\243\346\226\207\357\274\232", 0));
        label_11->setText(QApplication::translate("WwMail", "\345\217\221\351\200\201\350\277\233\345\272\246\357\274\232", 0));
        label->setText(QApplication::translate("WwMail", "\351\231\204\344\273\266\345\210\227\350\241\250", 0));
        label_10->setText(QApplication::translate("WwMail", "\345\270\270\347\224\250\350\201\224\347\263\273\344\272\272", 0));
        pushButton_7->setText(QApplication::translate("WwMail", "\350\257\273\345\217\226\350\215\211\347\250\277", 0));
        pushButton_8->setText(QApplication::translate("WwMail", "\345\255\230\344\270\272\350\215\211\347\250\277", 0));
        pushButton_9->setText(QApplication::translate("WwMail", "\347\253\213\345\215\263\345\217\221\351\200\201", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("WwMail", "\345\206\231\351\202\256\344\273\266", 0));
        menu_M->setTitle(QApplication::translate("WwMail", "\350\217\234\345\215\225(&M)", 0));
        menu_A->setTitle(QApplication::translate("WwMail", "\345\270\220\345\217\267(&A)", 0));
        menu_H->setTitle(QApplication::translate("WwMail", "\345\270\256\345\212\251(&H)", 0));
    } // retranslateUi

};

namespace Ui {
    class WwMail: public Ui_WwMail {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WWMAIL_H
