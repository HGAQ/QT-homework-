#include "arkmidnight.h"
#include "ui_arkmidnight.h"
#include "guide1.h"
#include "game.h"

ArkMidnight::ArkMidnight(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ArkMidnight)
{
    ui->setupUi(this);
    this->setWindowTitle("ArkMidnight");

}

ArkMidnight::~ArkMidnight()
{
    delete ui;
}


// 这是跳转到指导界面
void ArkMidnight::on_btn_guide_clicked()
{
    QWidget *w = new guide1();
    int x = this->pos().x();
    int y = this->pos().y();
    w->move(x, y);
    w->show();
    this->close ();
}

// 这是跳转到游戏界面
void ArkMidnight::on_btn_start_clicked()
{
    QWidget *w = new game();

    int x = this->pos().x();
    int y = this->pos().y();
    w->move(x, y);
    w->show();
    this->close ();
}

