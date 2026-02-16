/********************************************************************************
** Form generated from reading UI file 'navigationpage.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NAVIGATIONPAGE_H
#define UI_NAVIGATIONPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NavigationPage
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QVBoxLayout *layoutInner;
    QHBoxLayout *rowSearch;
    QLineEdit *editSearch;
    QPushButton *btnSearch;
    QFrame *mapPlaceholder;
    QVBoxLayout *mapLayout;
    QLabel *lblMap;
    QHBoxLayout *rowInfo;
    QLabel *lblLat;
    QLabel *lblLon;
    QSpacerItem *sp;
    QPushButton *btnCenter;
    QPushButton *btnZoomIn;
    QPushButton *btnZoomOut;

    void setupUi(QWidget *NavigationPage)
    {
        if (NavigationPage->objectName().isEmpty())
            NavigationPage->setObjectName("NavigationPage");
        verticalLayout = new QVBoxLayout(NavigationPage);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(14, 14, 14, 14);
        frame = new QFrame(NavigationPage);
        frame->setObjectName("frame");
        frame->setStyleSheet(QString::fromUtf8("\n"
"QFrame{background:#171a21;border-radius:16px;}\n"
"QLabel{color:white;}\n"
"QLineEdit{height:40px; border-radius:10px; background:#2a2f3a; color:white; padding: 0 10px; font-size:15px; border:1px solid #3d4455;}\n"
"QPushButton{height:48px;border-radius:12px;color:white;background:#222634;font-size:15px;padding:8px;}\n"
"QPushButton:pressed{background:#2d3245;}\n"
"      "));
        layoutInner = new QVBoxLayout(frame);
        layoutInner->setSpacing(10);
        layoutInner->setObjectName("layoutInner");
        layoutInner->setContentsMargins(14, 14, 14, 14);
        rowSearch = new QHBoxLayout();
        rowSearch->setSpacing(10);
        rowSearch->setObjectName("rowSearch");
        editSearch = new QLineEdit(frame);
        editSearch->setObjectName("editSearch");

        rowSearch->addWidget(editSearch);

        btnSearch = new QPushButton(frame);
        btnSearch->setObjectName("btnSearch");
        btnSearch->setMinimumWidth(100);

        rowSearch->addWidget(btnSearch);


        layoutInner->addLayout(rowSearch);

        mapPlaceholder = new QFrame(frame);
        mapPlaceholder->setObjectName("mapPlaceholder");
        mapPlaceholder->setMinimumHeight(240);
        mapPlaceholder->setStyleSheet(QString::fromUtf8("QFrame{background:#0f1115;border-radius:14px;border:1px solid #2a2f3a;}"));
        mapLayout = new QVBoxLayout(mapPlaceholder);
        mapLayout->setObjectName("mapLayout");
        mapLayout->setContentsMargins(10, 10, 10, 10);
        lblMap = new QLabel(mapPlaceholder);
        lblMap->setObjectName("lblMap");
        lblMap->setAlignment(Qt::AlignCenter);
        lblMap->setStyleSheet(QString::fromUtf8("QLabel{color:#b8c0cc;font-size:16px;}"));

        mapLayout->addWidget(lblMap);


        layoutInner->addWidget(mapPlaceholder);

        rowInfo = new QHBoxLayout();
        rowInfo->setSpacing(10);
        rowInfo->setObjectName("rowInfo");
        lblLat = new QLabel(frame);
        lblLat->setObjectName("lblLat");
        lblLat->setStyleSheet(QString::fromUtf8("QLabel{font-size:16px;}"));

        rowInfo->addWidget(lblLat);

        lblLon = new QLabel(frame);
        lblLon->setObjectName("lblLon");
        lblLon->setStyleSheet(QString::fromUtf8("QLabel{font-size:16px;}"));

        rowInfo->addWidget(lblLon);

        sp = new QSpacerItem(160, 10, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        rowInfo->addItem(sp);

        btnCenter = new QPushButton(frame);
        btnCenter->setObjectName("btnCenter");

        rowInfo->addWidget(btnCenter);

        btnZoomIn = new QPushButton(frame);
        btnZoomIn->setObjectName("btnZoomIn");

        rowInfo->addWidget(btnZoomIn);

        btnZoomOut = new QPushButton(frame);
        btnZoomOut->setObjectName("btnZoomOut");

        rowInfo->addWidget(btnZoomOut);


        layoutInner->addLayout(rowInfo);


        verticalLayout->addWidget(frame);


        retranslateUi(NavigationPage);

        QMetaObject::connectSlotsByName(NavigationPage);
    } // setupUi

    void retranslateUi(QWidget *NavigationPage)
    {
        editSearch->setPlaceholderText(QCoreApplication::translate("NavigationPage", "O\303\271 voulez-vous aller ?", nullptr));
        btnSearch->setText(QCoreApplication::translate("NavigationPage", "Aller", nullptr));
        lblMap->setText(QCoreApplication::translate("NavigationPage", "Carte (OSM) - placeholder", nullptr));
        lblLat->setText(QCoreApplication::translate("NavigationPage", "lat: --", nullptr));
        lblLon->setText(QCoreApplication::translate("NavigationPage", "lon: --", nullptr));
        btnCenter->setText(QCoreApplication::translate("NavigationPage", "Centrer", nullptr));
        btnZoomIn->setText(QCoreApplication::translate("NavigationPage", "Zoom +", nullptr));
        btnZoomOut->setText(QCoreApplication::translate("NavigationPage", "Zoom -", nullptr));
        (void)NavigationPage;
    } // retranslateUi

};

namespace Ui {
    class NavigationPage: public Ui_NavigationPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NAVIGATIONPAGE_H
