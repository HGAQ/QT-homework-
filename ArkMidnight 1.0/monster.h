#ifndef MONSTER_H
#define MONSTER_H

#include <QLabel>
#include <QMovie>
#include <QTimer>

struct index{int x;int y;
    index(int a,int b):x(a),y(b){};
    index(){};
};

class Monster : public QLabel
{
    Q_OBJECT
public:
    Monster(class game* parent=nullptr, int hp_=0, int spd=0, int x=0, int y=0);
    //基本参数
    int speed;
    int speedRemain = 0;
    int kind;

    //血量
    int sum_hp;
    int now_hp;

    //所属波次
    int wave;

    //击杀奖励
    int diamond;

    //所属游戏关卡
    QWidget* game;

    //位置
    int x_label;
    int y_label;
    int x_position;
    int y_position;
    int x_end;
    int y_end;

    //所在位置下一个目的地的坐标在path中的索引
    int pathIndex;

    //贴图
    QImage monster_img;
    QPixmap monster_pixmap;

    //路径
    index path[100];
    int len;

    //到达终点判断
    bool reachEnd(int x, int y);
    virtual void forward();

    //加东西后，调整下一个目标
    virtual void adjust();

    //展示血条
    void showHp();
};


class Basic_Monster :public Monster{
public:
    Basic_Monster(class game* parent=nullptr, int hp_ = 0, int spd = 0, int x=0,int y=5);
};

class Basic_Monster01 :public Basic_Monster{
public:
    Basic_Monster01(class game* parent=nullptr, int hp_ = 0, int spd = 0, int x=0,int y=5);
};

class Basic_Monster02 :public Basic_Monster{
public:
    Basic_Monster02(class game* parent=nullptr, int hp_ = 0, int spd = 0, int x=0,int y=5);
};


class Basic_Monster03 :public Basic_Monster{
public:
    Basic_Monster03(class game* parent=nullptr, int hp_ = 0, int spd = 0, int x=0,int y=5);
};


class Basic_Monster04 :public Basic_Monster{
public:
    Basic_Monster04(class game* parent=nullptr, int hp_ = 0, int spd = 0, int x=0,int y=5);
};


class Bomb_Monster :public Monster{
public:
    Bomb_Monster(class game* parent=nullptr, int hp_ = 0, int spd = 0, int x=0,int y=5);

};

class Bomb_Monster01 :public Bomb_Monster{
public:
    Bomb_Monster01(class game* parent=nullptr, int hp_ = 0, int spd = 0, int x=0,int y=5);
};

class Bomb_Monster02 :public Bomb_Monster{
public:
    Bomb_Monster02(class game* parent=nullptr, int hp_ = 0, int spd = 0, int x=0,int y=5);
};


class Flying_Monster :public Monster{
public:
    Flying_Monster(class game* parent=nullptr, int hp_ = 0, int spd = 0, int x=0,int y=0);
    virtual void forward();
};


class Flying_Monster01 :public Flying_Monster{
public:
    Flying_Monster01(class game* parent=nullptr, int hp_ = 0, int spd = 0, int x=0,int y=5);
};

class Flying_Monster02 :public Flying_Monster{
public:
    Flying_Monster02(class game* parent=nullptr, int hp_ = 0, int spd = 0, int x=0,int y=5);
};

class Flying_Monster03 :public Flying_Monster{
public:
    Flying_Monster03(class game* parent=nullptr, int hp_ = 0, int spd = 0, int x=0,int y=5);
};


class Heal_Monster :public Monster{
public:
    //自愈怪
    int to_heal = 1;
    int heal = 0; // 治疗量
    int heal_speed = 100;
    Heal_Monster(class game* parent=nullptr, int hp_ = 0, int spd = 0, int x=0,int y=0);
};

class Heal_Monster01 :public Heal_Monster{
public:
    Heal_Monster01(class game* parent=nullptr, int hp_ = 0, int spd = 0, int x=0,int y=5);
};

class Heal_Monster02 :public Heal_Monster{
public:
    Heal_Monster02(class game* parent=nullptr, int hp_ = 0, int spd = 0, int x=0,int y=5);
};

class Boss_Monster01: public Heal_Monster{
public:
    Boss_Monster01(class game* parent=nullptr, int hp_ = 0, int spd = 0, int x=0,int y=5);
};

class Boss_Monster02:public Monster{
public:
    //爆破怪
    int to_bomb = 1;
    int bomb_speed = 1000;
    Boss_Monster02(class game* parent=nullptr, int hp_ = 0, int spd = 0, int x=0,int y=5);
};

class Boss_Monster03: public Flying_Monster{
public:
    Boss_Monster03(class game* parent=nullptr, int hp_ = 0, int spd = 0, int x=0,int y=5);
};


#endif // MONSTER_H
