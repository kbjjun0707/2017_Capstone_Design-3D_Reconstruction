/********************************************************************************
** Form generated from reading UI file 'page01.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAGE01_H
#define UI_PAGE01_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_page01
{
public:
    QAction *menu01quit;
    QAction *menu01scan;
    QAction *menu01viewer;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *page01)
    {
        if (page01->objectName().isEmpty())
            page01->setObjectName(QStringLiteral("page01"));
        page01->resize(400, 280);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(page01->sizePolicy().hasHeightForWidth());
        page01->setSizePolicy(sizePolicy);
        page01->setMinimumSize(QSize(400, 280));
        menu01quit = new QAction(page01);
        menu01quit->setObjectName(QStringLiteral("menu01quit"));
        menu01scan = new QAction(page01);
        menu01scan->setObjectName(QStringLiteral("menu01scan"));
        menu01viewer = new QAction(page01);
        menu01viewer->setObjectName(QStringLiteral("menu01viewer"));
        centralWidget = new QWidget(page01);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(320, 220));
        label->setMaximumSize(QSize(16777215, 16777215));
        label->setPixmap(QPixmap(QString::fromUtf8(":/proto01/Resources/3D scanner.png")));
        label->setScaledContents(true);

        horizontalLayout->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        horizontalLayout->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout);

        page01->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(page01);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        page01->setMenuBar(menuBar);
        statusBar = new QStatusBar(page01);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        page01->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuFile->addSeparator();
        menuFile->addAction(menu01quit);
        menuEdit->addAction(menu01viewer);
        menuEdit->addSeparator();
        menuEdit->addAction(menu01scan);

        retranslateUi(page01);

        QMetaObject::connectSlotsByName(page01);
    } // setupUi

    void retranslateUi(QMainWindow *page01)
    {
        page01->setWindowTitle(QApplication::translate("page01", "3D scanner", Q_NULLPTR));
        menu01quit->setText(QApplication::translate("page01", "Quit", Q_NULLPTR));
        menu01scan->setText(QApplication::translate("page01", "Scan", Q_NULLPTR));
        menu01viewer->setText(QApplication::translate("page01", "Viewer", Q_NULLPTR));
        label->setText(QString());
        menuFile->setTitle(QApplication::translate("page01", "File", Q_NULLPTR));
        menuEdit->setTitle(QApplication::translate("page01", "Edit", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class page01: public Ui_page01 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAGE01_H
