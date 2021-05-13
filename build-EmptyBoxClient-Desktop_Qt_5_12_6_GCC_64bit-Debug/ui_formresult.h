/********************************************************************************
** Form generated from reading UI file 'formresult.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMRESULT_H
#define UI_FORMRESULT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormResult
{
public:
    QLabel *PhotoLab;
    QLabel *camLab;
    QLabel *modeLab;
    QLabel *timeLab;
    QLabel *resultLab;
    QLabel *rfidLab;

    void setupUi(QWidget *FormResult)
    {
        if (FormResult->objectName().isEmpty())
            FormResult->setObjectName(QString::fromUtf8("FormResult"));
        FormResult->resize(250, 120);
        FormResult->setStyleSheet(QString::fromUtf8(""));
        PhotoLab = new QLabel(FormResult);
        PhotoLab->setObjectName(QString::fromUtf8("PhotoLab"));
        PhotoLab->setGeometry(QRect(5, 5, 144, 108));
        PhotoLab->setStyleSheet(QString::fromUtf8("background-image: url(:/Images/photobg.png);"));
        camLab = new QLabel(FormResult);
        camLab->setObjectName(QString::fromUtf8("camLab"));
        camLab->setGeometry(QRect(160, 27, 81, 18));
        camLab->setStyleSheet(QString::fromUtf8("font-family: \"Microsoft Yahei\";font-size:13px;background:transparent;color:#00e4ff;"));
        modeLab = new QLabel(FormResult);
        modeLab->setObjectName(QString::fromUtf8("modeLab"));
        modeLab->setGeometry(QRect(160, 49, 81, 18));
        modeLab->setStyleSheet(QString::fromUtf8("font-family: \"Microsoft Yahei\";font-size:13px;background:transparent;color:#00e4ff;"));
        timeLab = new QLabel(FormResult);
        timeLab->setObjectName(QString::fromUtf8("timeLab"));
        timeLab->setGeometry(QRect(160, 71, 81, 18));
        timeLab->setStyleSheet(QString::fromUtf8("font-family: \"Microsoft Yahei\";font-size:13px;background:transparent;color:#00e4ff;"));
        resultLab = new QLabel(FormResult);
        resultLab->setObjectName(QString::fromUtf8("resultLab"));
        resultLab->setGeometry(QRect(160, 93, 81, 18));
        resultLab->setStyleSheet(QString::fromUtf8("font-family: \"Microsoft Yahei\";font-size:13px;background:transparent;color:#00e4ff;"));
        rfidLab = new QLabel(FormResult);
        rfidLab->setObjectName(QString::fromUtf8("rfidLab"));
        rfidLab->setGeometry(QRect(160, 5, 81, 20));
        rfidLab->setStyleSheet(QString::fromUtf8("font-family: \"Microsoft Yahei\";font-size:13px;background:transparent;color:#00e4ff;"));

        retranslateUi(FormResult);

        QMetaObject::connectSlotsByName(FormResult);
    } // setupUi

    void retranslateUi(QWidget *FormResult)
    {
        FormResult->setWindowTitle(QApplication::translate("FormResult", "Form", nullptr));
        PhotoLab->setText(QString());
        camLab->setText(QApplication::translate("FormResult", "\344\275\215\347\275\256:\346\221\204\345\203\217\345\244\2641", nullptr));
        modeLab->setText(QApplication::translate("FormResult", "\346\250\241\345\274\217:\346\263\250\345\206\214", nullptr));
        timeLab->setText(QApplication::translate("FormResult", "\346\227\266\351\227\264:12:20:39", nullptr));
        resultLab->setText(QApplication::translate("FormResult", "\347\273\223\346\236\234:\346\210\220\345\212\237", nullptr));
        rfidLab->setText(QApplication::translate("FormResult", "RFID\345\217\267:FFFF", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FormResult: public Ui_FormResult {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMRESULT_H
