#include "game.h"
#include "ui_game.h"
#include "block.h"
#include <Qtimer>
#include <vector>

game::game(QWidget *parent):QWidget(parent),ui(new Ui::game)
{
    ui->setupUi(this);
    board_height=9;
    board_width=12;
    this->setWindowTitle("game");
    tim = new QTimer();
    tim->setInterval(1000);
    connect(tim,SIGNAL(timeout()),this,SLOT(onTimeOut()));
    tim->start();
    Mymap = {
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
    Myblocks = new block**[board_height];
    for(int y_index = 0; y_index < board_height; y_index++){
            Myblocks[y_index]=new block*[board_width];
    }

    for(int x_index = 0; x_index < board_width; x_index++)
    {
        for(int y_index = 0; y_index < board_height; y_index++)
        {
            switch(Mymap[y_index][x_index]){
            case 0:
                Myblocks[y_index][x_index]=new road(this,x_index,y_index);
                break;
            case 1:
                Myblocks[y_index][x_index]=new wall(this,x_index,y_index);
                break;
            case 2:
                Myblocks[y_index][x_index]=new start(this,x_index,y_index);
                break;
            case 3:
                Myblocks[y_index][x_index]=new end(this,x_index,y_index);
                break;
            }
            Myblocks[y_index][x_index]->move(Myblocks[y_index][x_index]->x_position,Myblocks[y_index][x_index]->y_position);
            Myblocks[y_index][x_index]->setFixedSize(60,60);
            Myblocks[y_index][x_index]->setPixmap(QPixmap::fromImage(Myblocks[y_index][x_index]->block_img));
            Myblocks[y_index][x_index]->raise();
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
