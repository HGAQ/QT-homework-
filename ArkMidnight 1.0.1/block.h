#ifndef BLOCK_H
#define BLOCK_H
#include "qlabel.h"
#include "QObject"


class block: public QLabel
{
    Q_OBJECT;
public:
    int x_index, y_index; //这个板块的x与y
    int x_position, y_position; //这个板块的xy坐标
    int block_type;//种类，0:路，1:墙，2:起点，3:终点,……
    bool can_destroy;//可以被摧毁
    bool can_attack=0;//可以射

    int protect = 0;//被保护的个数
    int enhance_speed = 0;
    int enhance_atk = 0;

    bool can_through;//可以被穿过
    bool is_start;
    bool is_end;
    int atk;//用于激光塔
    QImage block_img;
    QPixmap block_pixmap;
    static const int cost = 0;
    int to_shoot = -1;//距离shoot还有多少tick？-1不能射
    int shoot_speed = -1; //射击间隔
    int shoot_range=-1; //攻击范围
    void showProtected();
    explicit block(QWidget *parent = nullptr, int x = 0,int y = 0);
};

class road: public block{
public:
    static const int cost = -1;
    explicit road(QWidget *parent = nullptr, int x = 0,int y = 0);
};

class wall: public block{
public:
    static const int cost = 30;
    explicit wall(QWidget *parent = nullptr, int x = 0,int y = 0);
};

class start: public block{
public:
    static const int cost = -1;
    explicit start(QWidget *parent = nullptr, int x = 0,int y = 0);
};

class end: public block{
public:
    static const int cost = -1;
    explicit end(QWidget *parent = nullptr, int x = 0,int y = 0);
};

class arrow: public block{
public:
    static const int cost = 200;
    explicit arrow(QWidget *parent = nullptr, int x = 0,int y = 0);
};

class laser: public block{
public:
    static const int cost = 350;
    explicit laser(QWidget *parent = nullptr, int x = 0,int y = 0);
};

class shield: public block{
public:
    static const int cost = 100;
    explicit shield(QWidget *parent = nullptr, int x = 0,int y = 0);
};

class attack: public block{
public:
    static const int cost = 100;
    explicit attack(QWidget *parent = nullptr, int x = 0,int y = 0);
};

class speed: public block{
public:
    static const int cost = 100;
    explicit speed(QWidget *parent = nullptr, int x = 0,int y = 0);
};

class heal: public block{
public:
    static const int cost = -1;
    explicit heal(QWidget *parent = nullptr, int x = 0,int y = 0);
};
#endif // BLOCK_H
