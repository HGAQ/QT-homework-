#include "game.h"
#include "ui_game.h"
#include <Qtimer>

game::game(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::game)
{
    ui->setupUi(this);
    this->setWindowTitle("game");
    tim = new QTimer();
    tim->setInterval(timegap);

    connect(tim,SIGNAL(timeout()),this,SLOT(onTimeOut()));

    connect(tim,SIGNAL(timeout()),this,SLOT(waveInc()));
    tim->start();
}

game::~game()
{
    delete ui;
}

void game::onTimeOut()
{
    static int value = 0;
    static int sec = 0;
    value++;
    if (value / (1000 / timegap) > sec) ui->label_2->setText(QString::number(++sec));

    //if(value > 100)
    //    tim->stop();
}

void game::waveInc()
{

}
