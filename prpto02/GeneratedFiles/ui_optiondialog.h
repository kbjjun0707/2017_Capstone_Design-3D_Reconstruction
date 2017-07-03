/********************************************************************************
** Form generated from reading UI file 'optiondialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTIONDIALOG_H
#define UI_OPTIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QGroupBox *groupBox;
    QWidget *layoutWidget_3;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QDoubleSpinBox *trackerspinbox;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QDoubleSpinBox *depthspinbox;
    QGroupBox *groupBox_2;
    QWidget *layoutWidget_4;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QDoubleSpinBox *blocksizepinbox;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(350, 190);
        Dialog->setMinimumSize(QSize(350, 190));
        Dialog->setMaximumSize(QSize(350, 190));
        groupBox = new QGroupBox(Dialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(11, 9, 250, 100));
        groupBox->setMinimumSize(QSize(250, 100));
        groupBox->setMaximumSize(QSize(250, 100));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        groupBox->setFont(font);
        groupBox->setFlat(true);
        groupBox->setCheckable(false);
        layoutWidget_3 = new QWidget(groupBox);
        layoutWidget_3->setObjectName(QStringLiteral("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(10, 20, 211, 72));
        verticalLayout_3 = new QVBoxLayout(layoutWidget_3);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(2);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_4 = new QLabel(layoutWidget_3);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMinimumSize(QSize(130, 0));
        label_4->setMaximumSize(QSize(130, 16777215));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(label_4);

        trackerspinbox = new QDoubleSpinBox(layoutWidget_3);
        trackerspinbox->setObjectName(QStringLiteral("trackerspinbox"));
        trackerspinbox->setMinimumSize(QSize(55, 25));
        trackerspinbox->setMaximumSize(QSize(55, 25));
        trackerspinbox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        trackerspinbox->setMinimum(0.05);
        trackerspinbox->setMaximum(1);
        trackerspinbox->setSingleStep(0.05);

        horizontalLayout_4->addWidget(trackerspinbox);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(2);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_5 = new QLabel(layoutWidget_3);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setMinimumSize(QSize(130, 0));
        label_5->setMaximumSize(QSize(130, 16777215));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(label_5);

        depthspinbox = new QDoubleSpinBox(layoutWidget_3);
        depthspinbox->setObjectName(QStringLiteral("depthspinbox"));
        depthspinbox->setMinimumSize(QSize(55, 25));
        depthspinbox->setMaximumSize(QSize(55, 25));
        depthspinbox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        depthspinbox->setMinimum(0.05);
        depthspinbox->setMaximum(1);
        depthspinbox->setSingleStep(0.05);

        horizontalLayout_5->addWidget(depthspinbox);


        verticalLayout_3->addLayout(horizontalLayout_5);

        groupBox_2 = new QGroupBox(Dialog);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(11, 120, 250, 69));
        groupBox_2->setMinimumSize(QSize(250, 0));
        groupBox_2->setMaximumSize(QSize(250, 16777215));
        groupBox_2->setFlat(true);
        layoutWidget_4 = new QWidget(groupBox_2);
        layoutWidget_4->setObjectName(QStringLiteral("layoutWidget_4"));
        layoutWidget_4->setGeometry(QRect(10, 20, 211, 34));
        verticalLayout_4 = new QVBoxLayout(layoutWidget_4);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(2);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_6 = new QLabel(layoutWidget_4);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setMinimumSize(QSize(130, 30));
        label_6->setMaximumSize(QSize(130, 30));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_6->addWidget(label_6);

        blocksizepinbox = new QDoubleSpinBox(layoutWidget_4);
        blocksizepinbox->setObjectName(QStringLiteral("blocksizepinbox"));
        blocksizepinbox->setMinimumSize(QSize(55, 25));
        blocksizepinbox->setMaximumSize(QSize(55, 25));
        blocksizepinbox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        blocksizepinbox->setDecimals(0);
        blocksizepinbox->setMinimum(3);
        blocksizepinbox->setMaximum(99);
        blocksizepinbox->setSingleStep(2);

        horizontalLayout_6->addWidget(blocksizepinbox);


        verticalLayout_4->addLayout(horizontalLayout_6);

        buttonBox = new QDialogButtonBox(Dialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(270, 10, 75, 52));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        retranslateUi(Dialog);
        QObject::connect(buttonBox, SIGNAL(clicked(QAbstractButton*)), Dialog, SLOT(close()));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Options", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("Dialog", "Down Scale", Q_NULLPTR));
        label_4->setText(QApplication::translate("Dialog", "Tracker : ", Q_NULLPTR));
        label_5->setText(QApplication::translate("Dialog", "Depth Maker : ", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("Dialog", "Stereo Option", Q_NULLPTR));
        label_6->setText(QApplication::translate("Dialog", "Block Size : ", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONDIALOG_H
