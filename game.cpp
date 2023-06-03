#include "game.h"
#include "ui_game.h"
#include <Qtimer>
#include <vector>

game::game(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::game)
{
    ui->setupUi(this);
    this->setWindowTitle("game");
    tim = new QTimer();
    tim->setInterval(1000);
    connect(tim,SIGNAL(timeout()),this,SLOT(onTimeOut()));
    tim->start();
    std::vector<std::vector<int>> Mymap = {
                        {0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
                        {0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0},
                        {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0},
                        {0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 3},
                        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0},
                        {2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
                        {0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0},
                        {0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0},
                        {0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0},
    };
    for(auto line : Mymap)
    {
        for(auto position: line)
        {

        }
    }




}

game::~game()
{
    delete ui;
}

void game::onTimeOut()
{
    static int value = 0;
    ui->label_2->setText(QString::number(value++));

    if(value > 100)
        tim->stop();
}
