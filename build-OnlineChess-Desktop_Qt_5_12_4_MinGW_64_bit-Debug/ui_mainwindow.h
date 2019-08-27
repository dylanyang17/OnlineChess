/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionLoadInit;
    QAction *actionLoadFromFile;
    QAction *actionSaveChess;
    QAction *actionPVP;
    QAction *actionOnline;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(865, 647);
        actionLoadInit = new QAction(MainWindow);
        actionLoadInit->setObjectName(QString::fromUtf8("actionLoadInit"));
        actionLoadFromFile = new QAction(MainWindow);
        actionLoadFromFile->setObjectName(QString::fromUtf8("actionLoadFromFile"));
        actionSaveChess = new QAction(MainWindow);
        actionSaveChess->setObjectName(QString::fromUtf8("actionSaveChess"));
        actionPVP = new QAction(MainWindow);
        actionPVP->setObjectName(QString::fromUtf8("actionPVP"));
        actionOnline = new QAction(MainWindow);
        actionOnline->setObjectName(QString::fromUtf8("actionOnline"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 865, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menu);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(menu_2->menuAction());
        menu->addAction(actionSaveChess);
        menu->addSeparator();
        menu->addAction(actionPVP);
        menu->addAction(actionOnline);
        menu_2->addAction(actionLoadInit);
        menu_2->addAction(actionLoadFromFile);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionLoadInit->setText(QApplication::translate("MainWindow", "\345\210\235\345\247\213\345\261\200\351\235\242", nullptr));
        actionLoadFromFile->setText(QApplication::translate("MainWindow", "\344\273\216\346\226\207\344\273\266\350\275\275\345\205\245..", nullptr));
        actionSaveChess->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230\345\261\200\351\235\242", nullptr));
        actionPVP->setText(QApplication::translate("MainWindow", "\345\217\214\344\272\272\345\257\271\345\274\210", nullptr));
        actionOnline->setText(QApplication::translate("MainWindow", "\350\201\224\346\234\272\345\257\271\345\274\210", nullptr));
        menu->setTitle(QApplication::translate("MainWindow", "\346\270\270\346\210\217", nullptr));
        menu_2->setTitle(QApplication::translate("MainWindow", "\350\275\275\345\205\245\345\261\200\351\235\242", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
