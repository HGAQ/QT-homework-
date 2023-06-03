/********************************************************************************
** Form generated from reading UI file 'arkmidnight.ui'
**
** Created by: Qt User Interface Compiler version 6.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ARKMIDNIGHT_H
#define UI_ARKMIDNIGHT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ArkMidnight
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QPushButton *btn_guide;
    QPushButton *btn_start;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ArkMidnight)
    {
        if (ArkMidnight->objectName().isEmpty())
            ArkMidnight->setObjectName("ArkMidnight");
        ArkMidnight->resize(780, 540);
        ArkMidnight->setMinimumSize(QSize(780, 540));
        ArkMidnight->setMaximumSize(QSize(780, 540));
        centralwidget = new QWidget(ArkMidnight);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setMinimumSize(QSize(780, 540));
        centralwidget->setMaximumSize(QSize(780, 540));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 780, 540));
        label->setMinimumSize(QSize(780, 540));
        label->setMaximumSize(QSize(780, 540));
        label->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/image/main.jpg")));
        btn_guide = new QPushButton(centralwidget);
        btn_guide->setObjectName("btn_guide");
        btn_guide->setGeometry(QRect(200, 390, 111, 31));
        QFont font;
        font.setFamilies({QString::fromUtf8("Times New Roman")});
        font.setPointSize(16);
        font.setBold(true);
        btn_guide->setFont(font);
        btn_start = new QPushButton(centralwidget);
        btn_start->setObjectName("btn_start");
        btn_start->setGeometry(QRect(470, 390, 111, 31));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Times New Roman")});
        font1.setPointSize(16);
        font1.setBold(true);
        font1.setUnderline(false);
        font1.setStrikeOut(false);
        btn_start->setFont(font1);
        ArkMidnight->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(ArkMidnight);
        statusbar->setObjectName("statusbar");
        ArkMidnight->setStatusBar(statusbar);

        retranslateUi(ArkMidnight);

        QMetaObject::connectSlotsByName(ArkMidnight);
    } // setupUi

    void retranslateUi(QMainWindow *ArkMidnight)
    {
        ArkMidnight->setWindowTitle(QCoreApplication::translate("ArkMidnight", "ArkMidnight", nullptr));
        label->setText(QString());
        btn_guide->setText(QCoreApplication::translate("ArkMidnight", "GUIDE", nullptr));
        btn_start->setText(QCoreApplication::translate("ArkMidnight", "START", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ArkMidnight: public Ui_ArkMidnight {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ARKMIDNIGHT_H
