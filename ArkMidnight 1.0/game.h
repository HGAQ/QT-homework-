#ifndef GAME_H
#define GAME_H
#include <Qtimer>
#include <QWidget>
#include <QMouseEvent>
#include <vector>
#include "block.h"
#include "choice.h"
#include "monster.h"
#include <nextwave.h>
#include <bullet.h>

#define timegap 20

namespace Ui {
class game;
}

class game : public QWidget
{
    Q_OBJECT

public:
    //基本参数
    int board_width;
    int board_height;
    class ArkMidnight *parent;
    int game_state = 0; //0为未结束，1为胜利，2为失败


    //场上的塔分布
    std::vector<std::vector<int>> Mymap;
    std::vector<int> shop;
    std::vector<choice*> choices;
    block*** Myblocks;

    //

    friend nextWave;
    friend QMouseEvent;
    friend Monster;
    friend nextWave;
    void putOnWaveNumber();
    void heartShow();
    void continueTim();
    void inCal();


    //塔的建造
    int build_and_destory;
    void mousePressEvent(QMouseEvent *event);
    bool inBoard(int x,int y);
    bool inShop(int x,int y);
    int cost[8] = {0}; /* 改 */
    choice* c;

    //最短路径相关
    index shortestPath[150];
    bool getPath(index*, int&, int, int);
    int shortestPathLen;
    bool build_update_and_check(int y_i,int x_i);
    void build_display(int y_i,int x_i);
    bool destroy_update_and_check_and_display(int y_i,int x_i,int type=0);

    //构造函数与析构
    explicit game(class ArkMidnight *parent = nullptr,
                  int stage_ = 0,
                  std::vector<std::vector<std::vector<int>>> mob_to_spawn_ = {{{}}},
                  std::vector<std::vector<int>> Mymap_ = {{}},
                  int diamond = 1000,
                  int heart = 5,
                  std::vector<int> shop_ = {1, 2, 3, 4, 5, 6}
                  );
    ~game();

    //关卡数
    int stage;
    //怪物入场了
    //怪物在回合开始时的tick数
    int start_value=0;
    //在回合结束时的tick数
    int end_value = 0;
    //本次游戏的关卡数量
    int wave_num;


    //本次关卡的怪物数量
    int mob_num=0;
    //目前应当生成的怪物序号
    int curr_mob=0;
    //目前未消失怪物数量,注意包含了还没生成的怪物
    int onFieldNum=0;
    //场上怪物
    int kill=0;
    //击杀怪物总数
    std::vector<Monster*> mob_on_field;

    //将要创造的怪物列表，按层次依次为：
    //1:波次，2:次序，3:多元数组
    //在3中 1:种类, 2:血量，3:速度 (1代表1s/1像素) 4:时间/timegap, 必须按顺序放
    std::vector<std::vector<std::vector<int>>> mob_to_spawn;
    //更新保护特效
    void protect_tower();
    //生成怪物函数，用于on_time_out
    void spawn_mobs();
    //怪物前进函数，用于on_time_out
    void march_mobs();
    //防御塔射击函数，用于on_time_out
    void tower_shoot();
    std::vector<bullet*> bullet_on_field;
    //子弹移动函数，用于on_time_out
    void bullet_move();
    //激光发射函数，用于on_time_out
    void laser_emit();
    //游戏失败，用于on_time_out
    void game_lose();
    //怪物死亡
    void mob_dead(Monster* mob);
    //治愈怪物
    void heal_mobs();
    void heal_mobs2();
    //怪物爆破塔
    void bomb_block();
    //游戏胜利，用于on_time_out
    void game_win();
    //起点
    int start_x;
    int start_y;
    //终点
    int end_x;
    int end_y;

private:
    //ui
    Ui::game *ui;

    //计时器
    QTimer *tim;


public:
    //一些场上参数
    int value;
    int sec;
    int wave;
    int diamond;
    bool ifWaveOver;
    int heart;
    int heart_total;
signals:
    void SignalInGame_openArkMidnight();
    void SignalInGame_openArkMidnight2();

public slots:
    void onTimeOut();
    void closeAnd();
    void closeAnd2();
private slots:
    void on_pushButton_clicked();
};

#endif // GAME_H
