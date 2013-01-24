/********************************************************************************
** Form generated from reading UI file 'changecompleteblindsdialog.ui'
**
** Created: Sun 9. Dec 12:11:07 2012
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANGECOMPLETEBLINDSDIALOG_H
#define UI_CHANGECOMPLETEBLINDSDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_changeCompleteBlindsDialog
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *hboxLayout;
    QLabel *label_3;
    QSpinBox *spinBox_firstSmallBlind;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout1;
    QRadioButton *radioButton_raiseBlindsAtHands;
    QSpinBox *spinBox_raiseSmallBlindEveryHands;
    QLabel *label_47;
    QRadioButton *radioButton_raiseBlindsAtMinutes;
    QSpinBox *spinBox_raiseSmallBlindEveryMinutes;
    QLabel *label_50;
    QGroupBox *groupBox_7;
    QGridLayout *gridLayout2;
    QRadioButton *radioButton_alwaysDoubleBlinds;
    QRadioButton *radioButton_manualBlindsOrder;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout3;
    QGridLayout *gridLayout4;
    QListWidget *listWidget_blinds;
    QPushButton *pushButton_delete;
    QSpacerItem *spacerItem;
    QSpinBox *spinBox_input;
    QPushButton *pushButton_add;
    QSpacerItem *spacerItem1;
    QGroupBox *groupBox;
    QGridLayout *gridLayout5;
    QRadioButton *radioButton_afterThisAlwaysDoubleBlinds;
    QHBoxLayout *hboxLayout1;
    QRadioButton *radioButton_afterThisAlwaysRaiseAbout;
    QSpinBox *spinBox_afterThisAlwaysRaiseValue;
    QLabel *label;
    QRadioButton *radioButton_afterThisStayAtLastBlind;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *changeCompleteBlindsDialog)
    {
        if (changeCompleteBlindsDialog->objectName().isEmpty())
            changeCompleteBlindsDialog->setObjectName(QString::fromUtf8("changeCompleteBlindsDialog"));
        changeCompleteBlindsDialog->resize(454, 397);
        gridLayout = new QGridLayout(changeCompleteBlindsDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        label_3 = new QLabel(changeCompleteBlindsDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        hboxLayout->addWidget(label_3);

        spinBox_firstSmallBlind = new QSpinBox(changeCompleteBlindsDialog);
        spinBox_firstSmallBlind->setObjectName(QString::fromUtf8("spinBox_firstSmallBlind"));
        spinBox_firstSmallBlind->setMinimum(5);
        spinBox_firstSmallBlind->setMaximum(20000);

        hboxLayout->addWidget(spinBox_firstSmallBlind);


        gridLayout->addLayout(hboxLayout, 0, 0, 1, 2);

        groupBox_6 = new QGroupBox(changeCompleteBlindsDialog);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        gridLayout1 = new QGridLayout(groupBox_6);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        gridLayout1->setContentsMargins(9, 0, -1, 9);
        radioButton_raiseBlindsAtHands = new QRadioButton(groupBox_6);
        radioButton_raiseBlindsAtHands->setObjectName(QString::fromUtf8("radioButton_raiseBlindsAtHands"));
        radioButton_raiseBlindsAtHands->setChecked(true);

        gridLayout1->addWidget(radioButton_raiseBlindsAtHands, 0, 0, 1, 1);

        spinBox_raiseSmallBlindEveryHands = new QSpinBox(groupBox_6);
        spinBox_raiseSmallBlindEveryHands->setObjectName(QString::fromUtf8("spinBox_raiseSmallBlindEveryHands"));
        spinBox_raiseSmallBlindEveryHands->setMinimum(1);

        gridLayout1->addWidget(spinBox_raiseSmallBlindEveryHands, 0, 1, 1, 1);

        label_47 = new QLabel(groupBox_6);
        label_47->setObjectName(QString::fromUtf8("label_47"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_47->sizePolicy().hasHeightForWidth());
        label_47->setSizePolicy(sizePolicy);

        gridLayout1->addWidget(label_47, 0, 2, 1, 1);

        radioButton_raiseBlindsAtMinutes = new QRadioButton(groupBox_6);
        radioButton_raiseBlindsAtMinutes->setObjectName(QString::fromUtf8("radioButton_raiseBlindsAtMinutes"));

        gridLayout1->addWidget(radioButton_raiseBlindsAtMinutes, 1, 0, 1, 1);

        spinBox_raiseSmallBlindEveryMinutes = new QSpinBox(groupBox_6);
        spinBox_raiseSmallBlindEveryMinutes->setObjectName(QString::fromUtf8("spinBox_raiseSmallBlindEveryMinutes"));
        spinBox_raiseSmallBlindEveryMinutes->setMinimum(1);

        gridLayout1->addWidget(spinBox_raiseSmallBlindEveryMinutes, 1, 1, 1, 1);

        label_50 = new QLabel(groupBox_6);
        label_50->setObjectName(QString::fromUtf8("label_50"));
        sizePolicy.setHeightForWidth(label_50->sizePolicy().hasHeightForWidth());
        label_50->setSizePolicy(sizePolicy);

        gridLayout1->addWidget(label_50, 1, 2, 1, 1);


        gridLayout->addWidget(groupBox_6, 1, 0, 1, 1);

        groupBox_7 = new QGroupBox(changeCompleteBlindsDialog);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        sizePolicy.setHeightForWidth(groupBox_7->sizePolicy().hasHeightForWidth());
        groupBox_7->setSizePolicy(sizePolicy);
        gridLayout2 = new QGridLayout(groupBox_7);
        gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
        gridLayout2->setContentsMargins(-1, 0, -1, -1);
        radioButton_alwaysDoubleBlinds = new QRadioButton(groupBox_7);
        radioButton_alwaysDoubleBlinds->setObjectName(QString::fromUtf8("radioButton_alwaysDoubleBlinds"));
        radioButton_alwaysDoubleBlinds->setChecked(true);

        gridLayout2->addWidget(radioButton_alwaysDoubleBlinds, 0, 0, 1, 1);

        radioButton_manualBlindsOrder = new QRadioButton(groupBox_7);
        radioButton_manualBlindsOrder->setObjectName(QString::fromUtf8("radioButton_manualBlindsOrder"));

        gridLayout2->addWidget(radioButton_manualBlindsOrder, 1, 0, 1, 1);


        gridLayout->addWidget(groupBox_7, 1, 1, 1, 1);

        groupBox_2 = new QGroupBox(changeCompleteBlindsDialog);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setEnabled(false);
        gridLayout3 = new QGridLayout(groupBox_2);
        gridLayout3->setObjectName(QString::fromUtf8("gridLayout3"));
        gridLayout4 = new QGridLayout();
        gridLayout4->setObjectName(QString::fromUtf8("gridLayout4"));
        gridLayout4->setHorizontalSpacing(4);
        listWidget_blinds = new QListWidget(groupBox_2);
        listWidget_blinds->setObjectName(QString::fromUtf8("listWidget_blinds"));

        gridLayout4->addWidget(listWidget_blinds, 0, 0, 2, 1);

        pushButton_delete = new QPushButton(groupBox_2);
        pushButton_delete->setObjectName(QString::fromUtf8("pushButton_delete"));

        gridLayout4->addWidget(pushButton_delete, 0, 1, 1, 1);

        spacerItem = new QSpacerItem(20, 121, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout4->addItem(spacerItem, 1, 1, 1, 1);

        spinBox_input = new QSpinBox(groupBox_2);
        spinBox_input->setObjectName(QString::fromUtf8("spinBox_input"));
        spinBox_input->setMaximum(20000);

        gridLayout4->addWidget(spinBox_input, 2, 0, 1, 1);

        pushButton_add = new QPushButton(groupBox_2);
        pushButton_add->setObjectName(QString::fromUtf8("pushButton_add"));

        gridLayout4->addWidget(pushButton_add, 2, 1, 1, 1);


        gridLayout3->addLayout(gridLayout4, 0, 0, 2, 1);

        spacerItem1 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout3->addItem(spacerItem1, 0, 1, 1, 1);

        groupBox = new QGroupBox(groupBox_2);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout5 = new QGridLayout(groupBox);
        gridLayout5->setObjectName(QString::fromUtf8("gridLayout5"));
        gridLayout5->setContentsMargins(-1, 0, -1, -1);
        radioButton_afterThisAlwaysDoubleBlinds = new QRadioButton(groupBox);
        radioButton_afterThisAlwaysDoubleBlinds->setObjectName(QString::fromUtf8("radioButton_afterThisAlwaysDoubleBlinds"));
        radioButton_afterThisAlwaysDoubleBlinds->setChecked(true);

        gridLayout5->addWidget(radioButton_afterThisAlwaysDoubleBlinds, 0, 0, 1, 1);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        radioButton_afterThisAlwaysRaiseAbout = new QRadioButton(groupBox);
        radioButton_afterThisAlwaysRaiseAbout->setObjectName(QString::fromUtf8("radioButton_afterThisAlwaysRaiseAbout"));

        hboxLayout1->addWidget(radioButton_afterThisAlwaysRaiseAbout);

        spinBox_afterThisAlwaysRaiseValue = new QSpinBox(groupBox);
        spinBox_afterThisAlwaysRaiseValue->setObjectName(QString::fromUtf8("spinBox_afterThisAlwaysRaiseValue"));
        spinBox_afterThisAlwaysRaiseValue->setMaximum(20000);

        hboxLayout1->addWidget(spinBox_afterThisAlwaysRaiseValue);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        hboxLayout1->addWidget(label);


        gridLayout5->addLayout(hboxLayout1, 1, 0, 1, 1);

        radioButton_afterThisStayAtLastBlind = new QRadioButton(groupBox);
        radioButton_afterThisStayAtLastBlind->setObjectName(QString::fromUtf8("radioButton_afterThisStayAtLastBlind"));

        gridLayout5->addWidget(radioButton_afterThisStayAtLastBlind, 2, 0, 1, 1);


        gridLayout3->addWidget(groupBox, 1, 1, 1, 1);


        gridLayout->addWidget(groupBox_2, 2, 0, 1, 2);

        buttonBox = new QDialogButtonBox(changeCompleteBlindsDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 3, 0, 1, 2);

        QWidget::setTabOrder(spinBox_firstSmallBlind, radioButton_raiseBlindsAtHands);
        QWidget::setTabOrder(radioButton_raiseBlindsAtHands, spinBox_raiseSmallBlindEveryHands);
        QWidget::setTabOrder(spinBox_raiseSmallBlindEveryHands, radioButton_raiseBlindsAtMinutes);
        QWidget::setTabOrder(radioButton_raiseBlindsAtMinutes, spinBox_raiseSmallBlindEveryMinutes);
        QWidget::setTabOrder(spinBox_raiseSmallBlindEveryMinutes, radioButton_alwaysDoubleBlinds);
        QWidget::setTabOrder(radioButton_alwaysDoubleBlinds, radioButton_manualBlindsOrder);
        QWidget::setTabOrder(radioButton_manualBlindsOrder, listWidget_blinds);
        QWidget::setTabOrder(listWidget_blinds, spinBox_input);
        QWidget::setTabOrder(spinBox_input, pushButton_add);
        QWidget::setTabOrder(pushButton_add, pushButton_delete);
        QWidget::setTabOrder(pushButton_delete, radioButton_afterThisAlwaysDoubleBlinds);
        QWidget::setTabOrder(radioButton_afterThisAlwaysDoubleBlinds, radioButton_afterThisAlwaysRaiseAbout);
        QWidget::setTabOrder(radioButton_afterThisAlwaysRaiseAbout, spinBox_afterThisAlwaysRaiseValue);
        QWidget::setTabOrder(spinBox_afterThisAlwaysRaiseValue, radioButton_afterThisStayAtLastBlind);
        QWidget::setTabOrder(radioButton_afterThisStayAtLastBlind, buttonBox);

        retranslateUi(changeCompleteBlindsDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), changeCompleteBlindsDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), changeCompleteBlindsDialog, SLOT(reject()));
        QObject::connect(radioButton_afterThisAlwaysRaiseAbout, SIGNAL(toggled(bool)), spinBox_afterThisAlwaysRaiseValue, SLOT(setEnabled(bool)));
        QObject::connect(radioButton_manualBlindsOrder, SIGNAL(toggled(bool)), groupBox_2, SLOT(setEnabled(bool)));

        QMetaObject::connectSlotsByName(changeCompleteBlindsDialog);
    } // setupUi

    void retranslateUi(QDialog *changeCompleteBlindsDialog)
    {
        changeCompleteBlindsDialog->setWindowTitle(QApplication::translate("changeCompleteBlindsDialog", "Change Blinds Settings", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("changeCompleteBlindsDialog", "First small blind:", 0, QApplication::UnicodeUTF8));
        groupBox_6->setTitle(QApplication::translate("changeCompleteBlindsDialog", "Raise blinds:", 0, QApplication::UnicodeUTF8));
        radioButton_raiseBlindsAtHands->setText(QApplication::translate("changeCompleteBlindsDialog", "Every:", 0, QApplication::UnicodeUTF8));
        label_47->setText(QApplication::translate("changeCompleteBlindsDialog", "hands", 0, QApplication::UnicodeUTF8));
        radioButton_raiseBlindsAtMinutes->setText(QApplication::translate("changeCompleteBlindsDialog", "Every:", 0, QApplication::UnicodeUTF8));
        label_50->setText(QApplication::translate("changeCompleteBlindsDialog", "minutes", 0, QApplication::UnicodeUTF8));
        groupBox_7->setTitle(QApplication::translate("changeCompleteBlindsDialog", "Raise mode:", 0, QApplication::UnicodeUTF8));
        radioButton_alwaysDoubleBlinds->setText(QApplication::translate("changeCompleteBlindsDialog", "Always double blinds", 0, QApplication::UnicodeUTF8));
        radioButton_manualBlindsOrder->setText(QApplication::translate("changeCompleteBlindsDialog", "Manual blinds order:", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("changeCompleteBlindsDialog", "Manual blinds order:", 0, QApplication::UnicodeUTF8));
        pushButton_delete->setText(QApplication::translate("changeCompleteBlindsDialog", "Delete", 0, QApplication::UnicodeUTF8));
        pushButton_add->setText(QApplication::translate("changeCompleteBlindsDialog", "Add", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("changeCompleteBlindsDialog", "Afterwards:", 0, QApplication::UnicodeUTF8));
        radioButton_afterThisAlwaysDoubleBlinds->setText(QApplication::translate("changeCompleteBlindsDialog", "Always double blinds", 0, QApplication::UnicodeUTF8));
        radioButton_afterThisAlwaysRaiseAbout->setText(QApplication::translate("changeCompleteBlindsDialog", "Always raise by:", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("changeCompleteBlindsDialog", "$", 0, QApplication::UnicodeUTF8));
        radioButton_afterThisStayAtLastBlind->setText(QApplication::translate("changeCompleteBlindsDialog", "Keep last blind", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class changeCompleteBlindsDialog: public Ui_changeCompleteBlindsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANGECOMPLETEBLINDSDIALOG_H
