/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayoutRoot;
    QFrame *topBarFrame;
    QHBoxLayout *topBarLayout;
    QLabel *lblSpeed;
    QLabel *lblBattery;
    QLabel *lblGps;
    QSpacerItem *spacerTop;
    QLabel *lblGear;
    QFrame *alertFrame;
    QHBoxLayout *alertLayout;
    QLabel *lblAlertTitle;
    QLabel *lblAlertText;
    QStackedWidget *stackedPages;
    QFrame *bottomNavFrame;
    QHBoxLayout *bottomNavLayout;
    QPushButton *btnHome;
    QPushButton *btnNav;
    QPushButton *btnCam;
    QPushButton *btnSettings;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayoutRoot = new QVBoxLayout(centralwidget);
        verticalLayoutRoot->setSpacing(10);
        verticalLayoutRoot->setObjectName("verticalLayoutRoot");
        verticalLayoutRoot->setContentsMargins(12, 12, 12, 12);
        topBarFrame = new QFrame(centralwidget);
        topBarFrame->setObjectName("topBarFrame");
        topBarFrame->setStyleSheet(QString::fromUtf8("QFrame{background:#171a21;border-radius:14px;} QLabel{color:white; font-size:16px;}"));
        topBarLayout = new QHBoxLayout(topBarFrame);
        topBarLayout->setSpacing(16);
        topBarLayout->setObjectName("topBarLayout");
        topBarLayout->setContentsMargins(12, 10, 12, 10);
        lblSpeed = new QLabel(topBarFrame);
        lblSpeed->setObjectName("lblSpeed");

        topBarLayout->addWidget(lblSpeed);

        lblBattery = new QLabel(topBarFrame);
        lblBattery->setObjectName("lblBattery");

        topBarLayout->addWidget(lblBattery);

        lblGps = new QLabel(topBarFrame);
        lblGps->setObjectName("lblGps");

        topBarLayout->addWidget(lblGps);

        spacerTop = new QSpacerItem(200, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        topBarLayout->addItem(spacerTop);

        lblGear = new QLabel(topBarFrame);
        lblGear->setObjectName("lblGear");
        lblGear->setStyleSheet(QString::fromUtf8("QLabel{font-weight:800;font-size:20px;}"));

        topBarLayout->addWidget(lblGear);


        verticalLayoutRoot->addWidget(topBarFrame);

        alertFrame = new QFrame(centralwidget);
        alertFrame->setObjectName("alertFrame");
        alertFrame->setVisible(false);
        alertFrame->setStyleSheet(QString::fromUtf8("QFrame{background:#6B4B16;border-radius:10px;} QLabel{color:white;}"));
        alertLayout = new QHBoxLayout(alertFrame);
        alertLayout->setSpacing(10);
        alertLayout->setObjectName("alertLayout");
        alertLayout->setContentsMargins(10, 8, 10, 8);
        lblAlertTitle = new QLabel(alertFrame);
        lblAlertTitle->setObjectName("lblAlertTitle");
        lblAlertTitle->setStyleSheet(QString::fromUtf8("QLabel{font-weight:800;}"));

        alertLayout->addWidget(lblAlertTitle);

        lblAlertText = new QLabel(alertFrame);
        lblAlertText->setObjectName("lblAlertText");

        alertLayout->addWidget(lblAlertText);


        verticalLayoutRoot->addWidget(alertFrame);

        stackedPages = new QStackedWidget(centralwidget);
        stackedPages->setObjectName("stackedPages");

        verticalLayoutRoot->addWidget(stackedPages);

        bottomNavFrame = new QFrame(centralwidget);
        bottomNavFrame->setObjectName("bottomNavFrame");
        bottomNavFrame->setStyleSheet(QString::fromUtf8("\n"
"QFrame{background:#171a21;border-radius:16px;}\n"
"QPushButton{height:54px;border-radius:12px;color:white;background:#222634;font-size:16px;}\n"
"QPushButton:pressed{background:#2d3245;}\n"
"       "));
        bottomNavLayout = new QHBoxLayout(bottomNavFrame);
        bottomNavLayout->setSpacing(10);
        bottomNavLayout->setObjectName("bottomNavLayout");
        bottomNavLayout->setContentsMargins(10, 10, 10, 10);
        btnHome = new QPushButton(bottomNavFrame);
        btnHome->setObjectName("btnHome");

        bottomNavLayout->addWidget(btnHome);

        btnNav = new QPushButton(bottomNavFrame);
        btnNav->setObjectName("btnNav");

        bottomNavLayout->addWidget(btnNav);

        btnCam = new QPushButton(bottomNavFrame);
        btnCam->setObjectName("btnCam");

        bottomNavLayout->addWidget(btnCam);

        btnSettings = new QPushButton(bottomNavFrame);
        btnSettings->setObjectName("btnSettings");

        bottomNavLayout->addWidget(btnSettings);


        verticalLayoutRoot->addWidget(bottomNavFrame);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "InterfaceGPS", nullptr));
        lblSpeed->setText(QCoreApplication::translate("MainWindow", "0 km/h", nullptr));
        lblBattery->setText(QCoreApplication::translate("MainWindow", "Bat 100%", nullptr));
        lblGps->setText(QCoreApplication::translate("MainWindow", "GPS OK", nullptr));
        lblGear->setText(QCoreApplication::translate("MainWindow", "D", nullptr));
        lblAlertTitle->setText(QCoreApplication::translate("MainWindow", "ALERTE", nullptr));
        lblAlertText->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        btnHome->setText(QCoreApplication::translate("MainWindow", "Home", nullptr));
        btnNav->setText(QCoreApplication::translate("MainWindow", "Nav", nullptr));
        btnCam->setText(QCoreApplication::translate("MainWindow", "Cam", nullptr));
        btnSettings->setText(QCoreApplication::translate("MainWindow", "Settings", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
