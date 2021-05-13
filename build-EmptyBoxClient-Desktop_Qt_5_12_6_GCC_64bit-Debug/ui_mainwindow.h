/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <Controls/roilabel.h>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *logoLab;
    QLabel *_StatCam1;
    QLabel *_StatCam2;
    QLabel *_StatNet;
    QWidget *rigitwidget;
    QWidget *widget;
    QListWidget *listWidget;
    QLabel *WorkStatusLab;
    QWidget *leftwidget;
    QWidget *widget2;
    QLabel *VideoImg2;
    QWidget *widget1;
    QLabel *VideoImg1;
    ROILabel *VideoImgRoi1;
    ROILabel *VideoImgRoi2;
    QPushButton *ROISetBtn;
    QTextEdit *ResultTxt;
    QLabel *versionLab;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        MainWindow->setStyleSheet(QString::fromUtf8("background-image: url(:/Images/BG.png);\n"
""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setStyleSheet(QString::fromUtf8("background:transparent"));
        logoLab = new QLabel(centralwidget);
        logoLab->setObjectName(QString::fromUtf8("logoLab"));
        logoLab->setGeometry(QRect(0, 0, 800, 45));
        logoLab->setStyleSheet(QString::fromUtf8("background-image: url(:/Images/logo.png);"));
        _StatCam1 = new QLabel(centralwidget);
        _StatCam1->setObjectName(QString::fromUtf8("_StatCam1"));
        _StatCam1->setGeometry(QRect(5, 25, 60, 14));
        _StatCam1->setStyleSheet(QString::fromUtf8("font-family: \"Microsoft Yahei\";font-size:10px;background:transparent;color:#ff0000;"));
        _StatCam2 = new QLabel(centralwidget);
        _StatCam2->setObjectName(QString::fromUtf8("_StatCam2"));
        _StatCam2->setGeometry(QRect(70, 25, 60, 14));
        _StatCam2->setStyleSheet(QString::fromUtf8("font-family: \"Microsoft Yahei\";font-size:10px;background:transparent;color:#ff0000;"));
        _StatNet = new QLabel(centralwidget);
        _StatNet->setObjectName(QString::fromUtf8("_StatNet"));
        _StatNet->setGeometry(QRect(5, 10, 60, 14));
        _StatNet->setStyleSheet(QString::fromUtf8("font-family: \"Microsoft Yahei\";font-size:10px;background:transparent;color:#00ff00;"));
        rigitwidget = new QWidget(centralwidget);
        rigitwidget->setObjectName(QString::fromUtf8("rigitwidget"));
        rigitwidget->setGeometry(QRect(510, 55, 282, 535));
        rigitwidget->setStyleSheet(QString::fromUtf8("background-image: url(:/Images/right.png);"));
        widget = new QWidget(rigitwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(5, 40, 272, 480));
        widget->setStyleSheet(QString::fromUtf8("background:transparent"));
        listWidget = new QListWidget(widget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(0, 0, 270, 480));
        listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        listWidget->setResizeMode(QListView::Adjust);
        listWidget->setViewMode(QListView::ListMode);
        WorkStatusLab = new QLabel(centralwidget);
        WorkStatusLab->setObjectName(QString::fromUtf8("WorkStatusLab"));
        WorkStatusLab->setGeometry(QRect(655, 25, 136, 14));
        WorkStatusLab->setStyleSheet(QString::fromUtf8("background-image: url(:/Images/identify.png);"));
        leftwidget = new QWidget(centralwidget);
        leftwidget->setObjectName(QString::fromUtf8("leftwidget"));
        leftwidget->setGeometry(QRect(5, 55, 494, 535));
        leftwidget->setStyleSheet(QString::fromUtf8("background-image: url(:/Images/left.png);"));
        widget2 = new QWidget(leftwidget);
        widget2->setObjectName(QString::fromUtf8("widget2"));
        widget2->setGeometry(QRect(87, 275, 320, 240));
        widget2->setStyleSheet(QString::fromUtf8("background:transparent"));
        VideoImg2 = new QLabel(widget2);
        VideoImg2->setObjectName(QString::fromUtf8("VideoImg2"));
        VideoImg2->setGeometry(QRect(0, 0, 320, 240));
        VideoImg2->setStyleSheet(QString::fromUtf8(""));
        widget1 = new QWidget(leftwidget);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(87, 20, 320, 240));
        widget1->setStyleSheet(QString::fromUtf8("background:transparent"));
        VideoImg1 = new QLabel(widget1);
        VideoImg1->setObjectName(QString::fromUtf8("VideoImg1"));
        VideoImg1->setGeometry(QRect(0, 0, 320, 240));
        VideoImg1->setLayoutDirection(Qt::LeftToRight);
        VideoImg1->setStyleSheet(QString::fromUtf8(""));
        VideoImgRoi1 = new ROILabel(leftwidget);
        VideoImgRoi1->setObjectName(QString::fromUtf8("VideoImgRoi1"));
        VideoImgRoi1->setGeometry(QRect(87, 20, 320, 240));
        VideoImgRoi1->setMouseTracking(true);
        VideoImgRoi1->setStyleSheet(QString::fromUtf8("background:transparent"));
        VideoImgRoi2 = new ROILabel(leftwidget);
        VideoImgRoi2->setObjectName(QString::fromUtf8("VideoImgRoi2"));
        VideoImgRoi2->setGeometry(QRect(87, 275, 320, 240));
        VideoImgRoi2->setMouseTracking(true);
        VideoImgRoi2->setStyleSheet(QString::fromUtf8("background:transparent"));
        ROISetBtn = new QPushButton(centralwidget);
        ROISetBtn->setObjectName(QString::fromUtf8("ROISetBtn"));
        ROISetBtn->setGeometry(QRect(655, 5, 135, 35));
        ROISetBtn->setStyleSheet(QString::fromUtf8("background:transparent"));
        ROISetBtn->setFlat(true);
        ResultTxt = new QTextEdit(centralwidget);
        ResultTxt->setObjectName(QString::fromUtf8("ResultTxt"));
        ResultTxt->setGeometry(QRect(600, 10, 30, 30));
        ResultTxt->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ResultTxt->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ResultTxt->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        versionLab = new QLabel(centralwidget);
        versionLab->setObjectName(QString::fromUtf8("versionLab"));
        versionLab->setGeometry(QRect(730, 5, 60, 15));
        versionLab->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        logoLab->setText(QString());
        _StatCam1->setText(QApplication::translate("MainWindow", "\346\221\204\345\203\217\345\244\2641:\346\225\205\351\232\234", nullptr));
        _StatCam2->setText(QApplication::translate("MainWindow", "\346\221\204\345\203\217\345\244\2642:\346\225\205\351\232\234", nullptr));
        _StatNet->setText(QApplication::translate("MainWindow", "\347\275\221\347\273\234:\346\255\243\345\270\270", nullptr));
        WorkStatusLab->setText(QString());
        VideoImg2->setText(QString());
        VideoImg1->setText(QString());
        VideoImgRoi1->setText(QString());
        VideoImgRoi2->setText(QString());
        ROISetBtn->setText(QString());
        ResultTxt->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Ubuntu';\">0</span></p></body></html>", nullptr));
        versionLab->setText(QApplication::translate("MainWindow", "V1.0.0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
