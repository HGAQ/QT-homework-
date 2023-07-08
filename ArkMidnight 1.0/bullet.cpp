#include "bullet.h"
#include "game.h"
#include "Qtimer"
#include "qpainter.h"


bullet::bullet(class game* parent)
    : QLabel{parent}
{
}

/*bool bullet::bullet_attack(){
    return 0;
}*/

arrow_bullet::arrow_bullet(class game *parent,block* shoot,int s_x,int s_y,int e_x,int e_y)
    : bullet(parent)
{
    time=750;
    atk = ceil(shoot->atk * pow(3, shoot->enhance_atk)); // 由箭塔攻击力决定，攻击力加增幅
    start_x=s_x;
    start_y=s_y;
    target_x=e_x;
    target_y=e_y;
    int distance=(e_x-s_x)*(e_x-s_x)+(e_y-s_y)*(e_y-s_y);
    moving_x=(e_x - s_x) * 10 / std::sqrt(distance);
    moving_y=(e_y - s_y) * 10 / std::sqrt(distance);

    shooter = shoot;
    range=200;
    bullet_img.load(":/bullet/image/arrowb.png");
    QTimer* timer = new QTimer(this);
    timer->start(time);//时间0.75s
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimeupDestroy()));
}

laser_bullet::laser_bullet(class game *parent,block* shoot,int s_x,int s_y,int e_x,int e_y)
    : bullet(parent)
{
    time=150;
    start_x=s_x;
    start_y=s_y;
    target_x=e_x;
    target_y=e_y;
    //int distance=(e_x-s_x)*(e_x-s_x)+(e_y-s_y)*(e_y-s_y);
    int top = std::min(s_y,e_y);
    int left = std::min(s_x,e_x);
    int length = std::max(abs(e_x-s_x),3);
    int width = std::max(abs(e_y-s_y),3);

    this->setGeometry(QRect(left,top,length,width));
    bullet_pixmap = QPixmap(length,width);
    bullet_pixmap.fill(QColor(0, 0, 0, 0));
    QPainter painter(&bullet_pixmap);
    painter.setPen(QPen(Qt::red, 5));
    if((s_x>e_x&&s_y>e_y)||(s_x<e_x&&s_y<e_y)){
        painter.drawLine(QPoint(0,0),QPoint(length,width));
    }
    else{
        painter.drawLine(QPoint(0,width),QPoint(length,0));
    }

    //painter.drawLine(QPoint(s_x-left,s_y-top),QPoint(e_x-left,e_x-top));
    shooter = shoot;
    QTimer* timer = new QTimer(this);
    timer->start(time);//时间0.15s
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimeupDestroy()));
}



void bullet::onTimeupDestroy(){
    this->close();
}











/*bool arrow_bullet::bullet_attack(){
    for(Monster* curr_mob: parent->mob_on_field){

    }
    if(){

    }

}*/
