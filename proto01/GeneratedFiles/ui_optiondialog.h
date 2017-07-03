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
    QDialogButtonBox *buttonBox;
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QDoubleSpinBox *trackerspinbox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QDoubleSpinBox *depthspinbox;
    QGroupBox *groupBox_2;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QDoubleSpinBox *blocksizepinbox;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(350, 190);
        Dialog->setMinimumSize(QSize(350, 190));
        Dialog->setMaximumSize(QSize(350, 190));
        buttonBox = new QDialogButtonBox(Dialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(269, 10, 75, 52));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        groupBox = new QGroupBox(Dialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 9, 250, 100));
        groupBox->setMinimumSize(QSize(250, 100));
        groupBox->setMaximumSize(QSize(250, 100));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        groupBox->setFont(font);
        groupBox->setFlat(true);
        groupBox->setCheckable(false);
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 20, 211, 72));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(130, 0));
        label->setMaximumSize(QSize(130, 16777215));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label);

        trackerspinbox = new QDoubleSpinBox(layoutWidget);
        trackerspinbox->setObjectName(QStringLiteral("trackerspinbox"));
        trackerspinbox->setMinimumSize(QSize(55, 25));
        trackerspinbox->setMaximumSize(QSize(55, 25));
        trackerspinbox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        trackerspinbox->setMaximum(1);
        trackerspinbox->setSingleStep(0.05);

        horizontalLayout->addWidget(trackerspinbox);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(130, 0));
        label_2->setMaximumSize(QSize(130, 16777215));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label_2);

        depthspinbox = new QDoubleSpinBox(layoutWidget);
        depthspinbox->setObjectName(QStringLiteral("depthspinbox"));
        depthspinbox->setMinimumSize(QSize(55, 25));
        depthspinbox->setMaximumSize(QSize(55, 25));
        depthspinbox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        depthspinbox->setMaximum(1);
        depthspinbox->setSingleStep(0.05);

        horizontalLayout_2->addWidget(depthspinbox);


        verticalLayout->addLayout(horizontalLayout_2);

        groupBox_2 = new QGroupBox(Dialog);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 120, 250, 69));
        groupBox_2->setMinimumSize(QSize(250, 0));
        groupBox_2->setMaximumSize(QSize(250, 16777215));
        groupBox_2->setFlat(true);
        layoutWidget_2 = new QWidget(groupBox_2);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(10, 20, 211, 34));
        verticalLayout_2 = new QVBoxLayout(layoutWidget_2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(2);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(layoutWidget_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMinimumSize(QSize(130, 30));
        label_3->setMaximumSize(QSize(130, 30));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(label_3);

        blocksizepinbox = new QDoubleSpinBox(layoutWidget_2);
        blocksizepinbox->setObjectName(QStringLiteral("blocksizepinbox"));
        blocksizepinbox->setMinimumSize(QSize(55, 25));
        blocksizepinbox->setMaximumSize(QSize(55, 25));
        blocksizepinbox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        blocksizepinbox->setDecimals(0);
        blocksizepinbox->setMinimum(3);
        blocksizepinbox->setMaximum(101);
        blocksizepinbox->setSingleStep(2);

        horizontalLayout_3->addWidget(blocksizepinbox);


        verticalLayout_2->addLayout(horizontalLayout_3);


        retranslateUi(Dialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), Dialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Dialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Option", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("Dialog", "Down Scale", Q_NULLPTR));
        label->setText(QApplication::translate("Dialog", "Tracker : ", Q_NULLPTR));
        label_2->setText(QApplication::translate("Dialog", "Depth Maker : ", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("Dialog", "Stereo Option", Q_NULLPTR));
        label_3->setText(QApplication::translate("Dialog", "Block Size : ", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONDIALOG_H
