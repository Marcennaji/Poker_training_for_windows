/********************************************************************************
** Form generated from reading UI file 'selectavatardialog.ui'
**
** Created: Sun 9. Dec 12:11:07 2012
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTAVATARDIALOG_H
#define UI_SELECTAVATARDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_selectAvatarDialog
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout1;
    QComboBox *comboBox_avatarViewCategorie;
    QListWidget *listWidget;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout2;
    QPushButton *pushButton_OpenAvatarFile;
    QLineEdit *lineEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *selectAvatarDialog)
    {
        if (selectAvatarDialog->objectName().isEmpty())
            selectAvatarDialog->setObjectName(QString::fromUtf8("selectAvatarDialog"));
        selectAvatarDialog->resize(548, 500);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(selectAvatarDialog->sizePolicy().hasHeightForWidth());
        selectAvatarDialog->setSizePolicy(sizePolicy);
        selectAvatarDialog->setMinimumSize(QSize(548, 500));
        selectAvatarDialog->setMaximumSize(QSize(548, 500));
        gridLayout = new QGridLayout(selectAvatarDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox = new QGroupBox(selectAvatarDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setCheckable(true);
        groupBox->setChecked(true);
        gridLayout1 = new QGridLayout(groupBox);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        comboBox_avatarViewCategorie = new QComboBox(groupBox);
        comboBox_avatarViewCategorie->setObjectName(QString::fromUtf8("comboBox_avatarViewCategorie"));

        gridLayout1->addWidget(comboBox_avatarViewCategorie, 0, 0, 1, 1);

        listWidget = new QListWidget(groupBox);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        gridLayout1->addWidget(listWidget, 1, 0, 1, 1);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(selectAvatarDialog);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setCheckable(true);
        groupBox_2->setChecked(false);
        gridLayout2 = new QGridLayout(groupBox_2);
        gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
        gridLayout2->setHorizontalSpacing(2);
        gridLayout2->setVerticalSpacing(2);
        gridLayout2->setContentsMargins(9, 9, 9, 9);
        pushButton_OpenAvatarFile = new QPushButton(groupBox_2);
        pushButton_OpenAvatarFile->setObjectName(QString::fromUtf8("pushButton_OpenAvatarFile"));
        pushButton_OpenAvatarFile->setMinimumSize(QSize(27, 26));
        pushButton_OpenAvatarFile->setMaximumSize(QSize(27, 26));

        gridLayout2->addWidget(pushButton_OpenAvatarFile, 0, 1, 1, 1);

        lineEdit = new QLineEdit(groupBox_2);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout2->addWidget(lineEdit, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox_2, 1, 0, 1, 1);

        buttonBox = new QDialogButtonBox(selectAvatarDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::NoButton|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 2, 0, 1, 1);

        QWidget::setTabOrder(groupBox, comboBox_avatarViewCategorie);
        QWidget::setTabOrder(comboBox_avatarViewCategorie, listWidget);
        QWidget::setTabOrder(listWidget, groupBox_2);
        QWidget::setTabOrder(groupBox_2, lineEdit);
        QWidget::setTabOrder(lineEdit, pushButton_OpenAvatarFile);
        QWidget::setTabOrder(pushButton_OpenAvatarFile, buttonBox);

        retranslateUi(selectAvatarDialog);
        QObject::connect(buttonBox, SIGNAL(rejected()), selectAvatarDialog, SLOT(reject()));
        QObject::connect(groupBox, SIGNAL(toggled(bool)), listWidget, SLOT(setEnabled(bool)));
        QObject::connect(groupBox_2, SIGNAL(toggled(bool)), lineEdit, SLOT(setEnabled(bool)));
        QObject::connect(groupBox_2, SIGNAL(toggled(bool)), pushButton_OpenAvatarFile, SLOT(setEnabled(bool)));
        QObject::connect(groupBox, SIGNAL(toggled(bool)), comboBox_avatarViewCategorie, SLOT(setEnabled(bool)));

        QMetaObject::connectSlotsByName(selectAvatarDialog);
    } // setupUi

    void retranslateUi(QDialog *selectAvatarDialog)
    {
        selectAvatarDialog->setWindowTitle(QApplication::translate("selectAvatarDialog", "Please select an avatar", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("selectAvatarDialog", "Select an avatar", 0, QApplication::UnicodeUTF8));
        comboBox_avatarViewCategorie->clear();
        comboBox_avatarViewCategorie->insertItems(0, QStringList()
         << QApplication::translate("selectAvatarDialog", "People", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("selectAvatarDialog", "Miscellaneous", 0, QApplication::UnicodeUTF8)
        );
        groupBox_2->setTitle(QApplication::translate("selectAvatarDialog", "Load avatar from external file", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class selectAvatarDialog: public Ui_selectAvatarDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTAVATARDIALOG_H
