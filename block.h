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
    bool can_through;//可以被穿过
    bool is_start;
    bool is_end;
    QImage block_img;
    explicit block(QWidget *parent = nullptr, int x = 0,int y = 0);
};

class road: public block{
public:
    explicit road(QWidget *parent = nullptr, int x = 0,int y = 0);
};

class wall: public block{
public:
    explicit wall(QWidget *parent = nullptr, int x = 0,int y = 0);
};

class start: public block{
public:
    explicit start(QWidget *parent = nullptr, int x = 0,int y = 0);
};

class end: public block{
public:
    explicit end(QWidget *parent = nullptr, int x = 0,int y = 0);
};

#endif // BLOCK_H
