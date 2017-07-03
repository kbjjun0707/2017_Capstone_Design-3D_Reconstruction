/********************************************************************************
** Form generated from reading UI file 'distancedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISTANCEDIALOG_H
#define UI_DISTANCEDIALOG_H

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

class Ui_Dialog2
{
public:
    QDialogButtonBox *buttonBox;
    QGroupBox *groupBox;
    QWidget *layoutWidget_3;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QDoubleSpinBox *minspinbox;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QDoubleSpinBox *maxspinbox;
    QGroupBox *groupBox_2;
    QWidget *layoutWidget_4;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QDoubleSpinBox *pointsizespinbox;

    void setupUi(QDialog *Dialog2)
    {
        if (Dialog2->objectName().isEmpty())
            Dialog2->setObjectName(QStringLiteral("Dialog2"));
        Dialog2->resize(255, 230);
        Dialog2->setMinimumSize(QSize(255, 230));
        Dialog2->setMaximumSize(QSize(255, 230));
        buttonBox = new QDialogButtonBox(Dialog2);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(40, 190, 201, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        groupBox = new QGroupBox(Dialog2);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 230, 100));
        groupBox->setFlat(true);
        layoutWidget_3 = new QWidget(groupBox);
        layoutWidget_3->setObjectName(QStringLiteral("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(10, 20, 216, 72));
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

        minspinbox = new QDoubleSpinBox(layoutWidget_3);
        minspinbox->setObjectName(QStringLiteral("minspinbox"));
        minspinbox->setMinimumSize(QSize(80, 25));
        minspinbox->setMaximumSize(QSize(55, 25));
        minspinbox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        minspinbox->setDecimals(1);
        minspinbox->setMinimum(0);
        minspinbox->setMaximum(1000);
        minspinbox->setSingleStep(10);
        minspinbox->setValue(0);

        horizontalLayout_4->addWidget(minspinbox);


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

        maxspinbox = new QDoubleSpinBox(layoutWidget_3);
        maxspinbox->setObjectName(QStringLiteral("maxspinbox"));
        maxspinbox->setMinimumSize(QSize(80, 25));
        maxspinbox->setMaximumSize(QSize(55, 25));
        maxspinbox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        maxspinbox->setDecimals(1);
        maxspinbox->setMinimum(0);
        maxspinbox->setMaximum(10000);
        maxspinbox->setSingleStep(10);
        maxspinbox->setValue(255);

        horizontalLayout_5->addWidget(maxspinbox);


        verticalLayout_3->addLayout(horizontalLayout_5);

        groupBox_2 = new QGroupBox(Dialog2);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 120, 236, 69));
        groupBox_2->setFlat(true);
        layoutWidget_4 = new QWidget(groupBox_2);
        layoutWidget_4->setObjectName(QStringLiteral("layoutWidget_4"));
        layoutWidget_4->setGeometry(QRect(10, 20, 216, 29));
        verticalLayout_4 = new QVBoxLayout(layoutWidget_4);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(2);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_6 = new QLabel(layoutWidget_4);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setMinimumSize(QSize(130, 0));
        label_6->setMaximumSize(QSize(130, 16777215));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_6->addWidget(label_6);

        pointsizespinbox = new QDoubleSpinBox(layoutWidget_4);
        pointsizespinbox->setObjectName(QStringLiteral("pointsizespinbox"));
        pointsizespinbox->setMinimumSize(QSize(80, 25));
        pointsizespinbox->setMaximumSize(QSize(55, 25));
        pointsizespinbox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        pointsizespinbox->setDecimals(2);
        pointsizespinbox->setMinimum(1);
        pointsizespinbox->setMaximum(20);
        pointsizespinbox->setSingleStep(1);
        pointsizespinbox->setValue(1);

        horizontalLayout_6->addWidget(pointsizespinbox);


        verticalLayout_4->addLayout(horizontalLayout_6);


        retranslateUi(Dialog2);
        QObject::connect(buttonBox, SIGNAL(accepted()), Dialog2, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Dialog2, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog2);
    } // setupUi

    void retranslateUi(QDialog *Dialog2)
    {
        Dialog2->setWindowTitle(QApplication::translate("Dialog2", "Options", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("Dialog2", "Distance", Q_NULLPTR));
        label_4->setText(QApplication::translate("Dialog2", "Min : ", Q_NULLPTR));
        label_5->setText(QApplication::translate("Dialog2", "Max : ", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("Dialog2", "Point Size", Q_NULLPTR));
        label_6->setText(QApplication::translate("Dialog2", "Size : ", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Dialog2: public Ui_Dialog2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISTANCEDIALOG_H
