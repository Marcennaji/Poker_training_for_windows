/********************************************************************************
** Form generated from reading UI file 'settingsdialog.ui'
**
** Created: Fri 4. Jan 18:23:57 2013
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSDIALOG_H
#define UI_SETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QStackedWidget>
#include <QtGui/QTabWidget>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "myavatarbutton.h"
#include "myhpavatarbutton.h"

QT_BEGIN_NAMESPACE

class Ui_settingsDialog
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *hboxLayout;
    QListWidget *listWidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QGridLayout *gridLayout_8;
    QLabel *label_19;
    QFrame *line_6;
    QHBoxLayout *hboxLayout1;
    QLabel *label_14;
    QComboBox *comboBox_switchLanguage;
    QSpacerItem *spacerItem;
    QGridLayout *gridLayout_7;
    QCheckBox *checkBox_showBlindButtons;
    QCheckBox *checkBox_showFadeOutCardsAnimation;
    QCheckBox *checkBox_dontTranslatePokerStrings;
    QCheckBox *checkBox_antiPeekMode;
    QCheckBox *checkBox_showFlipCardsAnimation;
    QCheckBox *checkBox_showPlayersStatistics;
    QCheckBox *checkBox_showRightToolbox;
    QSpacerItem *spacerItem1;
    QWidget *page_8;
    QGridLayout *gridLayout_12;
    QLabel *label_28;
    QFrame *line_7;
    QTabWidget *tabWidget;
    QWidget *tab_3;
    QGridLayout *gridLayout_13;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_addGameTableStyle;
    QPushButton *pushButton_removeGameTableStyle;
    QSpacerItem *verticalSpacer_3;
    QGroupBox *groupBox_13;
    QGridLayout *gridLayout_15;
    QLabel *label_gameTableStylePreview;
    QLabel *label_gameTableStyleInfo;
    QLabel *label_55;
    QTreeWidget *treeWidget_gameTableStyles;
    QWidget *tab_4;
    QGridLayout *gridLayout_14;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButton_addCardDeckStyle;
    QPushButton *pushButton_removeCardDeckStyle;
    QSpacerItem *verticalSpacer_333;
    QGroupBox *groupBox_14;
    QGridLayout *gridLayout_16;
    QLabel *label_cardDeckStylePreview;
    QLabel *label_cardDeckStyleInfo;
    QLabel *label_56;
    QTreeWidget *treeWidget_cardDeckStyles;
    QWidget *tab;
    QGridLayout *gridLayout_17;
    QRadioButton *radioButton_flipsideTux;
    QVBoxLayout *_3;
    QHBoxLayout *_10;
    QRadioButton *radioButton_flipsideOwn;
    QLineEdit *lineEdit_OwnFlipsideFilename;
    QPushButton *pushButton_openFlipsidePicture;
    QLabel *label_57;
    QSpacerItem *verticalSpacer_4;
    QWidget *page_6;
    QGridLayout *gridLayout1;
    QLabel *label_26;
    QFrame *line_8;
    QGroupBox *groupBox_playSoundEffects;
    QGridLayout *gridLayout2;
    QHBoxLayout *hboxLayout2;
    QLabel *label_25;
    QLabel *label_soundVolume;
    QSlider *horizontalSlider_soundVolume;
    QGroupBox *groupBox_10;
    QGridLayout *gridLayout3;
    QCheckBox *checkBox_playGameActions;
    QCheckBox *checkBox_playBlindRaiseSound;
    QSpacerItem *spacerItem2;
    QWidget *page_2;
    QVBoxLayout *vboxLayout;
    QLabel *label_5;
    QFrame *line_3;
    QHBoxLayout *hboxLayout3;
    QLabel *label_4;
    QSpinBox *spinBox_quantityPlayers;
    QHBoxLayout *hboxLayout4;
    QLabel *label_2;
    QSpinBox *spinBox_startCash;
    QHBoxLayout *hboxLayout5;
    QLabel *label_3;
    QSpinBox *spinBox_firstSmallBlind;
    QHBoxLayout *hboxLayout6;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout4;
    QRadioButton *radioButton_raiseBlindsAtHands;
    QSpinBox *spinBox_raiseSmallBlindEveryHands;
    QLabel *label_47;
    QRadioButton *radioButton_raiseBlindsAtMinutes;
    QSpinBox *spinBox_raiseSmallBlindEveryMinutes;
    QLabel *label_50;
    QSpacerItem *spacerItem3;
    QGroupBox *groupBox_7;
    QGridLayout *gridLayout5;
    QRadioButton *radioButton_alwaysDoubleBlinds;
    QRadioButton *radioButton_manualBlindsOrder;
    QPushButton *pushButton_editManualBlindsOrder;
    QHBoxLayout *hboxLayout7;
    QLabel *label;
    QSpinBox *spinBox_gameSpeed;
    QCheckBox *checkBox_pauseBetweenHands;
    QCheckBox *checkBox_showGameSettingsDialogOnNewGame;
    QSpacerItem *spacerItem4;
    QWidget *page_3;
    QGridLayout *gridLayout_10;
    QLabel *label_7;
    QFrame *line_4;
    QGridLayout *gridLayout_9;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_8;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    MyHPAvatarButton *pushButton_HumanPlayerAvatar;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_6;
    QLineEdit *lineEdit_HumanPlayerName;
    QSpacerItem *horizontalSpacer_7;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_11;
    QHBoxLayout *horizontalLayout_3;
    QGridLayout *gridLayout6;
    QLineEdit *lineEdit_Opponent1Name;
    QLabel *label_9;
    QHBoxLayout *hboxLayout8;
    QSpacerItem *spacerItem5;
    MyAvatarButton *pushButton_Opponent1Avatar;
    QSpacerItem *spacerItem6;
    QGridLayout *gridLayout7;
    QLineEdit *lineEdit_Opponent2Name;
    QLabel *label_10;
    QHBoxLayout *hboxLayout9;
    QSpacerItem *spacerItem7;
    MyAvatarButton *pushButton_Opponent2Avatar;
    QSpacerItem *spacerItem8;
    QGridLayout *gridLayout8;
    QLabel *label_11;
    QLineEdit *lineEdit_Opponent3Name;
    QHBoxLayout *hboxLayout10;
    QSpacerItem *spacerItem9;
    MyAvatarButton *pushButton_Opponent3Avatar;
    QSpacerItem *spacerItem10;
    QGridLayout *gridLayout9;
    QLineEdit *lineEdit_Opponent4Name;
    QLabel *label_12;
    QHBoxLayout *hboxLayout11;
    QSpacerItem *spacerItem11;
    MyAvatarButton *pushButton_Opponent4Avatar;
    QSpacerItem *spacerItem12;
    QGridLayout *gridLayout10;
    QLabel *label_20;
    QHBoxLayout *hboxLayout12;
    QSpacerItem *spacerItem13;
    MyAvatarButton *pushButton_Opponent5Avatar;
    QSpacerItem *spacerItem14;
    QLineEdit *lineEdit_Opponent5Name;
    QHBoxLayout *horizontalLayout_4;
    QGridLayout *gridLayout11;
    QHBoxLayout *hboxLayout13;
    QSpacerItem *spacerItem15;
    MyAvatarButton *pushButton_Opponent6Avatar;
    QSpacerItem *spacerItem16;
    QLineEdit *lineEdit_Opponent6Name;
    QLabel *label_21;
    QGridLayout *_4;
    QHBoxLayout *_5;
    QSpacerItem *spacerItem17;
    MyAvatarButton *pushButton_Opponent7Avatar;
    QSpacerItem *spacerItem18;
    QLineEdit *lineEdit_Opponent7Name;
    QLabel *label_33;
    QGridLayout *_6;
    QHBoxLayout *_7;
    QSpacerItem *spacerItem19;
    MyAvatarButton *pushButton_Opponent8Avatar;
    QSpacerItem *spacerItem20;
    QLineEdit *lineEdit_Opponent8Name;
    QLabel *label_53;
    QGridLayout *_8;
    QHBoxLayout *_9;
    QSpacerItem *spacerItem21;
    MyAvatarButton *pushButton_Opponent9Avatar;
    QSpacerItem *spacerItem22;
    QLineEdit *lineEdit_Opponent9Name;
    QLabel *label_54;
    QLabel *label_38;
    QSpacerItem *spacerItem23;
    QWidget *page_9;
    QGridLayout *gridLayout_22;
    QLabel *label_44;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout_10;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *pushButton_resetSettings;
    QSpacerItem *horizontalSpacer_10;
    QSpacerItem *verticalSpacer_6;
    QFrame *line_10;
    QLabel *label_resetNote;
    QFrame *line;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *settingsDialog)
    {
        if (settingsDialog->objectName().isEmpty())
            settingsDialog->setObjectName(QString::fromUtf8("settingsDialog"));
        settingsDialog->resize(785, 530);
        settingsDialog->setMinimumSize(QSize(785, 530));
        gridLayout = new QGridLayout(settingsDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        listWidget = new QListWidget(settingsDialog);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/gfx/preferences-desktop.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(listWidget);
        __qlistwidgetitem->setIcon(icon);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/gfx/fill-color.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem1 = new QListWidgetItem(listWidget);
        __qlistwidgetitem1->setIcon(icon1);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/gfx/speaker.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem2 = new QListWidgetItem(listWidget);
        __qlistwidgetitem2->setIcon(icon2);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/gfx/swbuttonlocalgame.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem3 = new QListWidgetItem(listWidget);
        __qlistwidgetitem3->setIcon(icon3);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setMinimumSize(QSize(190, 0));
        listWidget->setMaximumSize(QSize(190, 16777215));
        listWidget->setIconSize(QSize(32, 32));
        listWidget->setProperty("isWrapping", QVariant(false));
        listWidget->setWordWrap(true);

        hboxLayout->addWidget(listWidget);

        stackedWidget = new QStackedWidget(settingsDialog);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        gridLayout_8 = new QGridLayout(page);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        label_19 = new QLabel(page);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setStyleSheet(QString::fromUtf8("QLabel { font-weight: bold;  }"));

        gridLayout_8->addWidget(label_19, 0, 0, 1, 1);

        line_6 = new QFrame(page);
        line_6->setObjectName(QString::fromUtf8("line_6"));
        line_6->setFrameShape(QFrame::HLine);
        line_6->setFrameShadow(QFrame::Sunken);

        gridLayout_8->addWidget(line_6, 1, 0, 1, 1);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        label_14 = new QLabel(page);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        hboxLayout1->addWidget(label_14);

        comboBox_switchLanguage = new QComboBox(page);
        comboBox_switchLanguage->setObjectName(QString::fromUtf8("comboBox_switchLanguage"));

        hboxLayout1->addWidget(comboBox_switchLanguage);

        spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout1->addItem(spacerItem);


        gridLayout_8->addLayout(hboxLayout1, 2, 0, 1, 1);

        gridLayout_7 = new QGridLayout();
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        checkBox_showBlindButtons = new QCheckBox(page);
        checkBox_showBlindButtons->setObjectName(QString::fromUtf8("checkBox_showBlindButtons"));

        gridLayout_7->addWidget(checkBox_showBlindButtons, 5, 0, 1, 2);

        checkBox_showFadeOutCardsAnimation = new QCheckBox(page);
        checkBox_showFadeOutCardsAnimation->setObjectName(QString::fromUtf8("checkBox_showFadeOutCardsAnimation"));

        gridLayout_7->addWidget(checkBox_showFadeOutCardsAnimation, 2, 0, 1, 2);

        checkBox_dontTranslatePokerStrings = new QCheckBox(page);
        checkBox_dontTranslatePokerStrings->setObjectName(QString::fromUtf8("checkBox_dontTranslatePokerStrings"));

        gridLayout_7->addWidget(checkBox_dontTranslatePokerStrings, 7, 0, 1, 2);

        checkBox_antiPeekMode = new QCheckBox(page);
        checkBox_antiPeekMode->setObjectName(QString::fromUtf8("checkBox_antiPeekMode"));

        gridLayout_7->addWidget(checkBox_antiPeekMode, 6, 0, 1, 2);

        checkBox_showFlipCardsAnimation = new QCheckBox(page);
        checkBox_showFlipCardsAnimation->setObjectName(QString::fromUtf8("checkBox_showFlipCardsAnimation"));

        gridLayout_7->addWidget(checkBox_showFlipCardsAnimation, 3, 0, 1, 2);

        checkBox_showPlayersStatistics = new QCheckBox(page);
        checkBox_showPlayersStatistics->setObjectName(QString::fromUtf8("checkBox_showPlayersStatistics"));

        gridLayout_7->addWidget(checkBox_showPlayersStatistics, 1, 0, 1, 1);

        checkBox_showRightToolbox = new QCheckBox(page);
        checkBox_showRightToolbox->setObjectName(QString::fromUtf8("checkBox_showRightToolbox"));

        gridLayout_7->addWidget(checkBox_showRightToolbox, 4, 0, 1, 1);


        gridLayout_8->addLayout(gridLayout_7, 4, 0, 1, 1);

        spacerItem1 = new QSpacerItem(400, 111, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_8->addItem(spacerItem1, 5, 0, 1, 1);

        stackedWidget->addWidget(page);
        page_8 = new QWidget();
        page_8->setObjectName(QString::fromUtf8("page_8"));
        gridLayout_12 = new QGridLayout(page_8);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        label_28 = new QLabel(page_8);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setStyleSheet(QString::fromUtf8("QLabel { font-weight: bold;  }"));

        gridLayout_12->addWidget(label_28, 0, 0, 1, 1);

        line_7 = new QFrame(page_8);
        line_7->setObjectName(QString::fromUtf8("line_7"));
        line_7->setFrameShape(QFrame::HLine);
        line_7->setFrameShadow(QFrame::Sunken);

        gridLayout_12->addWidget(line_7, 1, 0, 1, 1);

        tabWidget = new QTabWidget(page_8);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        gridLayout_13 = new QGridLayout(tab_3);
        gridLayout_13->setObjectName(QString::fromUtf8("gridLayout_13"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        pushButton_addGameTableStyle = new QPushButton(tab_3);
        pushButton_addGameTableStyle->setObjectName(QString::fromUtf8("pushButton_addGameTableStyle"));

        verticalLayout->addWidget(pushButton_addGameTableStyle);

        pushButton_removeGameTableStyle = new QPushButton(tab_3);
        pushButton_removeGameTableStyle->setObjectName(QString::fromUtf8("pushButton_removeGameTableStyle"));

        verticalLayout->addWidget(pushButton_removeGameTableStyle);

        verticalSpacer_3 = new QSpacerItem(20, 17, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);


        gridLayout_13->addLayout(verticalLayout, 0, 1, 1, 1);

        groupBox_13 = new QGroupBox(tab_3);
        groupBox_13->setObjectName(QString::fromUtf8("groupBox_13"));
        gridLayout_15 = new QGridLayout(groupBox_13);
        gridLayout_15->setObjectName(QString::fromUtf8("gridLayout_15"));
        label_gameTableStylePreview = new QLabel(groupBox_13);
        label_gameTableStylePreview->setObjectName(QString::fromUtf8("label_gameTableStylePreview"));
        label_gameTableStylePreview->setMinimumSize(QSize(160, 120));
        label_gameTableStylePreview->setMaximumSize(QSize(160, 120));

        gridLayout_15->addWidget(label_gameTableStylePreview, 0, 0, 1, 1);

        label_gameTableStyleInfo = new QLabel(groupBox_13);
        label_gameTableStyleInfo->setObjectName(QString::fromUtf8("label_gameTableStyleInfo"));
        label_gameTableStyleInfo->setTextFormat(Qt::RichText);
        label_gameTableStyleInfo->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        gridLayout_15->addWidget(label_gameTableStyleInfo, 0, 1, 1, 1);


        gridLayout_13->addWidget(groupBox_13, 1, 0, 1, 2);

        label_55 = new QLabel(tab_3);
        label_55->setObjectName(QString::fromUtf8("label_55"));
        label_55->setOpenExternalLinks(true);

        gridLayout_13->addWidget(label_55, 2, 0, 1, 2);

        treeWidget_gameTableStyles = new QTreeWidget(tab_3);
        treeWidget_gameTableStyles->setObjectName(QString::fromUtf8("treeWidget_gameTableStyles"));
        treeWidget_gameTableStyles->setIndentation(5);
        treeWidget_gameTableStyles->setRootIsDecorated(false);
        treeWidget_gameTableStyles->setItemsExpandable(false);
        treeWidget_gameTableStyles->setSortingEnabled(true);
        treeWidget_gameTableStyles->setAllColumnsShowFocus(true);
        treeWidget_gameTableStyles->setColumnCount(3);
        treeWidget_gameTableStyles->header()->setCascadingSectionResizes(false);
        treeWidget_gameTableStyles->header()->setProperty("showSortIndicator", QVariant(true));

        gridLayout_13->addWidget(treeWidget_gameTableStyles, 0, 0, 1, 1);

        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        gridLayout_14 = new QGridLayout(tab_4);
        gridLayout_14->setObjectName(QString::fromUtf8("gridLayout_14"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        pushButton_addCardDeckStyle = new QPushButton(tab_4);
        pushButton_addCardDeckStyle->setObjectName(QString::fromUtf8("pushButton_addCardDeckStyle"));

        verticalLayout_2->addWidget(pushButton_addCardDeckStyle);

        pushButton_removeCardDeckStyle = new QPushButton(tab_4);
        pushButton_removeCardDeckStyle->setObjectName(QString::fromUtf8("pushButton_removeCardDeckStyle"));

        verticalLayout_2->addWidget(pushButton_removeCardDeckStyle);

        verticalSpacer_333 = new QSpacerItem(20, 17, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_333);


        gridLayout_14->addLayout(verticalLayout_2, 0, 1, 1, 1);

        groupBox_14 = new QGroupBox(tab_4);
        groupBox_14->setObjectName(QString::fromUtf8("groupBox_14"));
        gridLayout_16 = new QGridLayout(groupBox_14);
        gridLayout_16->setObjectName(QString::fromUtf8("gridLayout_16"));
        label_cardDeckStylePreview = new QLabel(groupBox_14);
        label_cardDeckStylePreview->setObjectName(QString::fromUtf8("label_cardDeckStylePreview"));
        label_cardDeckStylePreview->setMinimumSize(QSize(160, 120));
        label_cardDeckStylePreview->setMaximumSize(QSize(160, 120));

        gridLayout_16->addWidget(label_cardDeckStylePreview, 0, 0, 1, 1);

        label_cardDeckStyleInfo = new QLabel(groupBox_14);
        label_cardDeckStyleInfo->setObjectName(QString::fromUtf8("label_cardDeckStyleInfo"));
        label_cardDeckStyleInfo->setTextFormat(Qt::RichText);
        label_cardDeckStyleInfo->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        gridLayout_16->addWidget(label_cardDeckStyleInfo, 0, 1, 1, 1);


        gridLayout_14->addWidget(groupBox_14, 1, 0, 1, 2);

        label_56 = new QLabel(tab_4);
        label_56->setObjectName(QString::fromUtf8("label_56"));
        label_56->setOpenExternalLinks(true);

        gridLayout_14->addWidget(label_56, 2, 0, 1, 2);

        treeWidget_cardDeckStyles = new QTreeWidget(tab_4);
        treeWidget_cardDeckStyles->setObjectName(QString::fromUtf8("treeWidget_cardDeckStyles"));
        treeWidget_cardDeckStyles->setIndentation(5);
        treeWidget_cardDeckStyles->setRootIsDecorated(false);
        treeWidget_cardDeckStyles->setItemsExpandable(false);
        treeWidget_cardDeckStyles->setSortingEnabled(true);
        treeWidget_cardDeckStyles->setAllColumnsShowFocus(true);
        treeWidget_cardDeckStyles->header()->setProperty("showSortIndicator", QVariant(true));

        gridLayout_14->addWidget(treeWidget_cardDeckStyles, 0, 0, 1, 1);

        tabWidget->addTab(tab_4, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout_17 = new QGridLayout(tab);
        gridLayout_17->setObjectName(QString::fromUtf8("gridLayout_17"));
        radioButton_flipsideTux = new QRadioButton(tab);
        radioButton_flipsideTux->setObjectName(QString::fromUtf8("radioButton_flipsideTux"));
        radioButton_flipsideTux->setChecked(true);

        gridLayout_17->addWidget(radioButton_flipsideTux, 0, 0, 1, 1);

        _3 = new QVBoxLayout();
        _3->setSpacing(0);
        _3->setContentsMargins(0, 0, 0, 0);
        _3->setObjectName(QString::fromUtf8("_3"));
        _10 = new QHBoxLayout();
        _10->setSpacing(2);
#ifndef Q_OS_MAC
        _10->setContentsMargins(0, 0, 0, 0);
#endif
        _10->setObjectName(QString::fromUtf8("_10"));
        radioButton_flipsideOwn = new QRadioButton(tab);
        radioButton_flipsideOwn->setObjectName(QString::fromUtf8("radioButton_flipsideOwn"));

        _10->addWidget(radioButton_flipsideOwn);

        lineEdit_OwnFlipsideFilename = new QLineEdit(tab);
        lineEdit_OwnFlipsideFilename->setObjectName(QString::fromUtf8("lineEdit_OwnFlipsideFilename"));
        lineEdit_OwnFlipsideFilename->setEnabled(false);

        _10->addWidget(lineEdit_OwnFlipsideFilename);

        pushButton_openFlipsidePicture = new QPushButton(tab);
        pushButton_openFlipsidePicture->setObjectName(QString::fromUtf8("pushButton_openFlipsidePicture"));
        pushButton_openFlipsidePicture->setEnabled(false);
        pushButton_openFlipsidePicture->setMinimumSize(QSize(27, 26));
        pushButton_openFlipsidePicture->setMaximumSize(QSize(27, 26));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/gfx/document-open-folder.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_openFlipsidePicture->setIcon(icon4);

        _10->addWidget(pushButton_openFlipsidePicture);


        _3->addLayout(_10);

        label_57 = new QLabel(tab);
        label_57->setObjectName(QString::fromUtf8("label_57"));
        label_57->setWordWrap(true);

        _3->addWidget(label_57);


        gridLayout_17->addLayout(_3, 1, 0, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 276, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_17->addItem(verticalSpacer_4, 2, 0, 1, 1);

        tabWidget->addTab(tab, QString());

        gridLayout_12->addWidget(tabWidget, 2, 0, 1, 1);

        stackedWidget->addWidget(page_8);
        page_6 = new QWidget();
        page_6->setObjectName(QString::fromUtf8("page_6"));
        gridLayout1 = new QGridLayout(page_6);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        label_26 = new QLabel(page_6);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setStyleSheet(QString::fromUtf8("QLabel { font-weight: bold;  }"));

        gridLayout1->addWidget(label_26, 0, 0, 1, 1);

        line_8 = new QFrame(page_6);
        line_8->setObjectName(QString::fromUtf8("line_8"));
        line_8->setFrameShape(QFrame::HLine);
        line_8->setFrameShadow(QFrame::Sunken);

        gridLayout1->addWidget(line_8, 1, 0, 1, 1);

        groupBox_playSoundEffects = new QGroupBox(page_6);
        groupBox_playSoundEffects->setObjectName(QString::fromUtf8("groupBox_playSoundEffects"));
        groupBox_playSoundEffects->setCheckable(true);
        groupBox_playSoundEffects->setChecked(true);
        gridLayout2 = new QGridLayout(groupBox_playSoundEffects);
        gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
        hboxLayout2 = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout2->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        hboxLayout2->setContentsMargins(0, 0, 0, 0);
#endif
        hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
        label_25 = new QLabel(groupBox_playSoundEffects);
        label_25->setObjectName(QString::fromUtf8("label_25"));

        hboxLayout2->addWidget(label_25);

        label_soundVolume = new QLabel(groupBox_playSoundEffects);
        label_soundVolume->setObjectName(QString::fromUtf8("label_soundVolume"));
        label_soundVolume->setMinimumSize(QSize(20, 0));

        hboxLayout2->addWidget(label_soundVolume);

        horizontalSlider_soundVolume = new QSlider(groupBox_playSoundEffects);
        horizontalSlider_soundVolume->setObjectName(QString::fromUtf8("horizontalSlider_soundVolume"));
        horizontalSlider_soundVolume->setMinimum(1);
        horizontalSlider_soundVolume->setMaximum(10);
        horizontalSlider_soundVolume->setValue(8);
        horizontalSlider_soundVolume->setOrientation(Qt::Horizontal);

        hboxLayout2->addWidget(horizontalSlider_soundVolume);


        gridLayout2->addLayout(hboxLayout2, 0, 0, 1, 1);

        groupBox_10 = new QGroupBox(groupBox_playSoundEffects);
        groupBox_10->setObjectName(QString::fromUtf8("groupBox_10"));
        gridLayout3 = new QGridLayout(groupBox_10);
        gridLayout3->setObjectName(QString::fromUtf8("gridLayout3"));
        gridLayout3->setContentsMargins(-1, 0, -1, -1);
        checkBox_playGameActions = new QCheckBox(groupBox_10);
        checkBox_playGameActions->setObjectName(QString::fromUtf8("checkBox_playGameActions"));

        gridLayout3->addWidget(checkBox_playGameActions, 0, 0, 1, 1);

        checkBox_playBlindRaiseSound = new QCheckBox(groupBox_10);
        checkBox_playBlindRaiseSound->setObjectName(QString::fromUtf8("checkBox_playBlindRaiseSound"));

        gridLayout3->addWidget(checkBox_playBlindRaiseSound, 1, 0, 1, 1);


        gridLayout2->addWidget(groupBox_10, 1, 0, 1, 1);


        gridLayout1->addWidget(groupBox_playSoundEffects, 2, 0, 1, 1);

        spacerItem2 = new QSpacerItem(400, 321, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout1->addItem(spacerItem2, 3, 0, 1, 1);

        stackedWidget->addWidget(page_6);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        vboxLayout = new QVBoxLayout(page_2);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        label_5 = new QLabel(page_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setStyleSheet(QString::fromUtf8("QLabel { font-weight: bold;  }"));

        vboxLayout->addWidget(label_5);

        line_3 = new QFrame(page_2);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        vboxLayout->addWidget(line_3);

        hboxLayout3 = new QHBoxLayout();
        hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
        label_4 = new QLabel(page_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        hboxLayout3->addWidget(label_4);

        spinBox_quantityPlayers = new QSpinBox(page_2);
        spinBox_quantityPlayers->setObjectName(QString::fromUtf8("spinBox_quantityPlayers"));
        spinBox_quantityPlayers->setMinimum(2);
        spinBox_quantityPlayers->setMaximum(10);
        spinBox_quantityPlayers->setValue(10);

        hboxLayout3->addWidget(spinBox_quantityPlayers);


        vboxLayout->addLayout(hboxLayout3);

        hboxLayout4 = new QHBoxLayout();
        hboxLayout4->setObjectName(QString::fromUtf8("hboxLayout4"));
        label_2 = new QLabel(page_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        hboxLayout4->addWidget(label_2);

        spinBox_startCash = new QSpinBox(page_2);
        spinBox_startCash->setObjectName(QString::fromUtf8("spinBox_startCash"));
        spinBox_startCash->setMinimum(1000);
        spinBox_startCash->setMaximum(1000000);
        spinBox_startCash->setSingleStep(50);

        hboxLayout4->addWidget(spinBox_startCash);


        vboxLayout->addLayout(hboxLayout4);

        hboxLayout5 = new QHBoxLayout();
        hboxLayout5->setObjectName(QString::fromUtf8("hboxLayout5"));
        label_3 = new QLabel(page_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        hboxLayout5->addWidget(label_3);

        spinBox_firstSmallBlind = new QSpinBox(page_2);
        spinBox_firstSmallBlind->setObjectName(QString::fromUtf8("spinBox_firstSmallBlind"));
        spinBox_firstSmallBlind->setMinimum(5);
        spinBox_firstSmallBlind->setMaximum(20000);

        hboxLayout5->addWidget(spinBox_firstSmallBlind);


        vboxLayout->addLayout(hboxLayout5);

        hboxLayout6 = new QHBoxLayout();
        hboxLayout6->setObjectName(QString::fromUtf8("hboxLayout6"));
        groupBox_6 = new QGroupBox(page_2);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        gridLayout4 = new QGridLayout(groupBox_6);
        gridLayout4->setObjectName(QString::fromUtf8("gridLayout4"));
        gridLayout4->setContentsMargins(9, 0, -1, 9);
        radioButton_raiseBlindsAtHands = new QRadioButton(groupBox_6);
        radioButton_raiseBlindsAtHands->setObjectName(QString::fromUtf8("radioButton_raiseBlindsAtHands"));
        radioButton_raiseBlindsAtHands->setChecked(true);

        gridLayout4->addWidget(radioButton_raiseBlindsAtHands, 0, 0, 1, 1);

        spinBox_raiseSmallBlindEveryHands = new QSpinBox(groupBox_6);
        spinBox_raiseSmallBlindEveryHands->setObjectName(QString::fromUtf8("spinBox_raiseSmallBlindEveryHands"));
        spinBox_raiseSmallBlindEveryHands->setMinimum(1);

        gridLayout4->addWidget(spinBox_raiseSmallBlindEveryHands, 0, 1, 1, 1);

        label_47 = new QLabel(groupBox_6);
        label_47->setObjectName(QString::fromUtf8("label_47"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_47->sizePolicy().hasHeightForWidth());
        label_47->setSizePolicy(sizePolicy);

        gridLayout4->addWidget(label_47, 0, 2, 1, 1);

        radioButton_raiseBlindsAtMinutes = new QRadioButton(groupBox_6);
        radioButton_raiseBlindsAtMinutes->setObjectName(QString::fromUtf8("radioButton_raiseBlindsAtMinutes"));

        gridLayout4->addWidget(radioButton_raiseBlindsAtMinutes, 1, 0, 1, 1);

        spinBox_raiseSmallBlindEveryMinutes = new QSpinBox(groupBox_6);
        spinBox_raiseSmallBlindEveryMinutes->setObjectName(QString::fromUtf8("spinBox_raiseSmallBlindEveryMinutes"));
        spinBox_raiseSmallBlindEveryMinutes->setMinimum(1);

        gridLayout4->addWidget(spinBox_raiseSmallBlindEveryMinutes, 1, 1, 1, 1);

        label_50 = new QLabel(groupBox_6);
        label_50->setObjectName(QString::fromUtf8("label_50"));
        sizePolicy.setHeightForWidth(label_50->sizePolicy().hasHeightForWidth());
        label_50->setSizePolicy(sizePolicy);

        gridLayout4->addWidget(label_50, 1, 2, 1, 1);

        spacerItem3 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout4->addItem(spacerItem3, 2, 1, 1, 1);


        hboxLayout6->addWidget(groupBox_6);

        groupBox_7 = new QGroupBox(page_2);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        sizePolicy.setHeightForWidth(groupBox_7->sizePolicy().hasHeightForWidth());
        groupBox_7->setSizePolicy(sizePolicy);
        gridLayout5 = new QGridLayout(groupBox_7);
        gridLayout5->setObjectName(QString::fromUtf8("gridLayout5"));
        gridLayout5->setContentsMargins(-1, 0, -1, -1);
        radioButton_alwaysDoubleBlinds = new QRadioButton(groupBox_7);
        radioButton_alwaysDoubleBlinds->setObjectName(QString::fromUtf8("radioButton_alwaysDoubleBlinds"));
        radioButton_alwaysDoubleBlinds->setChecked(true);

        gridLayout5->addWidget(radioButton_alwaysDoubleBlinds, 0, 0, 1, 1);

        radioButton_manualBlindsOrder = new QRadioButton(groupBox_7);
        radioButton_manualBlindsOrder->setObjectName(QString::fromUtf8("radioButton_manualBlindsOrder"));

        gridLayout5->addWidget(radioButton_manualBlindsOrder, 1, 0, 1, 1);

        pushButton_editManualBlindsOrder = new QPushButton(groupBox_7);
        pushButton_editManualBlindsOrder->setObjectName(QString::fromUtf8("pushButton_editManualBlindsOrder"));
        pushButton_editManualBlindsOrder->setEnabled(false);

        gridLayout5->addWidget(pushButton_editManualBlindsOrder, 2, 0, 1, 1);


        hboxLayout6->addWidget(groupBox_7);


        vboxLayout->addLayout(hboxLayout6);

        hboxLayout7 = new QHBoxLayout();
        hboxLayout7->setObjectName(QString::fromUtf8("hboxLayout7"));
        label = new QLabel(page_2);
        label->setObjectName(QString::fromUtf8("label"));

        hboxLayout7->addWidget(label);

        spinBox_gameSpeed = new QSpinBox(page_2);
        spinBox_gameSpeed->setObjectName(QString::fromUtf8("spinBox_gameSpeed"));
        spinBox_gameSpeed->setMinimum(1);
        spinBox_gameSpeed->setMaximum(11);
        spinBox_gameSpeed->setSingleStep(1);
        spinBox_gameSpeed->setValue(8);

        hboxLayout7->addWidget(spinBox_gameSpeed);


        vboxLayout->addLayout(hboxLayout7);

        checkBox_pauseBetweenHands = new QCheckBox(page_2);
        checkBox_pauseBetweenHands->setObjectName(QString::fromUtf8("checkBox_pauseBetweenHands"));

        vboxLayout->addWidget(checkBox_pauseBetweenHands);

        checkBox_showGameSettingsDialogOnNewGame = new QCheckBox(page_2);
        checkBox_showGameSettingsDialogOnNewGame->setObjectName(QString::fromUtf8("checkBox_showGameSettingsDialogOnNewGame"));

        vboxLayout->addWidget(checkBox_showGameSettingsDialogOnNewGame);

        spacerItem4 = new QSpacerItem(437, 285, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout->addItem(spacerItem4);

        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        gridLayout_10 = new QGridLayout(page_3);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        gridLayout_10->setVerticalSpacing(8);
        gridLayout_10->setContentsMargins(-1, -1, -1, 1);
        label_7 = new QLabel(page_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setStyleSheet(QString::fromUtf8("QLabel { font-weight: bold;  }"));

        gridLayout_10->addWidget(label_7, 0, 0, 1, 1);

        line_4 = new QFrame(page_3);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        gridLayout_10->addWidget(line_4, 1, 0, 1, 1);

        gridLayout_9 = new QGridLayout();
        gridLayout_9->setSpacing(0);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        horizontalSpacer_4 = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_9->addItem(horizontalSpacer_4, 0, 0, 1, 1);

        label_8 = new QLabel(page_3);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setAlignment(Qt::AlignCenter);

        gridLayout_9->addWidget(label_8, 0, 1, 1, 3);

        horizontalSpacer_5 = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_9->addItem(horizontalSpacer_5, 0, 4, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        pushButton_HumanPlayerAvatar = new MyHPAvatarButton(page_3);
        pushButton_HumanPlayerAvatar->setObjectName(QString::fromUtf8("pushButton_HumanPlayerAvatar"));
        pushButton_HumanPlayerAvatar->setMinimumSize(QSize(60, 60));
        pushButton_HumanPlayerAvatar->setMaximumSize(QSize(60, 60));
        pushButton_HumanPlayerAvatar->setIconSize(QSize(50, 50));

        horizontalLayout->addWidget(pushButton_HumanPlayerAvatar);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout_9->addLayout(horizontalLayout, 1, 0, 1, 5);

        horizontalSpacer_6 = new QSpacerItem(78, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_9->addItem(horizontalSpacer_6, 2, 0, 1, 2);

        lineEdit_HumanPlayerName = new QLineEdit(page_3);
        lineEdit_HumanPlayerName->setObjectName(QString::fromUtf8("lineEdit_HumanPlayerName"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEdit_HumanPlayerName->sizePolicy().hasHeightForWidth());
        lineEdit_HumanPlayerName->setSizePolicy(sizePolicy1);
        lineEdit_HumanPlayerName->setMinimumSize(QSize(100, 25));
        lineEdit_HumanPlayerName->setMaximumSize(QSize(100, 25));
        lineEdit_HumanPlayerName->setMaxLength(12);

        gridLayout_9->addWidget(lineEdit_HumanPlayerName, 2, 2, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(88, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_9->addItem(horizontalSpacer_7, 2, 3, 1, 2);


        gridLayout_10->addLayout(gridLayout_9, 2, 0, 1, 1);

        groupBox_3 = new QGroupBox(page_3);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout_11 = new QGridLayout(groupBox_3);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        gridLayout_11->setContentsMargins(-1, 0, -1, 4);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        gridLayout6 = new QGridLayout();
        gridLayout6->setSpacing(0);
#ifndef Q_OS_MAC
        gridLayout6->setContentsMargins(0, 0, 0, 0);
#endif
        gridLayout6->setObjectName(QString::fromUtf8("gridLayout6"));
        lineEdit_Opponent1Name = new QLineEdit(groupBox_3);
        lineEdit_Opponent1Name->setObjectName(QString::fromUtf8("lineEdit_Opponent1Name"));
        sizePolicy1.setHeightForWidth(lineEdit_Opponent1Name->sizePolicy().hasHeightForWidth());
        lineEdit_Opponent1Name->setSizePolicy(sizePolicy1);
        lineEdit_Opponent1Name->setMinimumSize(QSize(100, 25));
        lineEdit_Opponent1Name->setMaximumSize(QSize(100, 25));
        lineEdit_Opponent1Name->setMaxLength(12);

        gridLayout6->addWidget(lineEdit_Opponent1Name, 2, 0, 1, 1);

        label_9 = new QLabel(groupBox_3);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        sizePolicy1.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy1);
        label_9->setMinimumSize(QSize(100, 0));
        label_9->setMaximumSize(QSize(100, 16777215));
        label_9->setAlignment(Qt::AlignCenter);

        gridLayout6->addWidget(label_9, 0, 0, 1, 1);

        hboxLayout8 = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout8->setSpacing(6);
#endif
        hboxLayout8->setContentsMargins(0, 0, 0, 0);
        hboxLayout8->setObjectName(QString::fromUtf8("hboxLayout8"));
        spacerItem5 = new QSpacerItem(3, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        hboxLayout8->addItem(spacerItem5);

        pushButton_Opponent1Avatar = new MyAvatarButton(groupBox_3);
        pushButton_Opponent1Avatar->setObjectName(QString::fromUtf8("pushButton_Opponent1Avatar"));
        QSizePolicy sizePolicy2(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButton_Opponent1Avatar->sizePolicy().hasHeightForWidth());
        pushButton_Opponent1Avatar->setSizePolicy(sizePolicy2);
        pushButton_Opponent1Avatar->setMinimumSize(QSize(60, 60));
        pushButton_Opponent1Avatar->setMaximumSize(QSize(60, 60));
        pushButton_Opponent1Avatar->setIconSize(QSize(50, 50));

        hboxLayout8->addWidget(pushButton_Opponent1Avatar);

        spacerItem6 = new QSpacerItem(3, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        hboxLayout8->addItem(spacerItem6);


        gridLayout6->addLayout(hboxLayout8, 1, 0, 1, 1);


        horizontalLayout_3->addLayout(gridLayout6);

        gridLayout7 = new QGridLayout();
        gridLayout7->setSpacing(0);
        gridLayout7->setContentsMargins(0, 0, 0, 0);
        gridLayout7->setObjectName(QString::fromUtf8("gridLayout7"));
        lineEdit_Opponent2Name = new QLineEdit(groupBox_3);
        lineEdit_Opponent2Name->setObjectName(QString::fromUtf8("lineEdit_Opponent2Name"));
        sizePolicy1.setHeightForWidth(lineEdit_Opponent2Name->sizePolicy().hasHeightForWidth());
        lineEdit_Opponent2Name->setSizePolicy(sizePolicy1);
        lineEdit_Opponent2Name->setMinimumSize(QSize(100, 25));
        lineEdit_Opponent2Name->setMaximumSize(QSize(100, 25));
        lineEdit_Opponent2Name->setMaxLength(12);

        gridLayout7->addWidget(lineEdit_Opponent2Name, 2, 0, 1, 1);

        label_10 = new QLabel(groupBox_3);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        sizePolicy1.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy1);
        label_10->setMinimumSize(QSize(100, 0));
        label_10->setMaximumSize(QSize(100, 16777215));
        label_10->setAlignment(Qt::AlignCenter);

        gridLayout7->addWidget(label_10, 0, 0, 1, 1);

        hboxLayout9 = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout9->setSpacing(6);
#endif
        hboxLayout9->setContentsMargins(0, 0, 0, 0);
        hboxLayout9->setObjectName(QString::fromUtf8("hboxLayout9"));
        spacerItem7 = new QSpacerItem(3, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        hboxLayout9->addItem(spacerItem7);

        pushButton_Opponent2Avatar = new MyAvatarButton(groupBox_3);
        pushButton_Opponent2Avatar->setObjectName(QString::fromUtf8("pushButton_Opponent2Avatar"));
        sizePolicy2.setHeightForWidth(pushButton_Opponent2Avatar->sizePolicy().hasHeightForWidth());
        pushButton_Opponent2Avatar->setSizePolicy(sizePolicy2);
        pushButton_Opponent2Avatar->setMinimumSize(QSize(60, 60));
        pushButton_Opponent2Avatar->setMaximumSize(QSize(60, 60));
        pushButton_Opponent2Avatar->setIconSize(QSize(50, 50));

        hboxLayout9->addWidget(pushButton_Opponent2Avatar);

        spacerItem8 = new QSpacerItem(3, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        hboxLayout9->addItem(spacerItem8);


        gridLayout7->addLayout(hboxLayout9, 1, 0, 1, 1);


        horizontalLayout_3->addLayout(gridLayout7);

        gridLayout8 = new QGridLayout();
        gridLayout8->setSpacing(0);
        gridLayout8->setContentsMargins(0, 0, 0, 0);
        gridLayout8->setObjectName(QString::fromUtf8("gridLayout8"));
        label_11 = new QLabel(groupBox_3);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        sizePolicy1.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy1);
        label_11->setMinimumSize(QSize(100, 0));
        label_11->setMaximumSize(QSize(100, 16777215));
        label_11->setAlignment(Qt::AlignCenter);

        gridLayout8->addWidget(label_11, 0, 0, 1, 1);

        lineEdit_Opponent3Name = new QLineEdit(groupBox_3);
        lineEdit_Opponent3Name->setObjectName(QString::fromUtf8("lineEdit_Opponent3Name"));
        sizePolicy1.setHeightForWidth(lineEdit_Opponent3Name->sizePolicy().hasHeightForWidth());
        lineEdit_Opponent3Name->setSizePolicy(sizePolicy1);
        lineEdit_Opponent3Name->setMinimumSize(QSize(100, 25));
        lineEdit_Opponent3Name->setMaximumSize(QSize(100, 25));
        lineEdit_Opponent3Name->setMaxLength(12);

        gridLayout8->addWidget(lineEdit_Opponent3Name, 2, 0, 1, 1);

        hboxLayout10 = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout10->setSpacing(6);
#endif
        hboxLayout10->setContentsMargins(0, 0, 0, 0);
        hboxLayout10->setObjectName(QString::fromUtf8("hboxLayout10"));
        spacerItem9 = new QSpacerItem(3, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        hboxLayout10->addItem(spacerItem9);

        pushButton_Opponent3Avatar = new MyAvatarButton(groupBox_3);
        pushButton_Opponent3Avatar->setObjectName(QString::fromUtf8("pushButton_Opponent3Avatar"));
        sizePolicy2.setHeightForWidth(pushButton_Opponent3Avatar->sizePolicy().hasHeightForWidth());
        pushButton_Opponent3Avatar->setSizePolicy(sizePolicy2);
        pushButton_Opponent3Avatar->setMinimumSize(QSize(60, 60));
        pushButton_Opponent3Avatar->setMaximumSize(QSize(60, 60));
        pushButton_Opponent3Avatar->setIconSize(QSize(50, 50));

        hboxLayout10->addWidget(pushButton_Opponent3Avatar);

        spacerItem10 = new QSpacerItem(3, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        hboxLayout10->addItem(spacerItem10);


        gridLayout8->addLayout(hboxLayout10, 1, 0, 1, 1);


        horizontalLayout_3->addLayout(gridLayout8);

        gridLayout9 = new QGridLayout();
        gridLayout9->setSpacing(0);
        gridLayout9->setContentsMargins(0, 0, 0, 0);
        gridLayout9->setObjectName(QString::fromUtf8("gridLayout9"));
        lineEdit_Opponent4Name = new QLineEdit(groupBox_3);
        lineEdit_Opponent4Name->setObjectName(QString::fromUtf8("lineEdit_Opponent4Name"));
        sizePolicy1.setHeightForWidth(lineEdit_Opponent4Name->sizePolicy().hasHeightForWidth());
        lineEdit_Opponent4Name->setSizePolicy(sizePolicy1);
        lineEdit_Opponent4Name->setMinimumSize(QSize(100, 25));
        lineEdit_Opponent4Name->setMaximumSize(QSize(100, 25));
        lineEdit_Opponent4Name->setMaxLength(12);

        gridLayout9->addWidget(lineEdit_Opponent4Name, 2, 0, 1, 1);

        label_12 = new QLabel(groupBox_3);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        sizePolicy1.setHeightForWidth(label_12->sizePolicy().hasHeightForWidth());
        label_12->setSizePolicy(sizePolicy1);
        label_12->setMinimumSize(QSize(100, 0));
        label_12->setMaximumSize(QSize(100, 16777215));
        label_12->setAlignment(Qt::AlignCenter);

        gridLayout9->addWidget(label_12, 0, 0, 1, 1);

        hboxLayout11 = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout11->setSpacing(6);
#endif
        hboxLayout11->setContentsMargins(0, 0, 0, 0);
        hboxLayout11->setObjectName(QString::fromUtf8("hboxLayout11"));
        spacerItem11 = new QSpacerItem(3, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        hboxLayout11->addItem(spacerItem11);

        pushButton_Opponent4Avatar = new MyAvatarButton(groupBox_3);
        pushButton_Opponent4Avatar->setObjectName(QString::fromUtf8("pushButton_Opponent4Avatar"));
        sizePolicy2.setHeightForWidth(pushButton_Opponent4Avatar->sizePolicy().hasHeightForWidth());
        pushButton_Opponent4Avatar->setSizePolicy(sizePolicy2);
        pushButton_Opponent4Avatar->setMinimumSize(QSize(60, 60));
        pushButton_Opponent4Avatar->setMaximumSize(QSize(60, 60));
        pushButton_Opponent4Avatar->setIconSize(QSize(50, 50));

        hboxLayout11->addWidget(pushButton_Opponent4Avatar);

        spacerItem12 = new QSpacerItem(3, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        hboxLayout11->addItem(spacerItem12);


        gridLayout9->addLayout(hboxLayout11, 1, 0, 1, 1);


        horizontalLayout_3->addLayout(gridLayout9);

        gridLayout10 = new QGridLayout();
        gridLayout10->setSpacing(0);
        gridLayout10->setContentsMargins(0, 0, 0, 0);
        gridLayout10->setObjectName(QString::fromUtf8("gridLayout10"));
        label_20 = new QLabel(groupBox_3);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        sizePolicy1.setHeightForWidth(label_20->sizePolicy().hasHeightForWidth());
        label_20->setSizePolicy(sizePolicy1);
        label_20->setMinimumSize(QSize(100, 0));
        label_20->setMaximumSize(QSize(100, 16777215));
        label_20->setAlignment(Qt::AlignCenter);

        gridLayout10->addWidget(label_20, 0, 0, 1, 1);

        hboxLayout12 = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout12->setSpacing(6);
#endif
        hboxLayout12->setContentsMargins(0, 0, 0, 0);
        hboxLayout12->setObjectName(QString::fromUtf8("hboxLayout12"));
        spacerItem13 = new QSpacerItem(3, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        hboxLayout12->addItem(spacerItem13);

        pushButton_Opponent5Avatar = new MyAvatarButton(groupBox_3);
        pushButton_Opponent5Avatar->setObjectName(QString::fromUtf8("pushButton_Opponent5Avatar"));
        sizePolicy2.setHeightForWidth(pushButton_Opponent5Avatar->sizePolicy().hasHeightForWidth());
        pushButton_Opponent5Avatar->setSizePolicy(sizePolicy2);
        pushButton_Opponent5Avatar->setMinimumSize(QSize(60, 60));
        pushButton_Opponent5Avatar->setMaximumSize(QSize(60, 60));
        pushButton_Opponent5Avatar->setIconSize(QSize(50, 50));

        hboxLayout12->addWidget(pushButton_Opponent5Avatar);

        spacerItem14 = new QSpacerItem(3, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        hboxLayout12->addItem(spacerItem14);


        gridLayout10->addLayout(hboxLayout12, 1, 0, 1, 1);

        lineEdit_Opponent5Name = new QLineEdit(groupBox_3);
        lineEdit_Opponent5Name->setObjectName(QString::fromUtf8("lineEdit_Opponent5Name"));
        sizePolicy1.setHeightForWidth(lineEdit_Opponent5Name->sizePolicy().hasHeightForWidth());
        lineEdit_Opponent5Name->setSizePolicy(sizePolicy1);
        lineEdit_Opponent5Name->setMinimumSize(QSize(100, 25));
        lineEdit_Opponent5Name->setMaximumSize(QSize(100, 25));
        lineEdit_Opponent5Name->setMaxLength(12);

        gridLayout10->addWidget(lineEdit_Opponent5Name, 2, 0, 1, 1);


        horizontalLayout_3->addLayout(gridLayout10);


        gridLayout_11->addLayout(horizontalLayout_3, 0, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        gridLayout11 = new QGridLayout();
        gridLayout11->setSpacing(0);
#ifndef Q_OS_MAC
        gridLayout11->setContentsMargins(0, 0, 0, 0);
#endif
        gridLayout11->setObjectName(QString::fromUtf8("gridLayout11"));
        hboxLayout13 = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout13->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        hboxLayout13->setContentsMargins(0, 0, 0, 0);
#endif
        hboxLayout13->setObjectName(QString::fromUtf8("hboxLayout13"));
        spacerItem15 = new QSpacerItem(3, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        hboxLayout13->addItem(spacerItem15);

        pushButton_Opponent6Avatar = new MyAvatarButton(groupBox_3);
        pushButton_Opponent6Avatar->setObjectName(QString::fromUtf8("pushButton_Opponent6Avatar"));
        sizePolicy2.setHeightForWidth(pushButton_Opponent6Avatar->sizePolicy().hasHeightForWidth());
        pushButton_Opponent6Avatar->setSizePolicy(sizePolicy2);
        pushButton_Opponent6Avatar->setMinimumSize(QSize(60, 60));
        pushButton_Opponent6Avatar->setMaximumSize(QSize(60, 60));
        pushButton_Opponent6Avatar->setIconSize(QSize(50, 50));

        hboxLayout13->addWidget(pushButton_Opponent6Avatar);

        spacerItem16 = new QSpacerItem(3, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        hboxLayout13->addItem(spacerItem16);


        gridLayout11->addLayout(hboxLayout13, 1, 0, 1, 1);

        lineEdit_Opponent6Name = new QLineEdit(groupBox_3);
        lineEdit_Opponent6Name->setObjectName(QString::fromUtf8("lineEdit_Opponent6Name"));
        sizePolicy1.setHeightForWidth(lineEdit_Opponent6Name->sizePolicy().hasHeightForWidth());
        lineEdit_Opponent6Name->setSizePolicy(sizePolicy1);
        lineEdit_Opponent6Name->setMinimumSize(QSize(100, 25));
        lineEdit_Opponent6Name->setMaximumSize(QSize(100, 25));
        lineEdit_Opponent6Name->setMaxLength(12);

        gridLayout11->addWidget(lineEdit_Opponent6Name, 2, 0, 1, 1);

        label_21 = new QLabel(groupBox_3);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        sizePolicy1.setHeightForWidth(label_21->sizePolicy().hasHeightForWidth());
        label_21->setSizePolicy(sizePolicy1);
        label_21->setMinimumSize(QSize(100, 0));
        label_21->setMaximumSize(QSize(100, 16777215));
        label_21->setAlignment(Qt::AlignCenter);

        gridLayout11->addWidget(label_21, 0, 0, 1, 1);


        horizontalLayout_4->addLayout(gridLayout11);

        _4 = new QGridLayout();
        _4->setSpacing(0);
        _4->setContentsMargins(0, 0, 0, 0);
        _4->setObjectName(QString::fromUtf8("_4"));
        _5 = new QHBoxLayout();
#ifndef Q_OS_MAC
        _5->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        _5->setContentsMargins(0, 0, 0, 0);
#endif
        _5->setObjectName(QString::fromUtf8("_5"));
        spacerItem17 = new QSpacerItem(3, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        _5->addItem(spacerItem17);

        pushButton_Opponent7Avatar = new MyAvatarButton(groupBox_3);
        pushButton_Opponent7Avatar->setObjectName(QString::fromUtf8("pushButton_Opponent7Avatar"));
        sizePolicy2.setHeightForWidth(pushButton_Opponent7Avatar->sizePolicy().hasHeightForWidth());
        pushButton_Opponent7Avatar->setSizePolicy(sizePolicy2);
        pushButton_Opponent7Avatar->setMinimumSize(QSize(60, 60));
        pushButton_Opponent7Avatar->setMaximumSize(QSize(60, 60));
        pushButton_Opponent7Avatar->setIconSize(QSize(50, 50));

        _5->addWidget(pushButton_Opponent7Avatar);

        spacerItem18 = new QSpacerItem(3, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        _5->addItem(spacerItem18);


        _4->addLayout(_5, 1, 0, 1, 1);

        lineEdit_Opponent7Name = new QLineEdit(groupBox_3);
        lineEdit_Opponent7Name->setObjectName(QString::fromUtf8("lineEdit_Opponent7Name"));
        sizePolicy1.setHeightForWidth(lineEdit_Opponent7Name->sizePolicy().hasHeightForWidth());
        lineEdit_Opponent7Name->setSizePolicy(sizePolicy1);
        lineEdit_Opponent7Name->setMinimumSize(QSize(100, 25));
        lineEdit_Opponent7Name->setMaximumSize(QSize(100, 25));
        lineEdit_Opponent7Name->setMaxLength(12);

        _4->addWidget(lineEdit_Opponent7Name, 2, 0, 1, 1);

        label_33 = new QLabel(groupBox_3);
        label_33->setObjectName(QString::fromUtf8("label_33"));
        sizePolicy1.setHeightForWidth(label_33->sizePolicy().hasHeightForWidth());
        label_33->setSizePolicy(sizePolicy1);
        label_33->setMinimumSize(QSize(100, 0));
        label_33->setMaximumSize(QSize(100, 16777215));
        label_33->setAlignment(Qt::AlignCenter);

        _4->addWidget(label_33, 0, 0, 1, 1);


        horizontalLayout_4->addLayout(_4);

        _6 = new QGridLayout();
        _6->setSpacing(0);
        _6->setContentsMargins(0, 0, 0, 0);
        _6->setObjectName(QString::fromUtf8("_6"));
        _7 = new QHBoxLayout();
#ifndef Q_OS_MAC
        _7->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        _7->setContentsMargins(0, 0, 0, 0);
#endif
        _7->setObjectName(QString::fromUtf8("_7"));
        spacerItem19 = new QSpacerItem(3, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        _7->addItem(spacerItem19);

        pushButton_Opponent8Avatar = new MyAvatarButton(groupBox_3);
        pushButton_Opponent8Avatar->setObjectName(QString::fromUtf8("pushButton_Opponent8Avatar"));
        sizePolicy2.setHeightForWidth(pushButton_Opponent8Avatar->sizePolicy().hasHeightForWidth());
        pushButton_Opponent8Avatar->setSizePolicy(sizePolicy2);
        pushButton_Opponent8Avatar->setMinimumSize(QSize(60, 60));
        pushButton_Opponent8Avatar->setMaximumSize(QSize(60, 60));
        pushButton_Opponent8Avatar->setIconSize(QSize(50, 50));

        _7->addWidget(pushButton_Opponent8Avatar);

        spacerItem20 = new QSpacerItem(3, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        _7->addItem(spacerItem20);


        _6->addLayout(_7, 1, 0, 1, 1);

        lineEdit_Opponent8Name = new QLineEdit(groupBox_3);
        lineEdit_Opponent8Name->setObjectName(QString::fromUtf8("lineEdit_Opponent8Name"));
        sizePolicy1.setHeightForWidth(lineEdit_Opponent8Name->sizePolicy().hasHeightForWidth());
        lineEdit_Opponent8Name->setSizePolicy(sizePolicy1);
        lineEdit_Opponent8Name->setMinimumSize(QSize(100, 25));
        lineEdit_Opponent8Name->setMaximumSize(QSize(100, 25));
        lineEdit_Opponent8Name->setMaxLength(12);

        _6->addWidget(lineEdit_Opponent8Name, 2, 0, 1, 1);

        label_53 = new QLabel(groupBox_3);
        label_53->setObjectName(QString::fromUtf8("label_53"));
        sizePolicy1.setHeightForWidth(label_53->sizePolicy().hasHeightForWidth());
        label_53->setSizePolicy(sizePolicy1);
        label_53->setMinimumSize(QSize(100, 0));
        label_53->setMaximumSize(QSize(100, 16777215));
        label_53->setAlignment(Qt::AlignCenter);

        _6->addWidget(label_53, 0, 0, 1, 1);


        horizontalLayout_4->addLayout(_6);

        _8 = new QGridLayout();
        _8->setSpacing(0);
        _8->setContentsMargins(0, 0, 0, 0);
        _8->setObjectName(QString::fromUtf8("_8"));
        _9 = new QHBoxLayout();
#ifndef Q_OS_MAC
        _9->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        _9->setContentsMargins(0, 0, 0, 0);
#endif
        _9->setObjectName(QString::fromUtf8("_9"));
        spacerItem21 = new QSpacerItem(3, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        _9->addItem(spacerItem21);

        pushButton_Opponent9Avatar = new MyAvatarButton(groupBox_3);
        pushButton_Opponent9Avatar->setObjectName(QString::fromUtf8("pushButton_Opponent9Avatar"));
        sizePolicy2.setHeightForWidth(pushButton_Opponent9Avatar->sizePolicy().hasHeightForWidth());
        pushButton_Opponent9Avatar->setSizePolicy(sizePolicy2);
        pushButton_Opponent9Avatar->setMinimumSize(QSize(60, 60));
        pushButton_Opponent9Avatar->setMaximumSize(QSize(60, 60));
        pushButton_Opponent9Avatar->setIconSize(QSize(50, 50));

        _9->addWidget(pushButton_Opponent9Avatar);

        spacerItem22 = new QSpacerItem(3, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        _9->addItem(spacerItem22);


        _8->addLayout(_9, 1, 0, 1, 1);

        lineEdit_Opponent9Name = new QLineEdit(groupBox_3);
        lineEdit_Opponent9Name->setObjectName(QString::fromUtf8("lineEdit_Opponent9Name"));
        sizePolicy1.setHeightForWidth(lineEdit_Opponent9Name->sizePolicy().hasHeightForWidth());
        lineEdit_Opponent9Name->setSizePolicy(sizePolicy1);
        lineEdit_Opponent9Name->setMinimumSize(QSize(100, 25));
        lineEdit_Opponent9Name->setMaximumSize(QSize(100, 25));
        lineEdit_Opponent9Name->setMaxLength(12);

        _8->addWidget(lineEdit_Opponent9Name, 2, 0, 1, 1);

        label_54 = new QLabel(groupBox_3);
        label_54->setObjectName(QString::fromUtf8("label_54"));
        sizePolicy1.setHeightForWidth(label_54->sizePolicy().hasHeightForWidth());
        label_54->setSizePolicy(sizePolicy1);
        label_54->setMinimumSize(QSize(100, 0));
        label_54->setMaximumSize(QSize(100, 16777215));
        label_54->setAlignment(Qt::AlignCenter);

        _8->addWidget(label_54, 0, 0, 1, 1);


        horizontalLayout_4->addLayout(_8);


        gridLayout_11->addLayout(horizontalLayout_4, 1, 0, 1, 1);


        gridLayout_10->addWidget(groupBox_3, 3, 0, 1, 1);

        label_38 = new QLabel(page_3);
        label_38->setObjectName(QString::fromUtf8("label_38"));
        label_38->setWordWrap(true);

        gridLayout_10->addWidget(label_38, 4, 0, 1, 1);

        spacerItem23 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_10->addItem(spacerItem23, 5, 0, 1, 1);

        stackedWidget->addWidget(page_3);
        page_9 = new QWidget();
        page_9->setObjectName(QString::fromUtf8("page_9"));
        gridLayout_22 = new QGridLayout(page_9);
        gridLayout_22->setObjectName(QString::fromUtf8("gridLayout_22"));
        label_44 = new QLabel(page_9);
        label_44->setObjectName(QString::fromUtf8("label_44"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_44->setFont(font);

        gridLayout_22->addWidget(label_44, 0, 0, 1, 2);

        verticalSpacer_5 = new QSpacerItem(269, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_22->addItem(verticalSpacer_5, 3, 1, 1, 1);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_9);

        pushButton_resetSettings = new QPushButton(page_9);
        pushButton_resetSettings->setObjectName(QString::fromUtf8("pushButton_resetSettings"));
        pushButton_resetSettings->setMinimumSize(QSize(300, 60));
        pushButton_resetSettings->setFont(font);

        horizontalLayout_10->addWidget(pushButton_resetSettings);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_10);


        gridLayout_22->addLayout(horizontalLayout_10, 4, 0, 1, 2);

        verticalSpacer_6 = new QSpacerItem(269, 292, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_22->addItem(verticalSpacer_6, 6, 1, 1, 1);

        line_10 = new QFrame(page_9);
        line_10->setObjectName(QString::fromUtf8("line_10"));
        line_10->setFrameShape(QFrame::HLine);
        line_10->setFrameShadow(QFrame::Sunken);

        gridLayout_22->addWidget(line_10, 1, 0, 1, 2);

        label_resetNote = new QLabel(page_9);
        label_resetNote->setObjectName(QString::fromUtf8("label_resetNote"));
        QFont font1;
        font1.setItalic(true);
        label_resetNote->setFont(font1);

        gridLayout_22->addWidget(label_resetNote, 5, 0, 1, 2);

        stackedWidget->addWidget(page_9);

        hboxLayout->addWidget(stackedWidget);


        gridLayout->addLayout(hboxLayout, 0, 0, 1, 1);

        line = new QFrame(settingsDialog);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 1, 0, 1, 1);

        buttonBox = new QDialogButtonBox(settingsDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 2, 0, 1, 1);

#ifndef QT_NO_SHORTCUT
        label_14->setBuddy(comboBox_switchLanguage);
        label_4->setBuddy(spinBox_quantityPlayers);
        label_2->setBuddy(spinBox_startCash);
        label_3->setBuddy(spinBox_firstSmallBlind);
        label->setBuddy(spinBox_gameSpeed);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(listWidget, comboBox_switchLanguage);
        QWidget::setTabOrder(comboBox_switchLanguage, checkBox_showFadeOutCardsAnimation);
        QWidget::setTabOrder(checkBox_showFadeOutCardsAnimation, checkBox_showFlipCardsAnimation);
        QWidget::setTabOrder(checkBox_showFlipCardsAnimation, checkBox_showBlindButtons);
        QWidget::setTabOrder(checkBox_showBlindButtons, checkBox_antiPeekMode);
        QWidget::setTabOrder(checkBox_antiPeekMode, checkBox_dontTranslatePokerStrings);
        QWidget::setTabOrder(checkBox_dontTranslatePokerStrings, tabWidget);
        QWidget::setTabOrder(tabWidget, treeWidget_gameTableStyles);
        QWidget::setTabOrder(treeWidget_gameTableStyles, pushButton_addGameTableStyle);
        QWidget::setTabOrder(pushButton_addGameTableStyle, pushButton_removeGameTableStyle);
        QWidget::setTabOrder(pushButton_removeGameTableStyle, treeWidget_cardDeckStyles);
        QWidget::setTabOrder(treeWidget_cardDeckStyles, pushButton_addCardDeckStyle);
        QWidget::setTabOrder(pushButton_addCardDeckStyle, pushButton_removeCardDeckStyle);
        QWidget::setTabOrder(pushButton_removeCardDeckStyle, radioButton_flipsideTux);
        QWidget::setTabOrder(radioButton_flipsideTux, radioButton_flipsideOwn);
        QWidget::setTabOrder(radioButton_flipsideOwn, lineEdit_OwnFlipsideFilename);
        QWidget::setTabOrder(lineEdit_OwnFlipsideFilename, pushButton_openFlipsidePicture);
        QWidget::setTabOrder(pushButton_openFlipsidePicture, groupBox_playSoundEffects);
        QWidget::setTabOrder(groupBox_playSoundEffects, horizontalSlider_soundVolume);
        QWidget::setTabOrder(horizontalSlider_soundVolume, checkBox_playGameActions);
        QWidget::setTabOrder(checkBox_playGameActions, spinBox_quantityPlayers);
        QWidget::setTabOrder(spinBox_quantityPlayers, spinBox_startCash);
        QWidget::setTabOrder(spinBox_startCash, spinBox_firstSmallBlind);
        QWidget::setTabOrder(spinBox_firstSmallBlind, radioButton_raiseBlindsAtHands);
        QWidget::setTabOrder(radioButton_raiseBlindsAtHands, spinBox_raiseSmallBlindEveryHands);
        QWidget::setTabOrder(spinBox_raiseSmallBlindEveryHands, radioButton_raiseBlindsAtMinutes);
        QWidget::setTabOrder(radioButton_raiseBlindsAtMinutes, spinBox_raiseSmallBlindEveryMinutes);
        QWidget::setTabOrder(spinBox_raiseSmallBlindEveryMinutes, radioButton_alwaysDoubleBlinds);
        QWidget::setTabOrder(radioButton_alwaysDoubleBlinds, radioButton_manualBlindsOrder);
        QWidget::setTabOrder(radioButton_manualBlindsOrder, pushButton_editManualBlindsOrder);
        QWidget::setTabOrder(pushButton_editManualBlindsOrder, spinBox_gameSpeed);
        QWidget::setTabOrder(spinBox_gameSpeed, checkBox_pauseBetweenHands);
        QWidget::setTabOrder(checkBox_pauseBetweenHands, checkBox_showGameSettingsDialogOnNewGame);
        QWidget::setTabOrder(checkBox_showGameSettingsDialogOnNewGame, pushButton_HumanPlayerAvatar);
        QWidget::setTabOrder(pushButton_HumanPlayerAvatar, lineEdit_HumanPlayerName);
        QWidget::setTabOrder(lineEdit_HumanPlayerName, pushButton_Opponent1Avatar);
        QWidget::setTabOrder(pushButton_Opponent1Avatar, lineEdit_Opponent1Name);
        QWidget::setTabOrder(lineEdit_Opponent1Name, pushButton_Opponent2Avatar);
        QWidget::setTabOrder(pushButton_Opponent2Avatar, lineEdit_Opponent2Name);
        QWidget::setTabOrder(lineEdit_Opponent2Name, pushButton_Opponent3Avatar);
        QWidget::setTabOrder(pushButton_Opponent3Avatar, lineEdit_Opponent3Name);
        QWidget::setTabOrder(lineEdit_Opponent3Name, pushButton_Opponent4Avatar);
        QWidget::setTabOrder(pushButton_Opponent4Avatar, lineEdit_Opponent4Name);
        QWidget::setTabOrder(lineEdit_Opponent4Name, pushButton_Opponent5Avatar);
        QWidget::setTabOrder(pushButton_Opponent5Avatar, lineEdit_Opponent5Name);
        QWidget::setTabOrder(lineEdit_Opponent5Name, pushButton_Opponent6Avatar);
        QWidget::setTabOrder(pushButton_Opponent6Avatar, lineEdit_Opponent6Name);
        QWidget::setTabOrder(lineEdit_Opponent6Name, pushButton_Opponent7Avatar);
        QWidget::setTabOrder(pushButton_Opponent7Avatar, lineEdit_Opponent7Name);
        QWidget::setTabOrder(lineEdit_Opponent7Name, pushButton_Opponent8Avatar);
        QWidget::setTabOrder(pushButton_Opponent8Avatar, lineEdit_Opponent8Name);
        QWidget::setTabOrder(lineEdit_Opponent8Name, pushButton_Opponent9Avatar);
        QWidget::setTabOrder(pushButton_Opponent9Avatar, lineEdit_Opponent9Name);
        QWidget::setTabOrder(lineEdit_Opponent9Name, buttonBox);

        retranslateUi(settingsDialog);
        QObject::connect(listWidget, SIGNAL(currentRowChanged(int)), stackedWidget, SLOT(setCurrentIndex(int)));
        QObject::connect(buttonBox, SIGNAL(rejected()), settingsDialog, SLOT(reject()));
        QObject::connect(horizontalSlider_soundVolume, SIGNAL(valueChanged(int)), label_soundVolume, SLOT(setNum(int)));
        QObject::connect(radioButton_manualBlindsOrder, SIGNAL(toggled(bool)), pushButton_editManualBlindsOrder, SLOT(setEnabled(bool)));
        QObject::connect(radioButton_flipsideOwn, SIGNAL(toggled(bool)), lineEdit_OwnFlipsideFilename, SLOT(setEnabled(bool)));
        QObject::connect(radioButton_flipsideOwn, SIGNAL(toggled(bool)), pushButton_openFlipsidePicture, SLOT(setEnabled(bool)));

        stackedWidget->setCurrentIndex(0);
        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(settingsDialog);
    } // setupUi

    void retranslateUi(QDialog *settingsDialog)
    {
        settingsDialog->setWindowTitle(QApplication::translate("settingsDialog", "Settings", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = listWidget->isSortingEnabled();
        listWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("settingsDialog", "Interface", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem1 = listWidget->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("settingsDialog", "Style", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem2 = listWidget->item(2);
        ___qlistwidgetitem2->setText(QApplication::translate("settingsDialog", "Sound", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem3 = listWidget->item(3);
        ___qlistwidgetitem3->setText(QApplication::translate("settingsDialog", "Game", 0, QApplication::UnicodeUTF8));
        listWidget->setSortingEnabled(__sortingEnabled);

        label_19->setText(QApplication::translate("settingsDialog", "Interface", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("settingsDialog", "Language:", 0, QApplication::UnicodeUTF8));
        checkBox_showBlindButtons->setText(QApplication::translate("settingsDialog", "Show buttons for small blind and big blind", 0, QApplication::UnicodeUTF8));
        checkBox_showFadeOutCardsAnimation->setText(QApplication::translate("settingsDialog", "Show fade-out animation for non-winning cards", 0, QApplication::UnicodeUTF8));
        checkBox_dontTranslatePokerStrings->setText(QApplication::translate("settingsDialog", "Don't translate poker strings like check, call, raise from game table style", 0, QApplication::UnicodeUTF8));
        checkBox_antiPeekMode->setText(QApplication::translate("settingsDialog", "Show own cards only on mouse click", 0, QApplication::UnicodeUTF8));
        checkBox_showFlipCardsAnimation->setText(QApplication::translate("settingsDialog", "Show flip-card animation", 0, QApplication::UnicodeUTF8));
        checkBox_showPlayersStatistics->setText(QApplication::translate("settingsDialog", "Show players statistics", 0, QApplication::UnicodeUTF8));
        checkBox_showRightToolbox->setText(QApplication::translate("settingsDialog", "Show right toolbox", 0, QApplication::UnicodeUTF8));
        label_28->setText(QApplication::translate("settingsDialog", "Style", 0, QApplication::UnicodeUTF8));
        pushButton_addGameTableStyle->setText(QApplication::translate("settingsDialog", "Add ...", 0, QApplication::UnicodeUTF8));
        pushButton_removeGameTableStyle->setText(QApplication::translate("settingsDialog", "Remove", 0, QApplication::UnicodeUTF8));
        groupBox_13->setTitle(QApplication::translate("settingsDialog", "Preview - Information:", 0, QApplication::UnicodeUTF8));
        label_gameTableStylePreview->setText(QString());
        label_gameTableStyleInfo->setText(QString());
        label_55->setText(QApplication::translate("settingsDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><a href=\"http://gtstyles.pokerth.net/\"><span style=\" text-decoration: underline; color:#0000ff;\">Get new PokerTH game table styles ...</span></a></p></body></html>", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget_gameTableStyles->headerItem();
        ___qtreewidgetitem->setText(2, QApplication::translate("settingsDialog", "State", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(1, QApplication::translate("settingsDialog", "Maintainer", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(0, QApplication::translate("settingsDialog", "Description", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("settingsDialog", "Game Table", 0, QApplication::UnicodeUTF8));
        pushButton_addCardDeckStyle->setText(QApplication::translate("settingsDialog", "Add ...", 0, QApplication::UnicodeUTF8));
        pushButton_removeCardDeckStyle->setText(QApplication::translate("settingsDialog", "Remove", 0, QApplication::UnicodeUTF8));
        groupBox_14->setTitle(QApplication::translate("settingsDialog", "Preview - Information:", 0, QApplication::UnicodeUTF8));
        label_cardDeckStylePreview->setText(QString());
        label_cardDeckStyleInfo->setText(QString());
        label_56->setText(QApplication::translate("settingsDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><a href=\"http://cdstyles.pokerth.net/\"><span style=\" text-decoration: underline; color:#0000ff;\">Get new PokerTH card deck styles ...</span></a></p></body></html>", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem1 = treeWidget_cardDeckStyles->headerItem();
        ___qtreewidgetitem1->setText(1, QApplication::translate("settingsDialog", "Maintainer", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem1->setText(0, QApplication::translate("settingsDialog", "Description", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("settingsDialog", "Card Deck", 0, QApplication::UnicodeUTF8));
        radioButton_flipsideTux->setText(QApplication::translate("settingsDialog", "Use card back from card style", 0, QApplication::UnicodeUTF8));
        radioButton_flipsideOwn->setText(QApplication::translate("settingsDialog", "Use custom card back picture:", 0, QApplication::UnicodeUTF8));
        label_57->setText(QApplication::translate("settingsDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Nimbus Sans L'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<table style=\"-qt-table-type: root; margin-top:4px; margin-bottom:4px; margin-left:4px; margin-right:4px;\">\n"
"<tr>\n"
"<td style=\"border: none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-style:italic;\">Note: Best quality with image ratio like </span><span style=\" font-weight:600; font-style:italic;\">width=48, height=76.</span></p></td></tr></table></body></html>", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("settingsDialog", "Card Back", 0, QApplication::UnicodeUTF8));
        label_26->setText(QApplication::translate("settingsDialog", "Sound", 0, QApplication::UnicodeUTF8));
        groupBox_playSoundEffects->setTitle(QApplication::translate("settingsDialog", "Play sound effects", 0, QApplication::UnicodeUTF8));
        label_25->setText(QApplication::translate("settingsDialog", "Sound Volume:", 0, QApplication::UnicodeUTF8));
        label_soundVolume->setText(QApplication::translate("settingsDialog", "10", 0, QApplication::UnicodeUTF8));
        groupBox_10->setTitle(QApplication::translate("settingsDialog", "Sound Categories ", 0, QApplication::UnicodeUTF8));
        checkBox_playGameActions->setText(QApplication::translate("settingsDialog", "Play game actions sounds like \"check\", \"call\", \"raise\"", 0, QApplication::UnicodeUTF8));
        checkBox_playBlindRaiseSound->setText(QApplication::translate("settingsDialog", "Play blind raise notification", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("settingsDialog", "Game Settings", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("settingsDialog", "Number of players:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("settingsDialog", "Start Cash:", 0, QApplication::UnicodeUTF8));
        spinBox_startCash->setPrefix(QApplication::translate("settingsDialog", "$", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("settingsDialog", "First small blind:", 0, QApplication::UnicodeUTF8));
        spinBox_firstSmallBlind->setPrefix(QApplication::translate("settingsDialog", "$", 0, QApplication::UnicodeUTF8));
        groupBox_6->setTitle(QApplication::translate("settingsDialog", "Raise blinds:", 0, QApplication::UnicodeUTF8));
        radioButton_raiseBlindsAtHands->setText(QApplication::translate("settingsDialog", "Every:", 0, QApplication::UnicodeUTF8));
        label_47->setText(QApplication::translate("settingsDialog", "hands", 0, QApplication::UnicodeUTF8));
        radioButton_raiseBlindsAtMinutes->setText(QApplication::translate("settingsDialog", "Every:", 0, QApplication::UnicodeUTF8));
        label_50->setText(QApplication::translate("settingsDialog", "minutes", 0, QApplication::UnicodeUTF8));
        groupBox_7->setTitle(QApplication::translate("settingsDialog", "Raise mode:", 0, QApplication::UnicodeUTF8));
        radioButton_alwaysDoubleBlinds->setText(QApplication::translate("settingsDialog", "Always double blinds", 0, QApplication::UnicodeUTF8));
        radioButton_manualBlindsOrder->setText(QApplication::translate("settingsDialog", "Manual blinds order:", 0, QApplication::UnicodeUTF8));
        pushButton_editManualBlindsOrder->setText(QApplication::translate("settingsDialog", "Edit ...", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("settingsDialog", "Game Speed:", 0, QApplication::UnicodeUTF8));
        checkBox_pauseBetweenHands->setText(QApplication::translate("settingsDialog", "Pause between hands (press \"start\" button to go on)", 0, QApplication::UnicodeUTF8));
        checkBox_showGameSettingsDialogOnNewGame->setText(QApplication::translate("settingsDialog", "Show game settings dialog on every new game", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("settingsDialog", "Player Nicks/Avatars", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("settingsDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Human Player:<br /><span style=\" font-style:italic;\">(This nick will also be used for the online game login)</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        pushButton_HumanPlayerAvatar->setText(QString());
        groupBox_3->setTitle(QApplication::translate("settingsDialog", "Computer Engine", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("settingsDialog", "Opponent 1:", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("settingsDialog", "Opponent 2:", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("settingsDialog", "Opponent 3:", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("settingsDialog", "Opponent 4:", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("settingsDialog", "Opponent 5:", 0, QApplication::UnicodeUTF8));
        label_21->setText(QApplication::translate("settingsDialog", "Opponent 6:", 0, QApplication::UnicodeUTF8));
        label_33->setText(QApplication::translate("settingsDialog", "Opponent 7:", 0, QApplication::UnicodeUTF8));
        label_53->setText(QApplication::translate("settingsDialog", "Opponent 8:", 0, QApplication::UnicodeUTF8));
        label_54->setText(QApplication::translate("settingsDialog", "Opponent 9:", 0, QApplication::UnicodeUTF8));
        label_38->setText(QApplication::translate("settingsDialog", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\"font-weight:400; font-style:normal; text-decoration:none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-style:italic;\">Note: Best avatar quality with image ratio like </span><span style=\" font-weight:600; font-style:italic;\">width=50, height=50.</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_44->setText(QApplication::translate("settingsDialog", "Factory Settings", 0, QApplication::UnicodeUTF8));
        pushButton_resetSettings->setText(QApplication::translate("settingsDialog", "Reset all settings to default ...", 0, QApplication::UnicodeUTF8));
        label_resetNote->setText(QApplication::translate("settingsDialog", "Note: You can not reset all settings to default during a running game!", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class settingsDialog: public Ui_settingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSDIALOG_H
