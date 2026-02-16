/********************************************************************************
** Form generated from reading UI file 'camerapage.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERAPAGE_H
#define UI_CAMERAPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CameraPage
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QVBoxLayout *layoutInner;
    QFrame *videoPlaceholder;
    QVBoxLayout *videoLayout;
    QLabel *lblVideo;
    QLabel *lblMode;
    QHBoxLayout *rowButtons;
    QPushButton *btnRear;
    QPushButton *btnFront;
    QPushButton *btnMosaic;
    QPushButton *btnBird;

    void setupUi(QWidget *CameraPage)
    {
        if (CameraPage->objectName().isEmpty())
            CameraPage->setObjectName("CameraPage");
        verticalLayout = new QVBoxLayout(CameraPage);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(14, 14, 14, 14);
        frame = new QFrame(CameraPage);
        frame->setObjectName("frame");
        frame->setStyleSheet(QString::fromUtf8("\n"
"QFrame{background:#171a21;border-radius:16px;}\n"
"QLabel{color:white;}\n"
"QPushButton{height:48px;border-radius:12px;color:white;background:#222634;font-size:15px;padding:8px;}\n"
"QPushButton:pressed{background:#2d3245;}\n"
"      "));
        layoutInner = new QVBoxLayout(frame);
        layoutInner->setSpacing(10);
        layoutInner->setObjectName("layoutInner");
        layoutInner->setContentsMargins(14, 14, 14, 14);
        videoPlaceholder = new QFrame(frame);
        videoPlaceholder->setObjectName("videoPlaceholder");
        videoPlaceholder->setMinimumHeight(240);
        videoPlaceholder->setStyleSheet(QString::fromUtf8("QFrame{background:#0f1115;border-radius:14px;border:1px solid #2a2f3a;}"));
        videoLayout = new QVBoxLayout(videoPlaceholder);
        videoLayout->setSpacing(6);
        videoLayout->setObjectName("videoLayout");
        videoLayout->setContentsMargins(10, 10, 10, 10);
        lblVideo = new QLabel(videoPlaceholder);
        lblVideo->setObjectName("lblVideo");
        lblVideo->setAlignment(Qt::AlignCenter);
        lblVideo->setStyleSheet(QString::fromUtf8("QLabel{color:#b8c0cc;font-size:16px;}"));

        videoLayout->addWidget(lblVideo);

        lblMode = new QLabel(videoPlaceholder);
        lblMode->setObjectName("lblMode");
        lblMode->setAlignment(Qt::AlignCenter);
        lblMode->setStyleSheet(QString::fromUtf8("QLabel{font-size:16px;font-weight:700;}"));

        videoLayout->addWidget(lblMode);


        layoutInner->addWidget(videoPlaceholder);

        rowButtons = new QHBoxLayout();
        rowButtons->setSpacing(10);
        rowButtons->setObjectName("rowButtons");
        btnRear = new QPushButton(frame);
        btnRear->setObjectName("btnRear");

        rowButtons->addWidget(btnRear);

        btnFront = new QPushButton(frame);
        btnFront->setObjectName("btnFront");

        rowButtons->addWidget(btnFront);

        btnMosaic = new QPushButton(frame);
        btnMosaic->setObjectName("btnMosaic");

        rowButtons->addWidget(btnMosaic);

        btnBird = new QPushButton(frame);
        btnBird->setObjectName("btnBird");

        rowButtons->addWidget(btnBird);


        layoutInner->addLayout(rowButtons);


        verticalLayout->addWidget(frame);


        retranslateUi(CameraPage);

        QMetaObject::connectSlotsByName(CameraPage);
    } // setupUi

    void retranslateUi(QWidget *CameraPage)
    {
        lblVideo->setText(QCoreApplication::translate("CameraPage", "Flux cam\303\251ra / Bird-eye - placeholder", nullptr));
        lblMode->setText(QCoreApplication::translate("CameraPage", "Mode: BIRD-EYE", nullptr));
        btnRear->setText(QCoreApplication::translate("CameraPage", "Rear", nullptr));
        btnFront->setText(QCoreApplication::translate("CameraPage", "Front", nullptr));
        btnMosaic->setText(QCoreApplication::translate("CameraPage", "Mosaic", nullptr));
        btnBird->setText(QCoreApplication::translate("CameraPage", "Bird", nullptr));
        (void)CameraPage;
    } // retranslateUi

};

namespace Ui {
    class CameraPage: public Ui_CameraPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERAPAGE_H
