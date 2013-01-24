/********************************************************************************
** Form generated from reading UI file 'startwindow.ui'
**
** Created: Sun 9. Dec 23:41:52 2012
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTWINDOW_H
#define UI_STARTWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_startWindow
{
public:
    QAction *actionStartGame;
    QAction *actionInternet_Game;
    QAction *actionAboutPokerTraining;
    QAction *actionConfigurePokerTraining;
    QAction *actionQuit;
    QAction *actionCreate_Network_Game;
    QAction *actionJoin_Network_Game;
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QSpacerItem *spacerItem;
    QSpacerItem *spacerItem1;
    QGridLayout *gridLayout;
    QPushButton *pushButtonStartGame;
    QSpacerItem *spacerItem2;
    QSpacerItem *spacerItem3;
    QMenuBar *menubar;
    QMenu *menuSettings;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *startWindow)
    {
        if (startWindow->objectName().isEmpty())
            startWindow->setObjectName(QString::fromUtf8("startWindow"));
        startWindow->resize(450, 350);
        startWindow->setMinimumSize(QSize(450, 350));
        startWindow->setMaximumSize(QSize(450, 350));
        actionStartGame = new QAction(startWindow);
        actionStartGame->setObjectName(QString::fromUtf8("actionStartGame"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/gfx/swbuttonlocalgame.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionStartGame->setIcon(icon);
        actionInternet_Game = new QAction(startWindow);
        actionInternet_Game->setObjectName(QString::fromUtf8("actionInternet_Game"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/gfx/swbuttoninternetgame.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionInternet_Game->setIcon(icon1);
        actionAboutPokerTraining = new QAction(startWindow);
        actionAboutPokerTraining->setObjectName(QString::fromUtf8("actionAboutPokerTraining"));
        actionConfigurePokerTraining = new QAction(startWindow);
        actionConfigurePokerTraining->setObjectName(QString::fromUtf8("actionConfigurePokerTraining"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/gfx/systemsettings.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionConfigurePokerTraining->setIcon(icon2);
        actionQuit = new QAction(startWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/gfx/application_exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionQuit->setIcon(icon3);
        actionCreate_Network_Game = new QAction(startWindow);
        actionCreate_Network_Game->setObjectName(QString::fromUtf8("actionCreate_Network_Game"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/gfx/swbuttoncreatenetworkgame.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCreate_Network_Game->setIcon(icon4);
        actionJoin_Network_Game = new QAction(startWindow);
        actionJoin_Network_Game->setObjectName(QString::fromUtf8("actionJoin_Network_Game"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/gfx/swbuttonjoinnetworkgame.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionJoin_Network_Game->setIcon(icon5);
        centralwidget = new QWidget(startWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        spacerItem = new QSpacerItem(20, 95, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(spacerItem, 0, 1, 1, 1);

        spacerItem1 = new QSpacerItem(63, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(spacerItem1, 1, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButtonStartGame = new QPushButton(centralwidget);
        pushButtonStartGame->setObjectName(QString::fromUtf8("pushButtonStartGame"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButtonStartGame->sizePolicy().hasHeightForWidth());
        pushButtonStartGame->setSizePolicy(sizePolicy);
        pushButtonStartGame->setFocusPolicy(Qt::NoFocus);
        pushButtonStartGame->setIcon(icon);
        pushButtonStartGame->setIconSize(QSize(37, 32));

        gridLayout->addWidget(pushButtonStartGame, 0, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 1, 1, 1, 1);

        spacerItem2 = new QSpacerItem(63, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(spacerItem2, 1, 2, 1, 1);

        spacerItem3 = new QSpacerItem(20, 95, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(spacerItem3, 2, 1, 1, 1);

        startWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(startWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 450, 18));
        menuSettings = new QMenu(menubar);
        menuSettings->setObjectName(QString::fromUtf8("menuSettings"));
        startWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(startWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        startWindow->setStatusBar(statusbar);

        menubar->addAction(menuSettings->menuAction());
        menuSettings->addAction(actionConfigurePokerTraining);

        retranslateUi(startWindow);
        QObject::connect(actionQuit, SIGNAL(triggered()), startWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(startWindow);
    } // setupUi

    void retranslateUi(QMainWindow *startWindow)
    {
        startWindow->setWindowTitle(QApplication::translate("startWindow", "PokerTrain 0.9 - Holdem No Limit Sit'n Go Training", 0, QApplication::UnicodeUTF8));
        actionStartGame->setText(QApplication::translate("startWindow", "Start Local Game ...", 0, QApplication::UnicodeUTF8));
        actionStartGame->setShortcut(QApplication::translate("startWindow", "Ctrl+N", 0, QApplication::UnicodeUTF8));
        actionInternet_Game->setText(QApplication::translate("startWindow", "Internet Game ...", 0, QApplication::UnicodeUTF8));
        actionInternet_Game->setShortcut(QApplication::translate("startWindow", "Ctrl+I", 0, QApplication::UnicodeUTF8));
        actionAboutPokerTraining->setText(QApplication::translate("startWindow", "About PokerTH", 0, QApplication::UnicodeUTF8));
        actionConfigurePokerTraining->setText(QApplication::translate("startWindow", "Configure PokerTraining ...", 0, QApplication::UnicodeUTF8));
        actionQuit->setText(QApplication::translate("startWindow", "Quit", 0, QApplication::UnicodeUTF8));
        actionQuit->setShortcut(QApplication::translate("startWindow", "Ctrl+Q", 0, QApplication::UnicodeUTF8));
        actionCreate_Network_Game->setText(QApplication::translate("startWindow", "Create Network Game ...", 0, QApplication::UnicodeUTF8));
        actionJoin_Network_Game->setText(QApplication::translate("startWindow", "Join Network Game ...", 0, QApplication::UnicodeUTF8));
        pushButtonStartGame->setText(QApplication::translate("startWindow", "Start game", 0, QApplication::UnicodeUTF8));
        menuSettings->setTitle(QApplication::translate("startWindow", "&Settings", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class startWindow: public Ui_startWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTWINDOW_H
