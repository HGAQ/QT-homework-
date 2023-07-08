#ifndef BULLET_H
#define BULLET_H

#include <QWidget>
#include <QLabel>
#include <block.h>
#include <math.h>

class bullet : public QLabel
{
    Q_OBJECT
public:
    explicit bullet(class game* parent);
    int time;
    int start_x;
    int start_y;
    int target_x;
    int target_y;
    double moving_x;
    double moving_y;
    int atk;
    QImage bullet_img;
    QPixmap bullet_pixmap;
    block* shooter;
    //range是起点与敌人的距离的平方最小值
    int range;
    //虚函数，检测是否到达敌人附近；
    //virtual bool bullet_attack();
private slots:
    void onTimeupDestroy();
};




class laser_bullet: public bullet{
public:
    explicit laser_bullet(class game* parent, block *shooter=nullptr, int s_x = 0,int s_y = 0,int e_x = 0,int e_y = 0);
};






class arrow_bullet: public bullet{
public:
    //bool bullet_attack();
    explicit arrow_bullet(class game* parent, block *shooter=nullptr, int s_x = 0,int s_y = 0,int e_x = 0,int e_y = 0);
};



#endif // BULLET_H
