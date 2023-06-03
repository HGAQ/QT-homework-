#include "nextwave.h"
#include "ui_nextwave.h"
#include <game.h>
#include <stdio.h>
#include <windows.h>

nextWave::nextWave(int _n, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::nextWave)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(_n);//根据按下的button按索引显示相应的页面
}

nextWave::~nextWave()
{
    delete ui;
}

void nextWave::on_pushButton_clicked()
{
    game::wave++;
    emit SignalInNextWave_WavePutOn();
    game::ifWaveOver = false;
    ui->label_2->setText(QString::asprintf("第%d波要开始了！[○･｀Д´･ ○]", game::wave));
    ui->stackedWidget->setCurrentIndex(1);//根据按下的button按索引显示相应的页面
}


void nextWave::on_pushButton_3_clicked()
{
    this->close();
}


void nextWave::on_pushButton_2_clicked()
{
    this->close();
}

void nextWave::on_pushButton_4_clicked()
{
    this->close();
}

