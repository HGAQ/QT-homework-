#include "guide1.h"
#include "ui_guide1.h"
#include "arkmidnight.h"
#include <QDebug>

guide1::guide1(QWidget *parent) :QWidget(parent), ui(new Ui::guide1)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/setting/image/icon.png"));
    ui->stackedWidget->setCurrentIndex(0);
    setAttribute(Qt::WA_DeleteOnClose);
}

guide1::~guide1()
{
    delete ui;
}

void guide1::on_btn_quit_2_clicked()
{
    emit SignalInGuide_openArkMidnight();
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
    emit SignalInGuide_openArkMidnight();
    this->close();
}


void guide1::on_btn_last_to_guide2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);//根据按下的button按索引显示相应的页面
}


void guide1::on_btn_quit_1_clicked()
{
    emit SignalInGuide_openArkMidnight();
    this->close();
}

