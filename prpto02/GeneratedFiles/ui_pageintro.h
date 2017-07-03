/********************************************************************************
** Form generated from reading UI file 'pageintro.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAGEINTRO_H
#define UI_PAGEINTRO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IntroClass
{
public:
    QAction *menuQuit;
    QAction *menuViewer;
    QAction *menuScanner;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QLabel *mainlabel;
    QFrame *line;
    QHBoxLayout *horizontalLayout;
    QPushButton *btn_Viewer;
    QPushButton *btn_Startscan;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menutools;

    void setupUi(QMainWindow *IntroClass)
    {
        if (IntroClass->objectName().isEmpty())
            IntroClass->setObjectName(QStringLiteral("IntroClass"));
        IntroClass->resize(435, 383);
        IntroClass->setMinimumSize(QSize(435, 382));
        IntroClass->setMaximumSize(QSize(16777215, 16777215));
        menuQuit = new QAction(IntroClass);
        menuQuit->setObjectName(QStringLiteral("menuQuit"));
        menuViewer = new QAction(IntroClass);
        menuViewer->setObjectName(QStringLiteral("menuViewer"));
        menuScanner = new QAction(IntroClass);
        menuScanner->setObjectName(QStringLiteral("menuScanner"));
        centralWidget = new QWidget(IntroClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(-1, -1, 0, -1);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        mainlabel = new QLabel(centralWidget);
        mainlabel->setObjectName(QStringLiteral("mainlabel"));
        mainlabel->setMinimumSize(QSize(415, 280));
        mainlabel->setMaximumSize(QSize(415, 280));
        mainlabel->setLayoutDirection(Qt::LeftToRight);
        mainlabel->setPixmap(QPixmap(QString::fromUtf8(":/Resources/Resources/3D scanner.png")));
        mainlabel->setScaledContents(true);

        verticalLayout->addWidget(mainlabel);

        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        btn_Viewer = new QPushButton(centralWidget);
        btn_Viewer->setObjectName(QStringLiteral("btn_Viewer"));
        btn_Viewer->setMinimumSize(QSize(160, 50));

        horizontalLayout->addWidget(btn_Viewer);

        btn_Startscan = new QPushButton(centralWidget);
        btn_Startscan->setObjectName(QStringLiteral("btn_Startscan"));
        btn_Startscan->setMinimumSize(QSize(160, 50));

        horizontalLayout->addWidget(btn_Startscan);


        verticalLayout->addLayout(horizontalLayout);

        verticalLayout->setStretch(1, 2);

        horizontalLayout_2->addLayout(verticalLayout);

        IntroClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(IntroClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 435, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menutools = new QMenu(menuBar);
        menutools->setObjectName(QStringLiteral("menutools"));
        IntroClass->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menutools->menuAction());
        menuFile->addSeparator();
        menuFile->addAction(menuQuit);
        menutools->addAction(menuViewer);
        menutools->addAction(menuScanner);

        retranslateUi(IntroClass);

        QMetaObject::connectSlotsByName(IntroClass);
    } // setupUi

    void retranslateUi(QMainWindow *IntroClass)
    {
        IntroClass->setWindowTitle(QApplication::translate("IntroClass", "3D Scanner", Q_NULLPTR));
        menuQuit->setText(QApplication::translate("IntroClass", "Quit", Q_NULLPTR));
        menuViewer->setText(QApplication::translate("IntroClass", "Viewer", Q_NULLPTR));
        menuScanner->setText(QApplication::translate("IntroClass", "Scanner", Q_NULLPTR));
        mainlabel->setText(QString());
        btn_Viewer->setText(QApplication::translate("IntroClass", "Viewer", Q_NULLPTR));
        btn_Startscan->setText(QApplication::translate("IntroClass", "Start Scan", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("IntroClass", "File", Q_NULLPTR));
        menutools->setTitle(QApplication::translate("IntroClass", "Tools", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class IntroClass: public Ui_IntroClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAGEINTRO_H
