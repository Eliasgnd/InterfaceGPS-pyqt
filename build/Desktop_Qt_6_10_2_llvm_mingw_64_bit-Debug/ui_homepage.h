/********************************************************************************
** Form generated from reading UI file 'homepage.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOMEPAGE_H
#define UI_HOMEPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HomePage
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QVBoxLayout *layoutInner;
    QLabel *lblSpeedBig;
    QLabel *lblSpeedUnit;
    QHBoxLayout *rowCards;
    QLabel *lblBattery;
    QLabel *lblGps;
    QLabel *lblReverse;
    QHBoxLayout *rowButtons;
    QPushButton *btnNav;
    QPushButton *btnCam;

    void setupUi(QWidget *HomePage)
    {
        if (HomePage->objectName().isEmpty())
            HomePage->setObjectName("HomePage");
        verticalLayout = new QVBoxLayout(HomePage);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(14, 14, 14, 14);
        frame = new QFrame(HomePage);
        frame->setObjectName("frame");
        frame->setStyleSheet(QString::fromUtf8("\n"
"QFrame{background:#171a21;border-radius:16px;}\n"
"QLabel{color:white;}\n"
"QPushButton{height:56px;border-radius:14px;color:white;background:#222634;font-size:16px;padding:10px;}\n"
"QPushButton:pressed{background:#2d3245;}\n"
"      "));
        layoutInner = new QVBoxLayout(frame);
        layoutInner->setSpacing(12);
        layoutInner->setObjectName("layoutInner");
        layoutInner->setContentsMargins(20, 20, 20, 20);
        lblSpeedBig = new QLabel(frame);
        lblSpeedBig->setObjectName("lblSpeedBig");
        lblSpeedBig->setAlignment(Qt::AlignCenter);
        lblSpeedBig->setStyleSheet(QString::fromUtf8("QLabel{font-size:72px;font-weight:900;}"));

        layoutInner->addWidget(lblSpeedBig);

        lblSpeedUnit = new QLabel(frame);
        lblSpeedUnit->setObjectName("lblSpeedUnit");
        lblSpeedUnit->setAlignment(Qt::AlignCenter);
        lblSpeedUnit->setStyleSheet(QString::fromUtf8("QLabel{color:#b8c0cc;font-size:18px;}"));

        layoutInner->addWidget(lblSpeedUnit);

        rowCards = new QHBoxLayout();
        rowCards->setSpacing(18);
        rowCards->setObjectName("rowCards");
        lblBattery = new QLabel(frame);
        lblBattery->setObjectName("lblBattery");
        lblBattery->setStyleSheet(QString::fromUtf8("QLabel{font-size:18px;}"));

        rowCards->addWidget(lblBattery);

        lblGps = new QLabel(frame);
        lblGps->setObjectName("lblGps");
        lblGps->setStyleSheet(QString::fromUtf8("QLabel{font-size:18px;}"));

        rowCards->addWidget(lblGps);

        lblReverse = new QLabel(frame);
        lblReverse->setObjectName("lblReverse");
        lblReverse->setStyleSheet(QString::fromUtf8("QLabel{font-size:18px;font-weight:800;}"));

        rowCards->addWidget(lblReverse);


        layoutInner->addLayout(rowCards);

        rowButtons = new QHBoxLayout();
        rowButtons->setSpacing(12);
        rowButtons->setObjectName("rowButtons");
        btnNav = new QPushButton(frame);
        btnNav->setObjectName("btnNav");

        rowButtons->addWidget(btnNav);

        btnCam = new QPushButton(frame);
        btnCam->setObjectName("btnCam");

        rowButtons->addWidget(btnCam);


        layoutInner->addLayout(rowButtons);


        verticalLayout->addWidget(frame);


        retranslateUi(HomePage);

        QMetaObject::connectSlotsByName(HomePage);
    } // setupUi

    void retranslateUi(QWidget *HomePage)
    {
        lblSpeedBig->setText(QCoreApplication::translate("HomePage", "0", nullptr));
        lblSpeedUnit->setText(QCoreApplication::translate("HomePage", "km/h", nullptr));
        lblBattery->setText(QCoreApplication::translate("HomePage", "100%", nullptr));
        lblGps->setText(QCoreApplication::translate("HomePage", "GPS OK", nullptr));
        lblReverse->setText(QCoreApplication::translate("HomePage", "D", nullptr));
        btnNav->setText(QCoreApplication::translate("HomePage", "Navigation", nullptr));
        btnCam->setText(QCoreApplication::translate("HomePage", "Cam\303\251ra", nullptr));
        (void)HomePage;
    } // retranslateUi

};

namespace Ui {
    class HomePage: public Ui_HomePage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOMEPAGE_H
