/********************************************************************************
** Form generated from reading UI file 'dialogcreatehost.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGCREATEHOST_H
#define UI_DIALOGCREATEHOST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogCreateHost
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QLineEdit *lineEdit;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButtonStart;
    QPushButton *pushButtonClose;

    void setupUi(QDialog *DialogCreateHost)
    {
        if (DialogCreateHost->objectName().isEmpty())
            DialogCreateHost->setObjectName(QString::fromUtf8("DialogCreateHost"));
        DialogCreateHost->resize(295, 106);
        verticalLayout = new QVBoxLayout(DialogCreateHost);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(DialogCreateHost);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        lineEdit = new QLineEdit(DialogCreateHost);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout->addWidget(lineEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        pushButtonStart = new QPushButton(DialogCreateHost);
        pushButtonStart->setObjectName(QString::fromUtf8("pushButtonStart"));

        horizontalLayout_2->addWidget(pushButtonStart);

        pushButtonClose = new QPushButton(DialogCreateHost);
        pushButtonClose->setObjectName(QString::fromUtf8("pushButtonClose"));

        horizontalLayout_2->addWidget(pushButtonClose);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(DialogCreateHost);

        QMetaObject::connectSlotsByName(DialogCreateHost);
    } // setupUi

    void retranslateUi(QDialog *DialogCreateHost)
    {
        DialogCreateHost->setWindowTitle(QApplication::translate("DialogCreateHost", "Dialog", nullptr));
        label->setText(QApplication::translate("DialogCreateHost", "Host IP:", nullptr));
        pushButtonStart->setText(QApplication::translate("DialogCreateHost", "\345\210\233\345\273\272\344\270\273\346\234\272", nullptr));
        pushButtonClose->setText(QApplication::translate("DialogCreateHost", "\345\205\263\351\227\255", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogCreateHost: public Ui_DialogCreateHost {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGCREATEHOST_H
