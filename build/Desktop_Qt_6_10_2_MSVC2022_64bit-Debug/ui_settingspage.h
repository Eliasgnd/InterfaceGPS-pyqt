/********************************************************************************
** Form generated from reading UI file 'settingspage.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSPAGE_H
#define UI_SETTINGSPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingsPage
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QVBoxLayout *layoutInner;
    QLabel *lblTitle;
    QHBoxLayout *rowTheme;
    QLabel *lblTheme;
    QComboBox *cmbTheme;
    QHBoxLayout *rowBrightness;
    QLabel *lblBright;
    QSlider *sliderBrightness;
    QLabel *lblBrightnessValue;
    QSpacerItem *spacerV;

    void setupUi(QWidget *SettingsPage)
    {
        if (SettingsPage->objectName().isEmpty())
            SettingsPage->setObjectName("SettingsPage");
        verticalLayout = new QVBoxLayout(SettingsPage);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(14, 14, 14, 14);
        frame = new QFrame(SettingsPage);
        frame->setObjectName("frame");
        frame->setStyleSheet(QString::fromUtf8("\n"
"QFrame{background:#171a21;border-radius:16px;}\n"
"QLabel{color:white;}\n"
"QComboBox, QSlider {color:white;}\n"
"QPushButton{height:50px;border-radius:12px;color:white;background:#222634;font-size:15px;padding:8px;}\n"
"QPushButton:pressed{background:#2d3245;}\n"
"      "));
        layoutInner = new QVBoxLayout(frame);
        layoutInner->setSpacing(12);
        layoutInner->setObjectName("layoutInner");
        layoutInner->setContentsMargins(16, 16, 16, 16);
        lblTitle = new QLabel(frame);
        lblTitle->setObjectName("lblTitle");
        lblTitle->setStyleSheet(QString::fromUtf8("QLabel{font-size:22px;font-weight:800;}"));

        layoutInner->addWidget(lblTitle);

        rowTheme = new QHBoxLayout();
        rowTheme->setSpacing(10);
        rowTheme->setObjectName("rowTheme");
        lblTheme = new QLabel(frame);
        lblTheme->setObjectName("lblTheme");
        lblTheme->setStyleSheet(QString::fromUtf8("QLabel{font-size:16px;}"));

        rowTheme->addWidget(lblTheme);

        cmbTheme = new QComboBox(frame);
        cmbTheme->addItem(QString());
        cmbTheme->addItem(QString());
        cmbTheme->setObjectName("cmbTheme");

        rowTheme->addWidget(cmbTheme);


        layoutInner->addLayout(rowTheme);

        rowBrightness = new QHBoxLayout();
        rowBrightness->setSpacing(10);
        rowBrightness->setObjectName("rowBrightness");
        lblBright = new QLabel(frame);
        lblBright->setObjectName("lblBright");
        lblBright->setStyleSheet(QString::fromUtf8("QLabel{font-size:16px;}"));

        rowBrightness->addWidget(lblBright);

        sliderBrightness = new QSlider(frame);
        sliderBrightness->setObjectName("sliderBrightness");
        sliderBrightness->setOrientation(Qt::Horizontal);
        sliderBrightness->setMinimum(0);
        sliderBrightness->setMaximum(100);
        sliderBrightness->setValue(60);

        rowBrightness->addWidget(sliderBrightness);

        lblBrightnessValue = new QLabel(frame);
        lblBrightnessValue->setObjectName("lblBrightnessValue");

        rowBrightness->addWidget(lblBrightnessValue);


        layoutInner->addLayout(rowBrightness);

        spacerV = new QSpacerItem(20, 200, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        layoutInner->addItem(spacerV);


        verticalLayout->addWidget(frame);


        retranslateUi(SettingsPage);

        QMetaObject::connectSlotsByName(SettingsPage);
    } // setupUi

    void retranslateUi(QWidget *SettingsPage)
    {
        lblTitle->setText(QCoreApplication::translate("SettingsPage", "Param\303\250tres", nullptr));
        lblTheme->setText(QCoreApplication::translate("SettingsPage", "Th\303\250me", nullptr));
        cmbTheme->setItemText(0, QCoreApplication::translate("SettingsPage", "Nuit", nullptr));
        cmbTheme->setItemText(1, QCoreApplication::translate("SettingsPage", "Jour", nullptr));

        lblBright->setText(QCoreApplication::translate("SettingsPage", "Luminosit\303\251", nullptr));
        lblBrightnessValue->setText(QCoreApplication::translate("SettingsPage", "60", nullptr));
        (void)SettingsPage;
    } // retranslateUi

};

namespace Ui {
    class SettingsPage: public Ui_SettingsPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSPAGE_H
