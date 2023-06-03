#include "game.h"
#include "ui_game.h"
#include <Qtimer>
#include "nextwave.h"

int game::value = 0;
int game::sec = 0;
int game::wave = 0;
bool game::ifWaveOver = true;

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
    game::value++;
    if (game::value / (1000 / timegap) > game::sec) ui->label_2->setText(QString::number(++game::sec));

    //if(value > 100)
    //    tim->stop();
}

void game::putOnWaveNumber(){
    ui->label_5->setText(QString::number(game::wave));
}

void game::on_pushButton_clicked()
{
    if (game::ifWaveOver){
        nextWave *w = new nextWave(0);
        connect(w,&nextWave::SignalInNextWave_WavePutOn,this,&game::putOnWaveNumber);
        int x = this->pos().x()+180;
        int y = this->pos().y();
        w->setWindowModality(Qt::ApplicationModal);
        w->setWindowTitle("确定吗？");
        w->move(x, y);
        w->show();
    }
    else{
        nextWave *w = new nextWave(2);
        connect(w,&nextWave::SignalInNextWave_WavePutOn,this,&game::putOnWaveNumber);
        int x = this->pos().x()+180;
        int y = this->pos().y();
        w->setWindowModality(Qt::ApplicationModal);
        w->setWindowTitle("你先别急！");
        w->move(x, y);
        w->show();
    }
}


