/********************************************************************************
** Form generated from reading UI file 'BiomakerTool.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BIOMAKERTOOL_H
#define UI_BIOMAKERTOOL_H

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

class Ui_BiomakerToolClass
{
public:
    QAction *action_tif;
    QAction *action_export;
    QAction *action_mark;
    QAction *action_nav;
    QAction *action_exportnav;
    QAction *actionExport_paths;
    QAction *action_paths;
    QAction *actionExport_tif;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuOpen;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *BiomakerToolClass)
    {
        if (BiomakerToolClass->objectName().isEmpty())
            BiomakerToolClass->setObjectName(QString::fromUtf8("BiomakerToolClass"));
        BiomakerToolClass->resize(1111, 709);
        action_tif = new QAction(BiomakerToolClass);
        action_tif->setObjectName(QString::fromUtf8("action_tif"));
        action_export = new QAction(BiomakerToolClass);
        action_export->setObjectName(QString::fromUtf8("action_export"));
        action_mark = new QAction(BiomakerToolClass);
        action_mark->setObjectName(QString::fromUtf8("action_mark"));
        action_nav = new QAction(BiomakerToolClass);
        action_nav->setObjectName(QString::fromUtf8("action_nav"));
        action_exportnav = new QAction(BiomakerToolClass);
        action_exportnav->setObjectName(QString::fromUtf8("action_exportnav"));
        actionExport_paths = new QAction(BiomakerToolClass);
        actionExport_paths->setObjectName(QString::fromUtf8("actionExport_paths"));
        action_paths = new QAction(BiomakerToolClass);
        action_paths->setObjectName(QString::fromUtf8("action_paths"));
        actionExport_tif = new QAction(BiomakerToolClass);
        actionExport_tif->setObjectName(QString::fromUtf8("actionExport_tif"));
        centralWidget = new QWidget(BiomakerToolClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        BiomakerToolClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(BiomakerToolClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1111, 23));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuOpen = new QMenu(menuFile);
        menuOpen->setObjectName(QString::fromUtf8("menuOpen"));
        BiomakerToolClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(BiomakerToolClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        BiomakerToolClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(BiomakerToolClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        BiomakerToolClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(menuOpen->menuAction());
        menuFile->addAction(action_export);
        menuFile->addAction(action_exportnav);
        menuFile->addAction(actionExport_paths);
        menuFile->addAction(actionExport_tif);
        menuOpen->addAction(action_tif);
        menuOpen->addAction(action_mark);
        menuOpen->addAction(action_nav);
        menuOpen->addAction(action_paths);

        retranslateUi(BiomakerToolClass);

        QMetaObject::connectSlotsByName(BiomakerToolClass);
    } // setupUi

    void retranslateUi(QMainWindow *BiomakerToolClass)
    {
        BiomakerToolClass->setWindowTitle(QApplication::translate("BiomakerToolClass", "BiomakerTool", nullptr));
        action_tif->setText(QApplication::translate("BiomakerToolClass", "*.tif", nullptr));
        action_export->setText(QApplication::translate("BiomakerToolClass", "Export(maker)", nullptr));
        action_mark->setText(QApplication::translate("BiomakerToolClass", "*.mark", nullptr));
        action_nav->setText(QApplication::translate("BiomakerToolClass", "*.nav", nullptr));
        action_exportnav->setText(QApplication::translate("BiomakerToolClass", "Export(nav)", nullptr));
        actionExport_paths->setText(QApplication::translate("BiomakerToolClass", "Export(paths)", nullptr));
        action_paths->setText(QApplication::translate("BiomakerToolClass", "*.paths", nullptr));
        actionExport_tif->setText(QApplication::translate("BiomakerToolClass", "Export(png)", nullptr));
        menuFile->setTitle(QApplication::translate("BiomakerToolClass", "File", nullptr));
        menuOpen->setTitle(QApplication::translate("BiomakerToolClass", "Load", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BiomakerToolClass: public Ui_BiomakerToolClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BIOMAKERTOOL_H
