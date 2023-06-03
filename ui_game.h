/********************************************************************************
** Form generated from reading UI file 'game.ui'
**
** Created by: Qt User Interface Compiler version 6.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAME_H
#define UI_GAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_game
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;

    void setupUi(QWidget *game)
    {
        if (game->objectName().isEmpty())
            game->setObjectName("game");
        game->resize(780, 600);
        game->setMinimumSize(QSize(780, 600));
        game->setMaximumSize(QSize(780, 600));
        label = new QLabel(game);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 780, 540));
        label->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/image/map.png")));
        label_2 = new QLabel(game);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(540, 540, 60, 60));
        QFont font;
        font.setFamilies({QString::fromUtf8("Times New Roman")});
        font.setPointSize(14);
        font.setBold(true);
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(game);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(500, 540, 60, 60));
        label_3->setFont(font);

        retranslateUi(game);

        QMetaObject::connectSlotsByName(game);
    } // setupUi

    void retranslateUi(QWidget *game)
    {
        game->setWindowTitle(QCoreApplication::translate("game", "Form", nullptr));
        label->setText(QString());
        label_2->setText(QCoreApplication::translate("game", "0", nullptr));
        label_3->setText(QCoreApplication::translate("game", "TIME:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class game: public Ui_game {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAME_H
