#include "attentions.h"
#include <QPainter>
#include <cstring>
#include <iostream>

attentions::attentions(QWidget* parent,QString str,Qt::GlobalColor color,int _x, int _y,int type):QLabel(parent),information(str),x(_x),y(_y-30)
{
    if (type == 0 || type == 1 || type == 3){ //type3是横条文字
        time=100;
        this->setText(information);
        QPalette pe;
        pe.setColor(QPalette::WindowText, color);
        this->setPalette(pe);
        QFont ft;
        if(type==1){
            ft=QFont("Microsoft YaHei", 9, QFont::Bold);
            this->resize(60,60);
        }
        else if(type==0){
            ft=QFont("Microsoft YaHei", 9, QFont::Bold);
            this->resize(60,60);
        }
        else if(type==3){
            ft=QFont("Microsoft YaHei", 20, QFont::Bold);
            time=200;
            this->resize(720,90);
        }

        this->setFont(ft);
        this->raise();

        this->setAlignment(Qt::AlignCenter);
        this->move(x, y);

        QTimer* timer = new QTimer(this);
        timer->start(time);//时间0.2s
        if(type==1){
            connect(timer, SIGNAL(timeout()), this, SLOT(onTimeupDestroy()));
        }
        else if(type==0){
            connect(timer, SIGNAL(timeout()), this, SLOT(onTimeupDestroy_2()));
        }
    }
    else if (type == 2){//type2是横条
        this->resize(720,90);
        this->move(0, 45);
        this->setScaledContents(true);
        this->setAlignment(Qt::AlignCenter);
        QTimer* timer = new QTimer(this);
        timer->start(time);//时间0.2s
        connect(timer, SIGNAL(timeout()), this, SLOT(onTimeupDestroy_3()));
        this->raise();
    }
}

void attentions::onTimeupDestroy(){
    num++;
    if (num == 1) this->move(x-4, y);
    else if (num == 2) this->move(x+4, y);
    else if (num == 3) this->move(x, y);
    else if (num == 20) this->close();
}

void attentions::onTimeupDestroy_2(){
    num++;
    if (num > 1 && num<7) {
        this->move(x, y-4);
        y-=4;
    }
    else if (num == 10) this->close();
}

void attentions::onTimeupDestroy_3(){
    num++;
    QPainter p;
    QImage image(":/setting/image/bar.png");
    if (num < 200){//变不透明
        p.begin(&image);
        p.setCompositionMode(QPainter::CompositionMode_DestinationIn);
        p.fillRect(image.rect(), QColor(0, 0, 0, num));
        p.end();
        this->setPixmap(QPixmap::fromImage(image));
        this->raise();
    }
    else if(num >= 400 && num <= 600){//变透明
        if (p_att2){delete p_att2; p_att2=NULL;}
        p.begin(&image);
        p.setCompositionMode(QPainter::CompositionMode_DestinationIn);
        p.fillRect(image.rect(), QColor(0, 0, 0, (600-num)));
        p.end();
        this->setPixmap(QPixmap::fromImage(image));
        this->raise();
    }
    if (num == 200){//显示文字
        //std::cout<<123<<std::endl;
        p_att2 = new attentions(this,information,Qt::white,0,30,3);
        p_att2->show();
        p_att2->raise();;
        this->raise();
    }
    this->show();

}
