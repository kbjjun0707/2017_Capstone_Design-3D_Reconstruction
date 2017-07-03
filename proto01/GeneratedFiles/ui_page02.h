/********************************************************************************
** Form generated from reading UI file 'page02.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAGE02_H
#define UI_PAGE02_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
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
#include <glrender.h>

QT_BEGIN_NAMESPACE

class Ui_page02
{
public:
    QAction *menu02back;
    QAction *menu02quit;
    QAction *menu02option;
    QAction *menu02cammodel;
    QAction *menu02color;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    GlRender *openGLWidget;
    QLabel *lb_disparity;
    QLabel *lb_cmp;
    QLabel *lb_std;
    QLabel *lb_cam;
    QVBoxLayout *verticalLayout_3;
    QPushButton *btn_save;
    QPushButton *btn_clear;
    QPushButton *btn_stop;
    QSpacerItem *verticalSpacer;
    QPushButton *btn_start;
    QLabel *lb_reproject;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuView;
    QMenu *menuEdi;

    void setupUi(QMainWindow *page02)
    {
        if (page02->objectName().isEmpty())
            page02->setObjectName(QStringLiteral("page02"));
        page02->resize(888, 629);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(page02->sizePolicy().hasHeightForWidth());
        page02->setSizePolicy(sizePolicy);
        page02->setMinimumSize(QSize(888, 629));
        page02->setMaximumSize(QSize(888, 629));
        menu02back = new QAction(page02);
        menu02back->setObjectName(QStringLiteral("menu02back"));
        menu02quit = new QAction(page02);
        menu02quit->setObjectName(QStringLiteral("menu02quit"));
        menu02option = new QAction(page02);
        menu02option->setObjectName(QStringLiteral("menu02option"));
        menu02cammodel = new QAction(page02);
        menu02cammodel->setObjectName(QStringLiteral("menu02cammodel"));
        menu02cammodel->setCheckable(true);
        menu02cammodel->setChecked(true);
        menu02color = new QAction(page02);
        menu02color->setObjectName(QStringLiteral("menu02color"));
        menu02color->setCheckable(true);
        menu02color->setChecked(false);
        centralwidget = new QWidget(page02);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        openGLWidget = new GlRender(centralwidget);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        sizePolicy.setHeightForWidth(openGLWidget->sizePolicy().hasHeightForWidth());
        openGLWidget->setSizePolicy(sizePolicy);
        openGLWidget->setMinimumSize(QSize(0, 0));
        openGLWidget->setMaximumSize(QSize(16777215, 16777215));

        gridLayout->addWidget(openGLWidget, 0, 1, 2, 3);

        lb_disparity = new QLabel(centralwidget);
        lb_disparity->setObjectName(QStringLiteral("lb_disparity"));
        sizePolicy.setHeightForWidth(lb_disparity->sizePolicy().hasHeightForWidth());
        lb_disparity->setSizePolicy(sizePolicy);
        lb_disparity->setMinimumSize(QSize(256, 192));
        lb_disparity->setMaximumSize(QSize(256, 192));
        lb_disparity->setFrameShape(QFrame::Box);
        lb_disparity->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lb_disparity, 1, 0, 1, 1);

        lb_cmp = new QLabel(centralwidget);
        lb_cmp->setObjectName(QStringLiteral("lb_cmp"));
        sizePolicy.setHeightForWidth(lb_cmp->sizePolicy().hasHeightForWidth());
        lb_cmp->setSizePolicy(sizePolicy);
        lb_cmp->setMinimumSize(QSize(256, 192));
        lb_cmp->setMaximumSize(QSize(256, 192));
        lb_cmp->setFrameShape(QFrame::Box);
        lb_cmp->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lb_cmp, 2, 2, 1, 1);

        lb_std = new QLabel(centralwidget);
        lb_std->setObjectName(QStringLiteral("lb_std"));
        sizePolicy.setHeightForWidth(lb_std->sizePolicy().hasHeightForWidth());
        lb_std->setSizePolicy(sizePolicy);
        lb_std->setMinimumSize(QSize(256, 192));
        lb_std->setMaximumSize(QSize(256, 192));
        lb_std->setFrameShape(QFrame::Box);
        lb_std->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lb_std, 2, 1, 1, 1);

        lb_cam = new QLabel(centralwidget);
        lb_cam->setObjectName(QStringLiteral("lb_cam"));
        sizePolicy.setHeightForWidth(lb_cam->sizePolicy().hasHeightForWidth());
        lb_cam->setSizePolicy(sizePolicy);
        lb_cam->setMinimumSize(QSize(256, 192));
        lb_cam->setMaximumSize(QSize(256, 192));
        lb_cam->setFrameShape(QFrame::Box);
        lb_cam->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lb_cam, 2, 0, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        btn_save = new QPushButton(centralwidget);
        btn_save->setObjectName(QStringLiteral("btn_save"));
        btn_save->setMinimumSize(QSize(80, 27));
        btn_save->setMaximumSize(QSize(80, 27));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        btn_save->setFont(font);

        verticalLayout_3->addWidget(btn_save);

        btn_clear = new QPushButton(centralwidget);
        btn_clear->setObjectName(QStringLiteral("btn_clear"));
        btn_clear->setMinimumSize(QSize(80, 27));
        btn_clear->setMaximumSize(QSize(80, 27));
        btn_clear->setFont(font);

        verticalLayout_3->addWidget(btn_clear);

        btn_stop = new QPushButton(centralwidget);
        btn_stop->setObjectName(QStringLiteral("btn_stop"));
        btn_stop->setMinimumSize(QSize(80, 27));
        btn_stop->setMaximumSize(QSize(80, 27));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        btn_stop->setFont(font1);

        verticalLayout_3->addWidget(btn_stop);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        btn_start = new QPushButton(centralwidget);
        btn_start->setObjectName(QStringLiteral("btn_start"));
        btn_start->setMinimumSize(QSize(80, 60));
        btn_start->setMaximumSize(QSize(80, 60));
        QFont font2;
        font2.setPointSize(14);
        font2.setBold(true);
        font2.setWeight(75);
        btn_start->setFont(font2);

        verticalLayout_3->addWidget(btn_start);


        gridLayout->addLayout(verticalLayout_3, 2, 3, 1, 1);

        lb_reproject = new QLabel(centralwidget);
        lb_reproject->setObjectName(QStringLiteral("lb_reproject"));
        sizePolicy.setHeightForWidth(lb_reproject->sizePolicy().hasHeightForWidth());
        lb_reproject->setSizePolicy(sizePolicy);
        lb_reproject->setMinimumSize(QSize(256, 192));
        lb_reproject->setMaximumSize(QSize(256, 192));
        lb_reproject->setFrameShape(QFrame::Box);
        lb_reproject->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lb_reproject, 0, 0, 1, 1);


        horizontalLayout->addLayout(gridLayout);

        page02->setCentralWidget(centralwidget);
        menubar = new QMenuBar(page02);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 888, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuView = new QMenu(menubar);
        menuView->setObjectName(QStringLiteral("menuView"));
        menuEdi = new QMenu(menubar);
        menuEdi->setObjectName(QStringLiteral("menuEdi"));
        page02->setMenuBar(menubar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuEdi->menuAction());
        menubar->addAction(menuView->menuAction());
        menuFile->addAction(menu02back);
        menuFile->addAction(menu02quit);
        menuView->addAction(menu02cammodel);
        menuView->addAction(menu02color);
        menuEdi->addAction(menu02option);

        retranslateUi(page02);

        QMetaObject::connectSlotsByName(page02);
    } // setupUi

    void retranslateUi(QMainWindow *page02)
    {
        page02->setWindowTitle(QApplication::translate("page02", "3D scanner", Q_NULLPTR));
        menu02back->setText(QApplication::translate("page02", "Back", Q_NULLPTR));
        menu02quit->setText(QApplication::translate("page02", "Quit", Q_NULLPTR));
        menu02option->setText(QApplication::translate("page02", "Option", Q_NULLPTR));
        menu02cammodel->setText(QApplication::translate("page02", "Camera Model", Q_NULLPTR));
        menu02color->setText(QApplication::translate("page02", "Color", Q_NULLPTR));
        lb_disparity->setText(QString());
        lb_cmp->setText(QString());
        lb_std->setText(QString());
        lb_cam->setText(QString());
        btn_save->setText(QApplication::translate("page02", "save", Q_NULLPTR));
        btn_clear->setText(QApplication::translate("page02", "clear", Q_NULLPTR));
        btn_stop->setText(QApplication::translate("page02", "pause", Q_NULLPTR));
        btn_start->setText(QApplication::translate("page02", "Start", Q_NULLPTR));
        lb_reproject->setText(QString());
        menuFile->setTitle(QApplication::translate("page02", "File", Q_NULLPTR));
        menuView->setTitle(QApplication::translate("page02", "View", Q_NULLPTR));
        menuEdi->setTitle(QApplication::translate("page02", "Edit", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class page02: public Ui_page02 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAGE02_H
