#include "nextwave.h"
#include "ui_nextwave.h"
#include "game.h"
#include "attentions.h"
#include <stdio.h>
#include <windows.h>
#include <QDebug>
#include <qtimer.h>
#include <iostream>

nextWave::nextWave(int _n, class game *parent) :
    QWidget(NULL),
    game(parent),
    ui(new Ui::nextWave)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/setting/image/icon.png"));
    ui->stackedWidget->setCurrentIndex(_n);//根据按下的button按索引显示相应的页面
    setAttribute(Qt::WA_DeleteOnClose);
}

nextWave::~nextWave()
{
    delete ui;
}

void nextWave::on_pushButton_clicked()
{
    //std::cout << 123 << std::endl;
    game->wave++;
    //double time=350;
    //std::cout << 123 << std::endl;

    emit SignalInNextWave_WavePutOn();
    emit SignalInNextWave_TimC();
    game->ifWaveOver = false;
    //ui->label_2->setText(QString::asprintf("第%d波要开始了！[○･｀Д´･ ○]", game->wave));

    attentions* p_att = new attentions(game,QString::asprintf("第%d波要开始了！", game->wave),Qt::white,0,0,2);//回合开始条幅
    p_att->show(); //回合结束，显示文字
    this->deleteLater();

    //QTimer* timer = new QTimer(this);
    //timer->start(time);//时间200tick
    //connect(timer, SIGNAL(timeout()), this, SLOT(onTimeupDestroy()));
    //ui->stackedWidget->setCurrentIndex(1);//根据按下的button按索引显示相应的页面
}

void nextWave::onTimeupDestroy(){
    this->close();
}

void nextWave::on_pushButton_3_clicked()
{
    emit SignalInNextWave_TimC();
    this->close();
}


void nextWave::on_pushButton_2_clicked()
{
    emit SignalInNextWave_TimC();
    this->close();
}

void nextWave::on_pushButton_4_clicked()
{
    emit SignalInNextWave_Close2();
    this->close();
}


void nextWave::on_pushButton_5_clicked()
{
    emit SignalInNextWave_Close();
    this->close();
}


void nextWave::on_pushButton_6_clicked()
{
    emit SignalInNextWave_Close2();
    this->close();
}

