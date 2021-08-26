/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionaaa;
    QAction *actionOpen;
    QAction *actionStop;
    QAction *actionPlay;
    QAction *actionPause;
    QAction *actionLoadTags;
    QAction *actionSaveTags;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menuFiles;
    QMenu *menuTags;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        actionaaa = new QAction(MainWindow);
        actionaaa->setObjectName(QString::fromUtf8("actionaaa"));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionStop = new QAction(MainWindow);
        actionStop->setObjectName(QString::fromUtf8("actionStop"));
        actionPlay = new QAction(MainWindow);
        actionPlay->setObjectName(QString::fromUtf8("actionPlay"));
        actionPause = new QAction(MainWindow);
        actionPause->setObjectName(QString::fromUtf8("actionPause"));
        actionLoadTags = new QAction(MainWindow);
        actionLoadTags->setObjectName(QString::fromUtf8("actionLoadTags"));
        actionSaveTags = new QAction(MainWindow);
        actionSaveTags->setObjectName(QString::fromUtf8("actionSaveTags"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 20));
        menuFiles = new QMenu(menubar);
        menuFiles->setObjectName(QString::fromUtf8("menuFiles"));
        menuTags = new QMenu(menubar);
        menuTags->setObjectName(QString::fromUtf8("menuTags"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFiles->menuAction());
        menubar->addAction(menuTags->menuAction());
        menuFiles->addAction(actionOpen);
        menuFiles->addAction(actionStop);
        menuFiles->addAction(actionPlay);
        menuFiles->addAction(actionPause);
        menuTags->addAction(actionLoadTags);
        menuTags->addAction(actionSaveTags);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionaaa->setText(QApplication::translate("MainWindow", "aaa", nullptr));
        actionOpen->setText(QApplication::translate("MainWindow", "Open Video", nullptr));
        actionStop->setText(QApplication::translate("MainWindow", "Close Video", nullptr));
        actionPlay->setText(QApplication::translate("MainWindow", "Play", nullptr));
        actionPause->setText(QApplication::translate("MainWindow", "Pause", nullptr));
        actionLoadTags->setText(QApplication::translate("MainWindow", "load Tagfile", nullptr));
        actionSaveTags->setText(QApplication::translate("MainWindow", "save Tagfile", nullptr));
        menuFiles->setTitle(QApplication::translate("MainWindow", "Video", nullptr));
        menuTags->setTitle(QApplication::translate("MainWindow", "Tags", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
