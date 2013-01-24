/********************************************************************************
** Form generated from reading UI file 'aboutpokertraining.ui'
**
** Created: Sun 9. Dec 12:11:07 2012
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTPOKERTRAINING_H
#define UI_ABOUTPOKERTRAINING_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QTextBrowser>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_aboutPokerTraining
{
public:
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout1;
    QLabel *label_PokerTrainingVersion;
    QLabel *label_logo;
    QLabel *label_infotext;
    QSpacerItem *spacerItem;
    QSpacerItem *spacerItem1;
    QLabel *label_3;
    QWidget *tab_2;
    QGridLayout *gridLayout2;
    QTextBrowser *textBrowser_2;
    QWidget *tab_5;
    QGridLayout *gridLayout3;
    QTextBrowser *textBrowser_4;
    QWidget *tab_4;
    QGridLayout *gridLayout4;
    QTextBrowser *textBrowser_3;
    QWidget *tab_3;
    QGridLayout *gridLayout5;
    QTextBrowser *textBrowser_licence;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem2;
    QPushButton *okButton;

    void setupUi(QDialog *aboutPokerTraining)
    {
        if (aboutPokerTraining->objectName().isEmpty())
            aboutPokerTraining->setObjectName(QString::fromUtf8("aboutPokerTraining"));
        aboutPokerTraining->resize(560, 415);
        gridLayout = new QGridLayout(aboutPokerTraining);
#ifndef Q_OS_MAC
        gridLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        gridLayout->setContentsMargins(9, 9, 9, 9);
#endif
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tabWidget = new QTabWidget(aboutPokerTraining);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setAutoFillBackground(true);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout1 = new QGridLayout(tab);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        label_PokerTrainingVersion = new QLabel(tab);
        label_PokerTrainingVersion->setObjectName(QString::fromUtf8("label_PokerTrainingVersion"));

        gridLayout1->addWidget(label_PokerTrainingVersion, 0, 0, 1, 1);

        label_logo = new QLabel(tab);
        label_logo->setObjectName(QString::fromUtf8("label_logo"));

        gridLayout1->addWidget(label_logo, 0, 1, 2, 1);

        label_infotext = new QLabel(tab);
        label_infotext->setObjectName(QString::fromUtf8("label_infotext"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_infotext->sizePolicy().hasHeightForWidth());
        label_infotext->setSizePolicy(sizePolicy);
        label_infotext->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        label_infotext->setOpenExternalLinks(true);

        gridLayout1->addWidget(label_infotext, 1, 0, 2, 1);

        spacerItem = new QSpacerItem(20, 100, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout1->addItem(spacerItem, 2, 1, 2, 1);

        spacerItem1 = new QSpacerItem(20, 91, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout1->addItem(spacerItem1, 3, 0, 1, 1);

        label_3 = new QLabel(tab);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_3->setOpenExternalLinks(true);

        gridLayout1->addWidget(label_3, 4, 0, 1, 2);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        gridLayout2 = new QGridLayout(tab_2);
#ifndef Q_OS_MAC
        gridLayout2->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        gridLayout2->setContentsMargins(9, 9, 9, 9);
#endif
        gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
        textBrowser_2 = new QTextBrowser(tab_2);
        textBrowser_2->setObjectName(QString::fromUtf8("textBrowser_2"));
        textBrowser_2->setLineWrapMode(QTextEdit::NoWrap);
        textBrowser_2->setOpenExternalLinks(true);

        gridLayout2->addWidget(textBrowser_2, 0, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        gridLayout3 = new QGridLayout(tab_5);
#ifndef Q_OS_MAC
        gridLayout3->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        gridLayout3->setContentsMargins(9, 9, 9, 9);
#endif
        gridLayout3->setObjectName(QString::fromUtf8("gridLayout3"));
        textBrowser_4 = new QTextBrowser(tab_5);
        textBrowser_4->setObjectName(QString::fromUtf8("textBrowser_4"));
        textBrowser_4->setOpenExternalLinks(true);

        gridLayout3->addWidget(textBrowser_4, 0, 0, 1, 1);

        tabWidget->addTab(tab_5, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        gridLayout4 = new QGridLayout(tab_4);
#ifndef Q_OS_MAC
        gridLayout4->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        gridLayout4->setContentsMargins(9, 9, 9, 9);
#endif
        gridLayout4->setObjectName(QString::fromUtf8("gridLayout4"));
        textBrowser_3 = new QTextBrowser(tab_4);
        textBrowser_3->setObjectName(QString::fromUtf8("textBrowser_3"));
        textBrowser_3->setAcceptRichText(false);
        textBrowser_3->setOpenExternalLinks(false);
        textBrowser_3->setOpenLinks(false);

        gridLayout4->addWidget(textBrowser_3, 0, 0, 1, 1);

        tabWidget->addTab(tab_4, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        gridLayout5 = new QGridLayout(tab_3);
#ifndef Q_OS_MAC
        gridLayout5->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        gridLayout5->setContentsMargins(9, 9, 9, 9);
#endif
        gridLayout5->setObjectName(QString::fromUtf8("gridLayout5"));
        textBrowser_licence = new QTextBrowser(tab_3);
        textBrowser_licence->setObjectName(QString::fromUtf8("textBrowser_licence"));
        textBrowser_licence->setAutoFillBackground(true);
        textBrowser_licence->setOpenLinks(false);

        gridLayout5->addWidget(textBrowser_licence, 0, 0, 1, 1);

        tabWidget->addTab(tab_3, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);

        hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        spacerItem2 = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem2);

        okButton = new QPushButton(aboutPokerTraining);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        hboxLayout->addWidget(okButton);


        gridLayout->addLayout(hboxLayout, 1, 0, 1, 1);


        retranslateUi(aboutPokerTraining);
        QObject::connect(okButton, SIGNAL(clicked()), aboutPokerTraining, SLOT(accept()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(aboutPokerTraining);
    } // setupUi

    void retranslateUi(QDialog *aboutPokerTraining)
    {
        label_infotext->setText(QString());
        label_3->setText(QApplication::translate("aboutPokerTraining", "<a href=\"http://www.pokerth.net\" target=\"_blank\">http://www.pokerth.net<a>", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("aboutPokerTraining", "About", 0, QApplication::UnicodeUTF8));
        textBrowser_2->setHtml(QApplication::translate("aboutPokerTraining", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Nimbus Sans L'; font-size:9pt;\"><br /></p></body></html>", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("aboutPokerTraining", "Project", 0, QApplication::UnicodeUTF8));
        textBrowser_4->setHtml(QApplication::translate("aboutPokerTraining", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<table border=\"0\" style=\"-qt-table-type: root; margin-top:4px; margin-bottom:4px; margin-left:4px; margin-right:4px;\">\n"
"<tr>\n"
"<td style=\"border: none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Nimbus Sans L'; font-size:8pt;\">translator name - mail address</span></p></td></tr></table></body></html>", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QApplication::translate("aboutPokerTraining", "Translation", 0, QApplication::UnicodeUTF8));
        textBrowser_3->setHtml(QApplication::translate("aboutPokerTraining", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Nimbus Sans L'; font-size:9pt;\"><br /></p></body></html>", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("aboutPokerTraining", "Thanks to", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("aboutPokerTraining", "License", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("aboutPokerTraining", "Close", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(aboutPokerTraining);
    } // retranslateUi

};

namespace Ui {
    class aboutPokerTraining: public Ui_aboutPokerTraining {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTPOKERTRAINING_H
