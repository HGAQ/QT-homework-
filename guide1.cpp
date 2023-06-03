#include "guide1.h"
#include "ui_guide1.h"
#include "arkmidnight.h"

guide1::guide1(QWidget *parent) :QWidget(parent), ui(new Ui::guide1)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
}

guide1::~guide1()
{
    delete ui;
}

void guide1::on_btn_quit_2_clicked()
{
    QWidget *w = new ArkMidnight();

    int x = this->pos().x();
    int y = this->pos().y();
    w->move(x, y);
    w->show();
    this->close();
}


void guide1::on_btn_last_to_guide1_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);//根据按下的button按索引显示相应的页面
}


void guide1::on_btn_next_to_guide3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);//根据按下的button按索引显示相应的页面
}


void guide1::on_btn_next_to_guide2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);//根据按下的button按索引显示相应的页面
}


void guide1::on_btn_quit_3_clicked()
{
    QWidget *w = new ArkMidnight();

    int x = this->pos().x();
    int y = this->pos().y();
    w->move(x, y);
    w->show();
    this->close();
}


void guide1::on_btn_last_to_guide2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);//根据按下的button按索引显示相应的页面
}


void guide1::on_btn_quit_1_clicked()
{
    QWidget *w = new ArkMidnight();

    int x = this->pos().x();
    int y = this->pos().y();
    w->move(x, y);
    w->show();
    this->close();
}

