/********************************************************************************
** Form generated from reading UI file 'frmbattery.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMBATTERY_H
#define UI_FRMBATTERY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>
#include "battery.h"

QT_BEGIN_NAMESPACE

class Ui_frmBattery
{
public:
    Battery *battery;
    QSlider *horizontalSlider;

    void setupUi(QWidget *frmBattery)
    {
        if (frmBattery->objectName().isEmpty())
            frmBattery->setObjectName(QString::fromUtf8("frmBattery"));
        frmBattery->resize(800, 600);
        battery = new Battery(frmBattery);
        battery->setObjectName(QString::fromUtf8("battery"));
        battery->setGeometry(QRect(9, 9, 482, 257));
        horizontalSlider = new QSlider(frmBattery);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(9, 272, 481, 19));
        horizontalSlider->setMaximum(100);
        horizontalSlider->setOrientation(Qt::Horizontal);
        horizontalSlider->setInvertedControls(false);

        retranslateUi(frmBattery);

        QMetaObject::connectSlotsByName(frmBattery);
    } // setupUi

    void retranslateUi(QWidget *frmBattery)
    {
        frmBattery->setWindowTitle(QApplication::translate("frmBattery", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class frmBattery: public Ui_frmBattery {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMBATTERY_H
