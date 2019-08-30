/********************************************************************************
** Form generated from reading UI file 'dialogconnecttohost.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGCONNECTTOHOST_H
#define UI_DIALOGCONNECTTOHOST_H

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

class Ui_DialogConnectToHost
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *lineEdit;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonConnect;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *DialogConnectToHost)
    {
        if (DialogConnectToHost->objectName().isEmpty())
            DialogConnectToHost->setObjectName(QString::fromUtf8("DialogConnectToHost"));
        DialogConnectToHost->resize(309, 124);
        verticalLayout = new QVBoxLayout(DialogConnectToHost);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(DialogConnectToHost);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        lineEdit = new QLineEdit(DialogConnectToHost);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout->addWidget(lineEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButtonConnect = new QPushButton(DialogConnectToHost);
        pushButtonConnect->setObjectName(QString::fromUtf8("pushButtonConnect"));

        horizontalLayout_2->addWidget(pushButtonConnect);

        pushButtonCancel = new QPushButton(DialogConnectToHost);
        pushButtonCancel->setObjectName(QString::fromUtf8("pushButtonCancel"));

        horizontalLayout_2->addWidget(pushButtonCancel);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(DialogConnectToHost);

        QMetaObject::connectSlotsByName(DialogConnectToHost);
    } // setupUi

    void retranslateUi(QDialog *DialogConnectToHost)
    {
        DialogConnectToHost->setWindowTitle(QApplication::translate("DialogConnectToHost", "\350\277\236\346\216\245\344\270\273\346\234\272", nullptr));
        label->setText(QApplication::translate("DialogConnectToHost", "Host IP:", nullptr));
        pushButtonConnect->setText(QApplication::translate("DialogConnectToHost", "\350\277\236\346\216\245", nullptr));
        pushButtonCancel->setText(QApplication::translate("DialogConnectToHost", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogConnectToHost: public Ui_DialogConnectToHost {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGCONNECTTOHOST_H
