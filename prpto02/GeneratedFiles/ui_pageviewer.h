/********************************************************************************
** Form generated from reading UI file 'pageviewer.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAGEVIEWER_H
#define UI_PAGEVIEWER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "filerender.h"

QT_BEGIN_NAMESPACE

class Ui_ViewerClass
{
public:
    QAction *menuBack;
    QAction *menuQuit;
    QAction *menuColor;
    QAction *menuOption;
    QAction *menuViewbox;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    FileRender *openGLWidget;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QToolButton *tbtn_dir;
    QPushButton *btn_render;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menutools;

    void setupUi(QMainWindow *ViewerClass)
    {
        if (ViewerClass->objectName().isEmpty())
            ViewerClass->setObjectName(QStringLiteral("ViewerClass"));
        ViewerClass->resize(888, 629);
        ViewerClass->setMinimumSize(QSize(888, 629));
        ViewerClass->setMaximumSize(QSize(16777215, 16777215));
        menuBack = new QAction(ViewerClass);
        menuBack->setObjectName(QStringLiteral("menuBack"));
        menuQuit = new QAction(ViewerClass);
        menuQuit->setObjectName(QStringLiteral("menuQuit"));
        menuColor = new QAction(ViewerClass);
        menuColor->setObjectName(QStringLiteral("menuColor"));
        menuColor->setCheckable(true);
        menuColor->setChecked(true);
        menuOption = new QAction(ViewerClass);
        menuOption->setObjectName(QStringLiteral("menuOption"));
        menuViewbox = new QAction(ViewerClass);
        menuViewbox->setObjectName(QStringLiteral("menuViewbox"));
        menuViewbox->setCheckable(true);
        menuViewbox->setChecked(true);
        centralwidget = new QWidget(ViewerClass);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        openGLWidget = new FileRender(centralwidget);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));

        verticalLayout->addWidget(openGLWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        tbtn_dir = new QToolButton(centralwidget);
        tbtn_dir->setObjectName(QStringLiteral("tbtn_dir"));

        horizontalLayout->addWidget(tbtn_dir);

        btn_render = new QPushButton(centralwidget);
        btn_render->setObjectName(QStringLiteral("btn_render"));

        horizontalLayout->addWidget(btn_render);

        horizontalLayout->setStretch(0, 3);

        verticalLayout->addLayout(horizontalLayout);

        verticalLayout->setStretch(0, 1);

        horizontalLayout_2->addLayout(verticalLayout);

        ViewerClass->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ViewerClass);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 888, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menutools = new QMenu(menubar);
        menutools->setObjectName(QStringLiteral("menutools"));
        ViewerClass->setMenuBar(menubar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menutools->menuAction());
        menuFile->addAction(menuBack);
        menuFile->addSeparator();
        menuFile->addAction(menuQuit);
        menutools->addAction(menuViewbox);
        menutools->addAction(menuColor);
        menutools->addSeparator();
        menutools->addAction(menuOption);

        retranslateUi(ViewerClass);

        QMetaObject::connectSlotsByName(ViewerClass);
    } // setupUi

    void retranslateUi(QMainWindow *ViewerClass)
    {
        ViewerClass->setWindowTitle(QApplication::translate("ViewerClass", "3D Scanner", Q_NULLPTR));
        menuBack->setText(QApplication::translate("ViewerClass", "Back", Q_NULLPTR));
        menuQuit->setText(QApplication::translate("ViewerClass", "Quit", Q_NULLPTR));
        menuColor->setText(QApplication::translate("ViewerClass", "Color", Q_NULLPTR));
        menuOption->setText(QApplication::translate("ViewerClass", "Option", Q_NULLPTR));
        menuViewbox->setText(QApplication::translate("ViewerClass", "View Box", Q_NULLPTR));
        tbtn_dir->setText(QApplication::translate("ViewerClass", "...", Q_NULLPTR));
        btn_render->setText(QApplication::translate("ViewerClass", "render", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("ViewerClass", "File", Q_NULLPTR));
        menutools->setTitle(QApplication::translate("ViewerClass", "Tools", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ViewerClass: public Ui_ViewerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAGEVIEWER_H
