#include "block.h"
#include <QDebug>

block::block(QWidget*parent, int x ,int y)
    :QLabel(parent)
{
    x_index = x;
    y_index = y;
    x_position = x * 60;
    y_position = y * 60;

}

road::road(QWidget*parent, int x ,int y):block(parent, x , y){
    can_destroy=0;
    protect=1;
    can_through=1;
    is_start=0;
    is_end=0;
    block_type=0;
    block_img.load(":/tower/image/empty.png");
    block_pixmap=QPixmap::fromImage(block_img);
}

wall::wall(QWidget*parent, int x ,int y):block(parent, x , y){
    can_destroy=1;
    can_through=0;
    is_start=0;
    is_end=0;
    block_type=1;
    block_img.load(":/tower/image/wall.png");
    block_pixmap=QPixmap::fromImage(block_img);
}

start::start(QWidget*parent, int x ,int y):block(parent, x , y){
    can_destroy=0;
    protect=1;
    can_through=0;
    is_start=1;
    is_end=0;
    block_type=2;
    block_img.load(":/tower/image/start.png");
    block_pixmap=QPixmap::fromImage(block_img);
}

end::end(QWidget*parent, int x ,int y):block(parent, x , y){
    can_destroy=0;
    protect=1;
    can_through=1;
    is_start=0;
    is_end=1;
    block_type=3;
    block_img.load(":/tower/image/end.png");
    block_pixmap=QPixmap::fromImage(block_img);
}

arrow::arrow(QWidget*parent, int x ,int y):block(parent, x , y){
    can_destroy=1;
    can_through=0;
    is_start=0;
    is_end=0;
    block_type=4;
    block_img.load(":/tower/image/arrow.png");
    block_pixmap=QPixmap::fromImage(block_img);
    to_shoot = 1;
    shoot_speed=20;
    shoot_range=120;
    atk = 2;
    can_attack = 1;
}

laser::laser(QWidget*parent, int x ,int y):block(parent, x , y){
    can_destroy=1;
    can_through=0;
    is_start=0;
    is_end=0;
    block_type=5;
    block_img.load(":/tower/image/laser.png");
    block_pixmap=QPixmap::fromImage(block_img);
    to_shoot = 1;
    shoot_speed = 50;
    shoot_range = 130;
    atk = 2;
    can_attack = 1;
}

shield::shield(QWidget*parent, int x ,int y):block(parent, x , y){
    can_destroy=1;
    protect=1;
    can_through=0;
    is_start=0;
    is_end=0;
    block_type=6;
    block_img.load(":/tower/image/shield.png");
    block_pixmap=QPixmap::fromImage(block_img);
    to_shoot = 1;
}

attack::attack(QWidget*parent, int x ,int y):block(parent, x , y){
    can_destroy=1;
    can_through=0;
    is_start=0;
    is_end=0;
    block_type=7;
    block_img.load(":/tower/image/attack.png");
    block_pixmap=QPixmap::fromImage(block_img);
    to_shoot = 1;
    shoot_speed=20;
    shoot_range=120;
}


speed::speed(QWidget*parent, int x ,int y):block(parent, x , y){
    can_destroy=1;
    can_through=0;
    is_start=0;
    is_end=0;
    block_type=8;
    block_img.load(":/tower/image/speed.png");
    block_pixmap=QPixmap::fromImage(block_img);
    to_shoot = 1;
    shoot_speed=20;
    shoot_range=120;

}

heal::heal(QWidget*parent, int x ,int y):block(parent, x , y){
    can_destroy=0;
    can_through=0;
    protect=1;
    is_start=0;
    is_end=0;
    block_type=9;
    block_img.load(":/tower/image/heal.png");
    block_pixmap=QPixmap::fromImage(block_img);
    to_shoot = 1;
    shoot_speed=40;
    shoot_range=120;
    atk = 10;//对于这个塔是治愈力
}
/*
void block::showProtected(){
    QPainter protection(&block_img);
    qreal barWidth = 60.0;

    qreal backgroundLeft = 0;
    qreal backgroundRight = barWidth;
    qreal backgroundBottom = 60;

    qreal bloodLeft = 0;
    qreal bloodRight = barWidth * (static_cast<qreal>(now_hp) / static_cast<qreal>(sum_hp));
    qreal bloodBottom = 60;
    healthbar.setRenderHint(QPainter::Antialiasing);
    healthbar.setPen(QPen(Qt::gray, 5));
    healthbar.drawLine(QLineF(backgroundLeft, backgroundBottom, backgroundRight, backgroundBottom));
    healthbar.setPen(QPen(Qt::red, 5));
    healthbar.drawLine(QLineF(bloodLeft, bloodBottom, bloodRight, bloodBottom));
    //healthbar.drawText(0,60,"黄河之水天上来");
    std::cout<<"hp:"<<(1.0*now_hp)/(1.0*sum_hp)<<"\n";
}*/
