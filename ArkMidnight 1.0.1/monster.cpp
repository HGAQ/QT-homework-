#include "monster.h"
#include <QDebug>
#include <iostream>
#include "game.h"
#include <qpainter.h>
#include <cmath>

Monster::Monster(class game* parent, int hp_, int spd, int x,int y):QLabel(parent){
    sum_hp = hp_;
    now_hp = hp_;
    speed = spd;
    x_label=x;
    x_position=x*60;
    y_label=y;
    y_position=y*60;
    x_end=parent->end_x;
    y_end=parent->end_y;
    game = parent;
    parent->getPath(path, len, x, y);
    this->move(x_position, y_position);
    pathIndex = 1;
}


Basic_Monster::Basic_Monster(class game* parent, int hp_, int spd, int x,int y):Monster(parent,  hp_, spd, x, y){
    kind = 0;
}

Basic_Monster01::Basic_Monster01(class game* parent, int hp_, int spd, int x,int y)
    :Basic_Monster(parent, hp_ , spd ,x,y){
    monster_img.load(":/monster/image/monsters/mob_normal01.png");
    monster_pixmap=QPixmap::fromImage(monster_img);
    kind = 0;
    diamond = 45;
}

Basic_Monster02::Basic_Monster02(class game* parent, int hp_, int spd, int x,int y)
    :Basic_Monster(parent, hp_ , spd ,x,y){
    monster_img.load(":/monster/image/monsters/mob_normal02.png");
    monster_pixmap=QPixmap::fromImage(monster_img);
    kind = 0;
    diamond = 50;
}
Basic_Monster03::Basic_Monster03(class game* parent, int hp_, int spd, int x,int y)
    :Basic_Monster(parent, hp_ , spd ,x,y){
    monster_img.load(":/monster/image/monsters/mob_fast01.png");
    monster_pixmap=QPixmap::fromImage(monster_img);
    kind = 0;
    diamond = 45;
}

Basic_Monster04::Basic_Monster04(class game* parent, int hp_, int spd, int x,int y)
    :Basic_Monster(parent, hp_ , spd ,x,y){
    monster_img.load(":/monster/image/monsters/mob_fast02.png");
    monster_pixmap=QPixmap::fromImage(monster_img);
    kind = 0;
    diamond = 50;
}

Bomb_Monster::Bomb_Monster(class game* parent, int hp_, int spd, int x,int y):Monster(parent,  hp_, spd, x, y){
    kind = 1;
}

Bomb_Monster01::Bomb_Monster01(class game* parent, int hp_, int spd, int x,int y)
    :Bomb_Monster(parent, hp_ , spd ,x,y){
    monster_img.load(":/monster/image/monsters/mob_explode01.png");
    monster_pixmap=QPixmap::fromImage(monster_img);
    kind = 1;
    diamond = 55;
}

Bomb_Monster02::Bomb_Monster02(class game* parent, int hp_, int spd, int x,int y)
    :Bomb_Monster(parent, hp_ , spd ,x,y){
    monster_img.load(":/monster/image/monsters/mob_explode02.png");
    monster_pixmap=QPixmap::fromImage(monster_img);
    kind = 1;
    diamond = 60;
}

Flying_Monster::Flying_Monster(class game* parent, int hp_, int spd, int x,int y):Monster(parent,  hp_, spd, x, y){
    path[0] = index(parent->start_x, parent->start_y);
    path[1] = index(parent->end_x, parent->end_y);
    kind = 2;
}

Flying_Monster01::Flying_Monster01(class game* parent, int hp_, int spd, int x,int y)
    :Flying_Monster(parent, hp_ , spd ,x,y){
    monster_img.load(":/monster/image/monsters/mob_fly01.png");
    monster_pixmap=QPixmap::fromImage(monster_img);
    kind = 2;
    diamond = 35;
}

Flying_Monster02::Flying_Monster02(class game* parent, int hp_, int spd, int x,int y)
    :Flying_Monster(parent, hp_ , spd ,x,y){
    monster_img.load(":/monster/image/monsters/mob_fly02.png");
    monster_pixmap=QPixmap::fromImage(monster_img);
    kind = 2;
    diamond = 40;
}

Flying_Monster03::Flying_Monster03(class game* parent, int hp_, int spd, int x,int y)
    :Flying_Monster(parent, hp_ , spd ,x,y){
    monster_img.load(":/monster/image/monsters/mob_fly03.png");
    monster_pixmap=QPixmap::fromImage(monster_img);
    kind = 2;
    diamond = 200;
}

Heal_Monster::Heal_Monster(class game* parent, int hp_, int spd, int x,int y):Monster(parent,  hp_, spd, x, y){
    kind = 3;
}

Heal_Monster01::Heal_Monster01(class game* parent, int hp_, int spd, int x,int y)
    :Heal_Monster(parent, hp_ , spd ,x,y){
    heal = 2;
    heal_speed = 50;
    monster_img.load(":/monster/image/monsters/mob_heal01.png");
    monster_pixmap=QPixmap::fromImage(monster_img);
    kind = 3;
    diamond = 70;
}

Heal_Monster02::Heal_Monster02(class game* parent, int hp_, int spd, int x,int y)
    :Heal_Monster(parent, hp_ , spd ,x,y){
    heal = 4;
    heal_speed = 100;
    monster_img.load(":/monster/image/monsters/mob_heal02.png");
    monster_pixmap=QPixmap::fromImage(monster_img);
    kind = 3;
    diamond = 75;
}

Boss_Monster01::Boss_Monster01(class game* parent, int hp_, int spd, int x,int y)
    :Heal_Monster(parent, hp_ , spd ,x,y){
    heal = 40;
    heal_speed = 400;
    monster_img.load(":/monster/image/monsters/mob_sp04.png");
    monster_pixmap=QPixmap::fromImage(monster_img);
    kind = 3;
    diamond = 2000;
}


Boss_Monster02::Boss_Monster02(class game* parent, int hp_, int spd, int x,int y)
    :Monster(parent, hp_ , spd ,x,y){
    monster_img.load(":/monster/image/monsters/mob_sp03.png");
    monster_pixmap=QPixmap::fromImage(monster_img);
    kind = 4;
    diamond = 20000;
}

Boss_Monster03::Boss_Monster03(class game* parent, int hp_, int spd, int x,int y)
    :Flying_Monster(parent, hp_ , spd ,x,y){
    monster_img.load(":/monster/image/monsters/mob_sp05.png");
    monster_pixmap=QPixmap::fromImage(monster_img);
    kind = 2;
    diamond = 200;
}

bool Monster::reachEnd(int x, int y){
    if ((abs(x*60-x_position)<2) && (abs(y*60-y_position)<2)){
        return true;
    }
    return false;
}

void Monster::forward(){
    int next_x = path[pathIndex].x;
    int next_y = path[pathIndex].y;
    int delta_x = x_position - next_x*60;
    int delta_y = y_position - next_y*60;
    speedRemain += speed;
    int pix = speedRemain / 50;//计算可以移动的像素
    speedRemain %= 50;
    //std::cout<<next_x<<" "<<next_y<<" "<<pathIndex<<" "<<x_position<<" "<<y_position<<" ";
    while(pix > 0){//找到下一个位置
        if (reachEnd(x_end, y_end)){break;}//到达终点则退出
        if (delta_x == 0 && delta_y == 0){//达到转折点则找下一个点
            pathIndex += 1;
            next_x = path[pathIndex].x;
            next_y = path[pathIndex].y;
            delta_x = x_position - next_x*60;
            delta_y = y_position - next_y*60;
        }
        pix -= 1;
        if (abs(delta_x) > abs(delta_y)){
            if (delta_x > 0) {x_position = x_position-1;}
            else {x_position = x_position+1;}
            delta_x -= 1;
        }
        else{
            if (delta_y > 0) {y_position = y_position-1;}
            else {y_position = y_position+1;}
            delta_y -= 1;
        }
    }
    this->move(x_position, y_position);
    //std::cout << x_position << " " << y_position << std::endl;
}

void Monster::adjust(){
    int first_x = path[0].x;
    int first_y = path[0].y;
    int second_x = path[1].x;
    int second_y = path[1].y;
    int delta_x = abs(first_x-second_x);
    int delta_y = abs(first_y-second_y);
    if (delta_y == 0 &&
    ((first_x*60 < x_position && second_x*60 > x_position)||
    (first_x*60 > x_position && second_x*60 < x_position))){
        pathIndex = 1;
        }
    else if(delta_x == 0 &&
             ((first_y*60 < y_position && second_y*60 > y_position)||
              (first_y*60 > y_position && second_y*60 < y_position))){
        pathIndex = 1;
    }
    else {
        pathIndex = 0;
    }
}


void Flying_Monster::forward(){
    int now_x = path[pathIndex-1].x;
    int now_y = path[pathIndex-1].y;
    int next_x = path[pathIndex].x;
    int next_y = path[pathIndex].y;
    double delta_x = x_position - next_x*60;
    double delta_y = y_position - next_y*60;
    speedRemain += speed;
    int pix = speedRemain / 50;//计算可以移动的像素
    speedRemain %= 50;
    //std::cout<<next_x<<" "<<next_y<<" "<<pathIndex<<" "<<x_position<<" "<<y_position<<" ";
    while(pix > 0){//找到下一个位置
        if (reachEnd(x_end, y_end)){break;}//到达终点则退出
        if (delta_x == 0 && delta_y == 0){//达到转折点则找下一个点
            pathIndex += 1;
            next_x = path[pathIndex].x;
            next_y = path[pathIndex].y;
            delta_x = x_position - next_x*60;
            delta_y = y_position - next_y*60;
        }
        pix -= 1;
        if ((double)abs(delta_x)/(double)abs(now_x-next_x) > (double)abs(delta_y)/(double)abs(now_y-next_y)){
            if (delta_x > 0) {x_position = x_position-1;}
            else {x_position = x_position+1;}
            delta_x -= 1;
        }
        else{
            if (delta_y > 0) {y_position = y_position-1;}
            else {y_position = y_position+1;}
            delta_y -= 1;
        }
    }
    this->move(x_position, y_position);
    //std::cout << x_position << " " << y_position << std::endl;
}


void Monster::showHp(){
    QPainter healthbar(&monster_pixmap);
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
    //std::cout<<"hp:"<<(1.0*now_hp)/(1.0*sum_hp)<<"\n";
}
