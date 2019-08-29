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
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
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
    QAction *actionPVP;
    QAction *actionLoadInit;
    QAction *actionLoadFromFile;
    QAction *actionSaveChess;
    QAction *actionGiveIn;
    QAction *actionCreateHost;
    QAction *actionConnectHost;
    QAction *actionDebug;
    QAction *actionPauseTimer;
    QWidget *centralWidget;
    QLCDNumber *lcdNumber;
    QLabel *labelNowColor;
    QLabel *labelMyColor;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_5;
    QMenu *menu_3;
    QMenu *menu_4;
    QMenu *menu_6;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(865, 647);
        actionPVP = new QAction(MainWindow);
        actionPVP->setObjectName(QString::fromUtf8("actionPVP"));
        actionLoadInit = new QAction(MainWindow);
        actionLoadInit->setObjectName(QString::fromUtf8("actionLoadInit"));
        actionLoadFromFile = new QAction(MainWindow);
        actionLoadFromFile->setObjectName(QString::fromUtf8("actionLoadFromFile"));
        actionSaveChess = new QAction(MainWindow);
        actionSaveChess->setObjectName(QString::fromUtf8("actionSaveChess"));
        actionGiveIn = new QAction(MainWindow);
        actionGiveIn->setObjectName(QString::fromUtf8("actionGiveIn"));
        actionCreateHost = new QAction(MainWindow);
        actionCreateHost->setObjectName(QString::fromUtf8("actionCreateHost"));
        actionConnectHost = new QAction(MainWindow);
        actionConnectHost->setObjectName(QString::fromUtf8("actionConnectHost"));
        actionDebug = new QAction(MainWindow);
        actionDebug->setObjectName(QString::fromUtf8("actionDebug"));
        actionDebug->setCheckable(true);
        actionDebug->setChecked(false);
        actionPauseTimer = new QAction(MainWindow);
        actionPauseTimer->setObjectName(QString::fromUtf8("actionPauseTimer"));
        actionPauseTimer->setCheckable(true);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        lcdNumber = new QLCDNumber(centralWidget);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        lcdNumber->setGeometry(QRect(200, 10, 101, 41));
        labelNowColor = new QLabel(centralWidget);
        labelNowColor->setObjectName(QString::fromUtf8("labelNowColor"));
        labelNowColor->setGeometry(QRect(359, 28, 181, 16));
        labelMyColor = new QLabel(centralWidget);
        labelMyColor->setObjectName(QString::fromUtf8("labelMyColor"));
        labelMyColor->setGeometry(QRect(70, 30, 101, 16));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 865, 26));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_5 = new QMenu(menu);
        menu_5->setObjectName(QString::fromUtf8("menu_5"));
        menu_3 = new QMenu(menuBar);
        menu_3->setObjectName(QString::fromUtf8("menu_3"));
        menu_4 = new QMenu(menu_3);
        menu_4->setObjectName(QString::fromUtf8("menu_4"));
        menu_6 = new QMenu(menuBar);
        menu_6->setObjectName(QString::fromUtf8("menu_6"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_3->menuAction());
        menuBar->addAction(menu_6->menuAction());
        menu->addAction(actionPVP);
        menu->addAction(menu_5->menuAction());
        menu->addSeparator();
        menu->addAction(actionGiveIn);
        menu_5->addAction(actionCreateHost);
        menu_5->addAction(actionConnectHost);
        menu_3->addAction(menu_4->menuAction());
        menu_3->addAction(actionSaveChess);
        menu_4->addAction(actionLoadInit);
        menu_4->addAction(actionLoadFromFile);
        menu_6->addAction(actionDebug);
        menu_6->addAction(actionPauseTimer);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionPVP->setText(QApplication::translate("MainWindow", "\345\217\214\344\272\272\345\257\271\345\274\210", nullptr));
        actionLoadInit->setText(QApplication::translate("MainWindow", "\345\210\235\345\247\213\345\261\200\351\235\242", nullptr));
        actionLoadFromFile->setText(QApplication::translate("MainWindow", "\344\273\216\346\226\207\344\273\266\350\275\275\345\205\245..", nullptr));
        actionSaveChess->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230\345\261\200\351\235\242", nullptr));
        actionGiveIn->setText(QApplication::translate("MainWindow", "\350\256\244\350\276\223", nullptr));
        actionCreateHost->setText(QApplication::translate("MainWindow", "\345\210\233\345\273\272\344\270\273\346\234\272", nullptr));
        actionConnectHost->setText(QApplication::translate("MainWindow", "\350\277\236\346\216\245\344\270\273\346\234\272", nullptr));
        actionDebug->setText(QApplication::translate("MainWindow", "\345\274\200\345\220\257\350\260\203\350\257\225", nullptr));
        actionPauseTimer->setText(QApplication::translate("MainWindow", "\350\256\241\346\227\266\346\232\202\345\201\234", nullptr));
        labelNowColor->setText(QApplication::translate("MainWindow", "\346\211\247\345\255\220\346\226\271\357\274\232", nullptr));
        labelMyColor->setText(QApplication::translate("MainWindow", "\346\210\221\346\226\271\357\274\232", nullptr));
        menu->setTitle(QApplication::translate("MainWindow", "\346\270\270\346\210\217", nullptr));
        menu_5->setTitle(QApplication::translate("MainWindow", "\350\201\224\346\234\272\345\257\271\345\274\210", nullptr));
        menu_3->setTitle(QApplication::translate("MainWindow", "\345\261\200\351\235\242", nullptr));
        menu_4->setTitle(QApplication::translate("MainWindow", "\350\275\275\345\205\245\345\261\200\351\235\242", nullptr));
        menu_6->setTitle(QApplication::translate("MainWindow", "\351\200\211\351\241\271", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
