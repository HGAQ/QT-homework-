/********************************************************************************
** Form generated from reading UI file 'guide1.ui'
**
** Created by: Qt User Interface Compiler version 6.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUIDE1_H
#define UI_GUIDE1_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_guide1
{
public:
    QStackedWidget *stackedWidget;
    QWidget *page;
    QLabel *label;
    QPushButton *btn_quit_1;
    QPushButton *btn_next_to_guide2;
    QWidget *page_2;
    QPushButton *btn_next_to_guide3;
    QPushButton *btn_last_to_guide1;
    QPushButton *btn_quit_2;
    QLabel *label_2;
    QWidget *page_3;
    QLabel *label_3;
    QPushButton *btn_quit_3;
    QPushButton *btn_last_to_guide2;

    void setupUi(QWidget *guide1)
    {
        if (guide1->objectName().isEmpty())
            guide1->setObjectName("guide1");
        guide1->resize(777, 541);
        stackedWidget = new QStackedWidget(guide1);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(-30, 0, 830, 600));
        page = new QWidget();
        page->setObjectName("page");
        page->setMinimumSize(QSize(815, 564));
        page->setMaximumSize(QSize(815, 564));
        label = new QLabel(page);
        label->setObjectName("label");
        label->setGeometry(QRect(10, -10, 815, 564));
        label->setMinimumSize(QSize(815, 564));
        label->setMaximumSize(QSize(815, 564));
        label->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/image/guide1.jpg")));
        btn_quit_1 = new QPushButton(page);
        btn_quit_1->setObjectName("btn_quit_1");
        btn_quit_1->setGeometry(QRect(30, 510, 111, 31));
        QFont font;
        font.setFamilies({QString::fromUtf8("Times New Roman")});
        font.setPointSize(16);
        font.setBold(true);
        btn_quit_1->setFont(font);
        btn_next_to_guide2 = new QPushButton(page);
        btn_next_to_guide2->setObjectName("btn_next_to_guide2");
        btn_next_to_guide2->setGeometry(QRect(690, 510, 111, 31));
        btn_next_to_guide2->setFont(font);
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        btn_next_to_guide3 = new QPushButton(page_2);
        btn_next_to_guide3->setObjectName("btn_next_to_guide3");
        btn_next_to_guide3->setGeometry(QRect(690, 510, 111, 31));
        btn_next_to_guide3->setFont(font);
        btn_last_to_guide1 = new QPushButton(page_2);
        btn_last_to_guide1->setObjectName("btn_last_to_guide1");
        btn_last_to_guide1->setGeometry(QRect(690, 470, 111, 31));
        btn_last_to_guide1->setFont(font);
        btn_quit_2 = new QPushButton(page_2);
        btn_quit_2->setObjectName("btn_quit_2");
        btn_quit_2->setGeometry(QRect(30, 510, 111, 31));
        btn_quit_2->setFont(font);
        label_2 = new QLabel(page_2);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(30, -10, 815, 564));
        label_2->setMinimumSize(QSize(815, 564));
        label_2->setMaximumSize(QSize(815, 564));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/image/guide2.jpg")));
        stackedWidget->addWidget(page_2);
        label_2->raise();
        btn_next_to_guide3->raise();
        btn_quit_2->raise();
        btn_last_to_guide1->raise();
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        label_3 = new QLabel(page_3);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(30, -10, 815, 564));
        label_3->setMinimumSize(QSize(815, 564));
        label_3->setMaximumSize(QSize(815, 564));
        label_3->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/image/guide3.jpg")));
        btn_quit_3 = new QPushButton(page_3);
        btn_quit_3->setObjectName("btn_quit_3");
        btn_quit_3->setGeometry(QRect(30, 510, 111, 31));
        btn_quit_3->setFont(font);
        btn_last_to_guide2 = new QPushButton(page_3);
        btn_last_to_guide2->setObjectName("btn_last_to_guide2");
        btn_last_to_guide2->setGeometry(QRect(690, 470, 111, 31));
        btn_last_to_guide2->setFont(font);
        stackedWidget->addWidget(page_3);

        retranslateUi(guide1);

        QMetaObject::connectSlotsByName(guide1);
    } // setupUi

    void retranslateUi(QWidget *guide1)
    {
        guide1->setWindowTitle(QCoreApplication::translate("guide1", "Form", nullptr));
        label->setText(QString());
        btn_quit_1->setText(QCoreApplication::translate("guide1", "QUIT", nullptr));
        btn_next_to_guide2->setText(QCoreApplication::translate("guide1", "NEXT", nullptr));
        btn_next_to_guide3->setText(QCoreApplication::translate("guide1", "NEXT", nullptr));
        btn_last_to_guide1->setText(QCoreApplication::translate("guide1", "LAST", nullptr));
        btn_quit_2->setText(QCoreApplication::translate("guide1", "QUIT", nullptr));
        label_2->setText(QString());
        label_3->setText(QString());
        btn_quit_3->setText(QCoreApplication::translate("guide1", "QUIT", nullptr));
        btn_last_to_guide2->setText(QCoreApplication::translate("guide1", "LAST", nullptr));
    } // retranslateUi

};

namespace Ui {
    class guide1: public Ui_guide1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUIDE1_H
