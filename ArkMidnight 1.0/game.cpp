#include "game.h"
#include "arkmidnight.h"
#include "qmainwindow.h"
#include "qpainter.h"
#include "ui_game.h"
#include "attentions.h"
#include <Qtimer>
#include <cstring>
#include <iostream>
#include <QMouseEvent>
#include "nextwave.h"
#include "choice.h"
#include <QDebug>
#include <QtMath>
#include <math.h>

///////////////////////////////////////////构造析构///////////////////////////////////////////////////////////////


game::game(class ArkMidnight *parent_, int stage_,
                  std::vector<std::vector<std::vector<int>>> mob_to_spawn_ ,
                  std::vector<std::vector<int>> Mymap_ ,
                  int diamond_,
                  int heart_,
                  std::vector<int> shop_
            )
    :QWidget((QMainWindow*)parent_), shop(shop_), ui(new Ui::game)
{
    parent = parent_;
    ui->setupUi(this);
    board_height = 9;
    board_width = 12;
    this->setWindowTitle("game");
    this->setWindowIcon(QIcon(":/setting/image/icon.png"));

    tim = new QTimer();
    tim->setInterval(timegap);
    connect(tim, SIGNAL(timeout()), this, SLOT(onTimeOut()));
    tim->start();
    ///////////绘制初始地图///////////////
    Mymap = Mymap_;
    mob_to_spawn=mob_to_spawn_;
    Myblocks = new block * *[board_height];
    for (int y = 0; y < board_height; y++) {
        Myblocks[y] = new block * [board_width];
    }

    for (int x = 0; x < board_width; x++)
    {
        for (int y = 0; y < board_height; y++)
        {
            switch (Mymap[y][x]) {
            case 0:
                Myblocks[y][x] = new road(this, x, y);
                break;
            case 1:
                Myblocks[y][x] = new wall(this, x, y);
                break;
            case 2:
                Myblocks[y][x] = new start(this, x, y);
                start_x = x;
                start_y = y;
                break;
            case 3:
                Myblocks[y][x] = new end(this, x, y);
                end_x = x;
                end_y = y;
                break;
            case 9:
                Myblocks[y][x] = new heal(this, x, y);
                break;
            }
            Myblocks[y][x]->move(Myblocks[y][x]->x_position, Myblocks[y][x]->y_position);
            Myblocks[y][x]->setFixedSize(60, 60);
            Myblocks[y][x]->setPixmap(QPixmap::fromImage(Myblocks[y][x]->block_img));
            Myblocks[y][x]->raise();
        }
    }

    ///////////绘制初始商店///////////////
    c=new choice(this, 1);
    c->move(12*60, 60);
    c->setFixedSize(60, 60);
    c->setPixmap(QPixmap::fromImage(c->choice_img));
    c->raise();
    choices.push_back(c);
    for (unsigned int i=0; i < shop.size();++i){
        c=new choice(this, shop[i]+1);
        c->move(12*60, (i+2)*60);
        c->setFixedSize(60, 60);
        c->setPixmap(QPixmap::fromImage(c->choice_img));
        c->raise();
        int cost_ = 0;
        switch(shop[i]){
            case 1:
                cost_ = wall::cost;
                break;
            case 2:
                cost_ = arrow::cost;
                break;
            case 3:
                cost_ = laser::cost;
                break;
            case 4:
                cost_ = shield::cost;
                break;
            case 5:
                cost_ = attack::cost;
                break;
            case 6:
                cost_ = speed::cost;
                break;
        }
        choices.push_back(c);
        cost[i+1] = cost_;

        QLabel* back = new QLabel(this);
        back->setPixmap(QPixmap::fromImage(QImage(":/setting/image/back.png")));
        back->resize(60,60);
        back->raise();
        back->move(12*60, (i+2)*60);
        back->show();

        QLabel* money = new QLabel(this);
        money->setText(QString::asprintf("%d 💎", cost_));
        QPalette pe;
        pe.setColor(QPalette::WindowText, Qt::white);
        money->setPalette(pe);
        QFont ft;
        ft=QFont("Microsoft YaHei", 8, QFont::Bold);
        money->resize(60,60);
        money->setFont(ft);
        money->raise();
        money->setAlignment(Qt::AlignCenter);
        money->move(12*60, (i+2)*60+20);
        money->show();


    }
    setAttribute(Qt::WA_DeleteOnClose);

    value = 0;
    sec = 0;
    wave = 0;
    ifWaveOver = true;
    diamond = diamond_;//初始钻石数
    heart = heart_;
    heart_total = heart_;
    stage = stage_;
    wave_num=mob_to_spawn.size();
    kill=0;

    heartShow();
}


game::~game()
{
    delete ui;
}


/////////////////////////////////塔的建造与寻路////////////////////////////////////////////////////////////////////


bool game::inBoard(int x, int y)
{
    return x >= 0 && y >= 0 && x < board_width && y < board_height;
}


bool game::inShop(int x, int y)
{
    return x >= board_width && x < board_width + 1 && y >= 0 && y <= (int)shop.size()+1;
}


bool game::getPath(index* path, int& pathLen, int startx, int starty)
{
    bool visited[board_height][board_width];
    memset(visited, 0, sizeof(visited));
    int dx[4] = {1, 0, 0, -1};
    int dy[4] = {0, 1, -1, 0};
    struct POS{
        int x;
        int y;
        int step;
        int path_x[150],path_y[150];
    };
    POS q[150], Start;
    int t = 0, l = 0;
    Start.x = startx;
    Start.y = starty;
    Start.step = 0;
    Start.path_x[0] = Start.x;
    Start.path_y[0] = Start.y;
    q[0] = Start;
    visited[Start.y][Start.x] = true;

    while(t <= l)
    {
        for (int d = 0;d < 4;++d)
        {
            int xx = q[t].x + dx[d];
            int yy = q[t].y + dy[d];
            if (inBoard(xx,yy) && (Mymap[yy][xx] == 0||Mymap[yy][xx] == 3) && !visited[yy][xx])
            {
                visited[yy][xx]=true;
                l++;
                q[l]=q[t];
                q[l].x=xx;
                q[l].y=yy;
                q[l].step++;
                q[l].path_x[q[l].step] = xx;
                q[l].path_y[q[l].step] = yy;
                if (Myblocks[yy][xx]->is_end)
                {
                    pathLen = q[l].step + 1;
                    for (int i = 0;i < pathLen;++i)
                    {
                        path[i].x = q[l].path_x[i];
                        path[i].y = q[l].path_y[i];
                    }
                    return true;
                }
            }
        }
        t++;
    }
    return false;
}


//////////////////////////////////////////////////////////////////////////////////////////


void game::mousePressEvent(QMouseEvent* event)
{
    if (game_state){return;}
    int x_i = (event->position().x()) / 60; /* 改 */
    int y_i = (event->position().y()) / 60; /* 改 */

    if (game::inBoard(x_i, y_i))
    {
        if (build_and_destory >= 0)
        {
            if (build_and_destory==0)
            {//摧毁
                destroy_update_and_check_and_display(y_i,x_i);
            }
            else if(Myblocks[y_i][x_i]->block_type == 0 && diamond >= cost[build_and_destory])
            {
            //在road上建造&&钻石数够
                Mymap[y_i][x_i]=-1;
                //build_update_and_check
                //检测是否可以建造并改变路线//
                if (!build_update_and_check(y_i,x_i)){
                    //build_error_attention
                    attentions* p_att = new attentions(this,"不要堵路",Qt::red,Myblocks[y_i][x_i]->x_position,Myblocks[y_i][x_i]->y_position+30);
                    p_att->show();
                    Mymap[y_i][x_i]=0;
                }
                else{
                    build_display(y_i,x_i);
                }
            }
            else if(Myblocks[y_i][x_i]->block_type == 0 && diamond < cost[build_and_destory])
            {
                attentions* p_att = new attentions(this,"你没钱啦",Qt::red,Myblocks[y_i][x_i]->x_position,Myblocks[y_i][x_i]->y_position+30);
                p_att->show();
            }
            for (auto var:choices) {
                var->choice_pixmap = QPixmap::fromImage(var->choice_img);
                var->setPixmap(var->choice_pixmap);
                var->show();
            }
            build_and_destory = -1;
            return;
        }
    }
    if (game::inShop(x_i, y_i))
    {//计划：0-destroy;1-wall;2-arrow;3-laser;4-shield;5-attack;6-speed
        build_and_destory = y_i-1;
        for (auto var:choices) {
            var->choice_pixmap = QPixmap::fromImage(var->choice_img);
            var->setPixmap(var->choice_pixmap);
            var->show();
        }
        QPainter select_painter(&choices[build_and_destory]->choice_pixmap);
        select_painter.drawPixmap(0,0,choices[build_and_destory]->selected_pixmap);
        for (auto var:choices) {
            var->setPixmap(var->choice_pixmap);
            var->show();
        }
    }
    return; /* 改 */
}


bool game::destroy_update_and_check_and_display(int y_i,int x_i,int type){
    if(y_i>=0&&x_i>=0&&y_i<board_height&&x_i<board_width)
    {
        //分两类讨论，一类是能不能挖，一类是能不能炸掉
        if (((Myblocks[y_i][x_i]->can_destroy)&&(type==0)) || ((Myblocks[y_i][x_i]->protect<=0)&&(type==1)))
        {   //不是road则可以摧毁
            if (Myblocks[y_i][x_i]->block_type == 6){
                //挖了要给盾牌保护消除
                int dx[4] = {1, 0, 0, -1};
                int dy[4] = {0, 1, -1, 0};
                for (int i=0; i<4; i++){
                    int p_x = x_i+dx[i];
                    int p_y = y_i+dy[i];
                    if (inBoard(p_x, p_y) && (Myblocks[p_y][p_x]->block_type != 0)
                        && (Myblocks[p_y][p_x]->block_type != 2)&& (Myblocks[p_y][p_x]->block_type != 3)
                        && (Myblocks[p_y][p_x]->block_type != 6)){
                        (Myblocks[p_y][p_x]->protect)--;
                    }
                }
            }
            if (Myblocks[y_i][x_i]->block_type == 7){
                //挖了要给同谐效果消除
                int dx[4] = {1, 0, 0, -1};
                int dy[4] = {0, 1, -1, 0};
                for (int i=0; i<4; i++){
                    int p_x = x_i+dx[i];
                    int p_y = y_i+dy[i];
                    if (inBoard(p_x, p_y) && ((Myblocks[p_y][p_x]->block_type == 4) || (Myblocks[p_y][p_x]->block_type == 5))){
                        (Myblocks[p_y][p_x]->enhance_atk)--;
                    }
                }
            }
            if (Myblocks[y_i][x_i]->block_type == 8){
                //挖了要给巡猎效果消除
                int dx[4] = {1, 0, 0, -1};
                int dy[4] = {0, 1, -1, 0};
                for (int i=0; i<4; i++){
                    int p_x = x_i+dx[i];
                    int p_y = y_i+dy[i];
                    if (inBoard(p_x, p_y) && ((Myblocks[p_y][p_x]->block_type == 4) || (Myblocks[p_y][p_x]->block_type == 5))){
                        (Myblocks[p_y][p_x]->enhance_speed)--;
                    }
                }
            }
            delete Myblocks[y_i][x_i];
            Myblocks[y_i][x_i] = new road(this, x_i, y_i);
            Mymap[y_i][x_i]=0;
            Myblocks[y_i][x_i]->move(Myblocks[y_i][x_i]->x_position, Myblocks[y_i][x_i]->y_position);
            Myblocks[y_i][x_i]->setFixedSize(60, 60);
            Myblocks[y_i][x_i]->setPixmap(QPixmap::fromImage(Myblocks[y_i][x_i]->block_img));
            Myblocks[y_i][x_i]->lower();
            ui->label->lower();
            Myblocks[y_i][x_i]->show();
            for(auto mob = mob_on_field.begin(); mob != mob_on_field.end(); mob++){
                if ((*mob) && ((*mob)->kind != 2)){
                    getPath((*mob)->path, (*mob)->len, (*mob)->x_position/60, (*mob)->y_position/60);
                    (*mob)->adjust();
                }
            }
            return 1;
        }
        else{
            return 0;
        }
    }
    else{
        return 0;
    }
}


void game::build_display(int y_i,int x_i){
    int dx[4] = {1, 0, 0, -1};
    int dy[4] = {0, 1, -1, 0};
    delete Myblocks[y_i][x_i];
    switch (shop[build_and_destory-1])
    {
    case 1:
        Myblocks[y_i][x_i] = new wall(this, x_i, y_i);
        diamond -= wall::cost;
        Mymap[y_i][x_i]=1;
        break;
    case 2:
        Myblocks[y_i][x_i] = new arrow(this, x_i, y_i);
        diamond -= arrow::cost;
        Mymap[y_i][x_i]=4;
        break;
    case 3:
        Myblocks[y_i][x_i] = new laser(this, x_i, y_i);
        diamond -= laser::cost;
        Mymap[y_i][x_i]=5;
        break;
    case 4:
        Myblocks[y_i][x_i] = new shield(this, x_i, y_i); //是盾牌，给周围加保护
        diamond -= shield::cost;
        Mymap[y_i][x_i]=6;
        for (int i=0; i<4; i++){
            int p_x = x_i+dx[i];
            int p_y = y_i+dy[i];
            if (inBoard(p_x, p_y) && (Myblocks[p_y][p_x]->block_type != 0)
                && (Myblocks[p_y][p_x]->block_type != 2)&& (Myblocks[p_y][p_x]->block_type != 3)
                && (Myblocks[p_y][p_x]->block_type != 6)){
                (Myblocks[p_y][p_x]->protect)++;
            }
        }
        break;
    case 5:
        Myblocks[y_i][x_i] = new attack(this, x_i, y_i); //是同谐，给周围加攻击力
        diamond -= attack::cost;
        Mymap[y_i][x_i]=7;
        for (int i=0; i<4; i++){
            int p_x = x_i+dx[i];
            int p_y = y_i+dy[i];
            if (inBoard(p_x, p_y) && ((Myblocks[p_y][p_x]->block_type == 4) || (Myblocks[p_y][p_x]->block_type == 5))){
                (Myblocks[p_y][p_x]->enhance_atk)++;
            }
        }
        break;
    case 6:
        Myblocks[y_i][x_i] = new speed(this, x_i, y_i); //是巡猎，给周围加攻速
        diamond -= speed::cost;
        Mymap[y_i][x_i]=8;
        for (int i=0; i<4; i++){
            int p_x = x_i+dx[i];
            int p_y = y_i+dy[i];
            if (inBoard(p_x, p_y) && ((Myblocks[p_y][p_x]->block_type == 4) || (Myblocks[p_y][p_x]->block_type == 5))){
                (Myblocks[p_y][p_x]->enhance_speed)++;
            }
        }
        break;
    }
    if (shop[build_and_destory-1] != 4){//如果不是盾牌，放进去后要给自己加保护
        int dx[4] = {1, 0, 0, -1};
        int dy[4] = {0, 1, -1, 0};
        for (int i=0; i<4; i++){
            int p_x = x_i+dx[i];
            int p_y = y_i+dy[i];
            if (inBoard(p_x, p_y) && (Myblocks[p_y][p_x]->block_type == 6)){
                (Myblocks[y_i][x_i]->protect)++;
            }
        }
    }
    if ((shop[build_and_destory-1] == 2) || (shop[build_and_destory-1] == 3)){//如果是攻击塔，给自己加攻击力
        int dx[4] = {1, 0, 0, -1};
        int dy[4] = {0, 1, -1, 0};
        for (int i=0; i<4; i++){
            int p_x = x_i+dx[i];
            int p_y = y_i+dy[i];
            if (inBoard(p_x, p_y) && (Myblocks[p_y][p_x]->block_type == 7)){
                (Myblocks[y_i][x_i]->enhance_atk)++;
            }
        }
    }
    if ((shop[build_and_destory-1] == 2) || (shop[build_and_destory-1] == 3)){//如果是攻击塔，给自己加攻速
        int dx[4] = {1, 0, 0, -1};
        int dy[4] = {0, 1, -1, 0};
        for (int i=0; i<4; i++){
            int p_x = x_i+dx[i];
            int p_y = y_i+dy[i];
            if (inBoard(p_x, p_y) && (Myblocks[p_y][p_x]->block_type == 8)){
                (Myblocks[y_i][x_i]->enhance_speed)++;
            }
        }
    }
    Myblocks[y_i][x_i]->move(Myblocks[y_i][x_i]->x_position, Myblocks[y_i][x_i]->y_position);
    Myblocks[y_i][x_i]->setFixedSize(60, 60);
    Myblocks[y_i][x_i]->setPixmap(Myblocks[y_i][x_i]->block_pixmap);
    Myblocks[y_i][x_i]->lower();
    ui->label->lower();//图层显示顺序
    Myblocks[y_i][x_i]->show();
}


bool game::build_update_and_check(int y_i,int x_i){
    bool flag = true;
    if (ifWaveOver == false){
        index paths[150][150];
        int pathLens[150];
        int _i = 0;
        //对于每个怪物找是否有路，并存起来，有一个不行则flag改变
        for(auto mob = mob_on_field.begin(); mob != mob_on_field.end(); mob++){
            if ((*mob) && ((*mob)->kind != 2)){
                if (!getPath(paths[_i], pathLens[_i], (*mob)->x_position/60, (*mob)->y_position/60)){flag = false;};
                if ((abs((*mob)->x_position - x_i*60) < 60) && (abs((*mob)->y_position - y_i*60) < 60)){flag = false;};
                _i++;
            }
        }
        //对于起点找路，不用存，因为不行的话也不会改变，行的话就已经存起来了
        if (!getPath(shortestPath, shortestPathLen, start_x, start_y)){flag = false;}
        //改变怪物的路线
        if (flag){
            _i = 0;
            for(auto mob = mob_on_field.begin(); mob != mob_on_field.end(); mob++){
                if ((*mob) && ((*mob)->kind != 2)){
                    for (int _j = 0; _j < pathLens[_i]; ++_j)
                    {
                        (*mob)->path[_j].x = paths[_i][_j].x;
                        (*mob)->path[_j].y = paths[_i][_j].y;
                    }
                    _i++;
                    (*mob)->adjust();
                }
            }
        }
    }
    else{//对于没怪物则找起点就可以了
        flag = (getPath(shortestPath, shortestPathLen, start_x, start_y));
    }
    return flag;
}


////////////////////////////////////////////////////////////////////////////////////////////////


void game::onTimeOut()
{
    game::value++;
    ui->label_7->setText(QString::number(game::diamond));
    if (game::value / (1000 / timegap) > game::sec)
        ui->label_2->setText(QString::number(++game::sec));
    //if (game::ifWaveOver && wave_num == mob_to_spawn.size()) return;
    if(!game::ifWaveOver){
        //进入了回合
        //刚进入设置一下初始时间和怪物数量吧
        //std::cout<<"haimeishi"<<curr_mob<<std::endl;
        if(!start_value)
        {
            getPath(shortestPath, shortestPathLen, start_x, start_y);
            start_value=value;
        }
        if(!mob_num)
        {
            mob_num = mob_to_spawn[wave-1].size();
            onFieldNum = mob_num;
        }
        //保护效果展示
        protect_tower();
        //所有机械头发射范围激光
        laser_emit();
        //生成怪物
        spawn_mobs();
        //所有塔发射子弹
        tower_shoot();
        //所有子弹移动位置
        bullet_move();
        //治愈怪物，由塔回血
        heal_mobs();
        //治愈怪物，由怪物自己回血
        heal_mobs2();
        //boss2爆破
        bomb_block();
        //所有怪物前进，更新血条
        march_mobs();
        //判断游戏结束
        if (heart <= 0){
            game_lose();
        }
        //如果场上没有怪，生成列表也没怪，波次结束
        if (!onFieldNum){
            game::ifWaveOver = true;
        }
        //
        //std::cout<<value-start_value<<" "<<mob_num<<" "<<sec<<std::endl;
    }
    else{
        //回合结束初始化参数
        if(start_value){
            start_value=0;
            end_value=value;
            mob_num=0;
            curr_mob=0;
            for(auto &curr_bullet: bullet_on_field){//把没目标的子弹删了
                if(curr_bullet){
                    delete (curr_bullet);
                    curr_bullet=NULL;
                }
            }
            //std::cout << wave_num << std::endl;
            if (wave_num == wave && heart > 0) game_win();
            attentions* p_att = new attentions(this,QString::asprintf("第%d波结束！", wave),Qt::white,0,0,2); //回合结束条幅
            p_att->show();
        }
        protect_tower();
        //回合之间间隔不超过24s！
        if(value-end_value>=1200){
            wave++;
            ifWaveOver = false;
            attentions* p_att = new attentions(this,QString::asprintf("第%d波要开始了！", wave),Qt::white,0,0,2); //回合开始条幅
            p_att->show();
            putOnWaveNumber();
        }
    }
    //if(value > 100)
    //    tim->stop();
}


void game::protect_tower(){
    for (int x = 0; x < board_width; x++)
    {
        for (int y = 0; y < board_height; y++)
        {
            Myblocks[y][x]->block_pixmap=QPixmap::fromImage(Myblocks[y][x]->block_img);
            QPainter block_painter(&Myblocks[y][x]->block_pixmap);
            QFont font;//设置字体，下面设置字体属性
            font.setPointSize(15);//字体点大小
            block_painter.setFont(font);
            if(Myblocks[y][x]->can_destroy==1&&Myblocks[y][x]->protect>=1){
                block_painter.drawText(2,50,"🛡️");
            }
            if(Myblocks[y][x]->can_attack==1&&Myblocks[y][x]->enhance_atk>=1){

                block_painter.drawText(2,20,"⚔");
            }
            if(Myblocks[y][x]->can_attack==1&&Myblocks[y][x]->enhance_speed>=1){

                block_painter.drawText(30,20,"🐇");
            }
            Myblocks[y][x]->setPixmap(Myblocks[y][x]->block_pixmap);
            Myblocks[y][x]->lower();
            ui->label->lower();//图层显示顺序
            Myblocks[y][x]->show();
        }
    }
}


void game::laser_emit(){
    for (int x = 0; x < board_width; x++)
    {
        for (int y = 0; y < board_height; y++)
        {
            //激光塔！
            if(Mymap[y][x]==5 && Myblocks[y][x]->block_type==5){
                block* curr_block = Myblocks[y][x];
                //std::cout<<"123 "<<curr_block->to_shoot<<std::endl;
                int tower_x = curr_block->x_position;
                int tower_y = curr_block->y_position;
                //是时候射击了……
                if(curr_block->to_shoot==0){
                    curr_block->to_shoot=curr_block->shoot_speed*pow(0.8, curr_block->enhance_speed);
                    int target_x=-1;
                    int target_y=-1;
                    int min_distance=0x3f3f3f3f;
                    if(!mob_on_field.empty()){
                        for(Monster* curr_mob : mob_on_field){
                            if(curr_mob){
                                int mob_x=curr_mob->x_position;
                                int mob_y=curr_mob->y_position;
                                int distance = (mob_y-tower_y)*(mob_y-tower_y)+(mob_x-tower_x)*(mob_x-tower_x);
                                if(distance < curr_block->shoot_range * curr_block->shoot_range && distance < min_distance){
                                    min_distance=distance;
                                    target_x=mob_x;
                                    target_y=mob_y;
                                }
                            }
                        }
                        //如果有敌人在攻击范围内……
                        if(target_x!=-1&&target_y!=-1){
                            for(auto &curr_mob: mob_on_field){
                                if(curr_mob){
                                    int mob_x=curr_mob->x_position;
                                    int mob_y=curr_mob->y_position;
                                    int distance = (mob_y-tower_y)*(mob_y-tower_y)+(mob_x-tower_x)*(mob_x-tower_x);

                                    if (distance < curr_block->shoot_range * curr_block->shoot_range){
                                        //怪物被击中
                                        bullet* new_bullet=new laser_bullet(this,curr_block,tower_x+30,tower_y+30,mob_x+30,mob_y+30);
                                        new_bullet->setPixmap(new_bullet->bullet_pixmap);
                                        new_bullet->show();
                                        //
                                        curr_mob->now_hp -= ceil(Myblocks[y][x]->atk * pow(3, Myblocks[y][x]->enhance_atk)); //攻击力加增幅
                                        curr_mob->setPixmap(curr_mob->monster_pixmap);
                                        //死了！
                                        if(curr_mob->now_hp<=0){
                                            //是炸弹！！
                                            if(curr_mob->kind==1){
                                                int mob_x_index=(curr_mob->x_position+30)/60;
                                                int mob_y_index=(curr_mob->y_position+30)/60;
                                                destroy_update_and_check_and_display(mob_y_index,mob_x_index,1);
                                                destroy_update_and_check_and_display(mob_y_index,mob_x_index+1,1);
                                                destroy_update_and_check_and_display(mob_y_index+1,mob_x_index,1);
                                                destroy_update_and_check_and_display(mob_y_index,mob_x_index-1,1);
                                                destroy_update_and_check_and_display(mob_y_index-1,mob_x_index,1);
                                            }
                                            diamond+=curr_mob->diamond;
                                            QString report_diamond="💎+="+QString::number(curr_mob->diamond);
                                            attentions* p_att = new attentions(this,report_diamond,Qt::blue, mob_x-30,mob_y,0);
                                            p_att->show();
                                            //没血delete
                                            delete curr_mob;
                                            curr_mob = NULL;
                                            onFieldNum--;
                                            kill++;
                                        }
                                    }
                                }
                            }
                        }
                        else{
                            curr_block->to_shoot=0;
                        }
                    }
                    else{
                        curr_block->to_shoot=0;
                    }
                }
                //还不是时候……
                else{
                    curr_block->to_shoot--;
                }
            }
        }
    }
}


void game::bullet_move(){
    for(auto &curr_bullet: bullet_on_field){
        if(curr_bullet){
            if (curr_bullet->start_x > 720 || curr_bullet->start_x < 0 || curr_bullet->start_y > 540 || curr_bullet->start_y < 0 ){
            delete (curr_bullet);
            curr_bullet=NULL;
            }
        }
        if(curr_bullet){
            //箭塔的箭；
            if(curr_bullet->shooter->block_type==4){
                int bullet_x = curr_bullet->start_x;
                int bullet_y = curr_bullet->start_y;
                int collapse=0;
                //离怪物足够近
                for(auto &curr_mob: mob_on_field){
                    if(curr_mob){
                        int mob_x=curr_mob->x_position+30;
                        int mob_y=curr_mob->y_position+30;
                        int distance = (mob_y-bullet_y)*(mob_y-bullet_y)+(mob_x-bullet_x)*(mob_x-bullet_x);
                        if(distance < curr_bullet->range){//攻击
                            curr_mob->now_hp -= curr_bullet->atk;
                            delete (curr_bullet);
                            curr_bullet = NULL;
                            collapse = 1;
                            curr_mob->setPixmap(curr_mob->monster_pixmap);
                            //死了！
                            if(curr_mob->now_hp<=0){
                                //是炸弹！！
                                if(curr_mob->kind==1){
                                    int mob_x_index=(curr_mob->x_position+30)/60;
                                    int mob_y_index=(curr_mob->y_position+30)/60;
                                    destroy_update_and_check_and_display(mob_y_index,mob_x_index,1);
                                    destroy_update_and_check_and_display(mob_y_index,mob_x_index+1,1);
                                    destroy_update_and_check_and_display(mob_y_index+1,mob_x_index,1);
                                    destroy_update_and_check_and_display(mob_y_index,mob_x_index-1,1);
                                    destroy_update_and_check_and_display(mob_y_index-1,mob_x_index,1);
                                }
                                diamond+=curr_mob->diamond;
                                QString report_diamond="💎+="+QString::number(curr_mob->diamond);
                                attentions* p_att = new attentions(this,report_diamond,Qt::blue, mob_x-30,mob_y,0);
                                p_att->show();
                                //没血delete
                                delete curr_mob;
                                curr_mob = NULL;
                                onFieldNum--;
                                kill++;
                            }
                            break;
                        }

                    }
                }
                //没射到，动弹
                if(!collapse && curr_bullet){
                    bullet_x+=curr_bullet->moving_x;
                    bullet_y+=curr_bullet->moving_y;
                    curr_bullet->move(bullet_x,bullet_y);
                    curr_bullet->start_x=bullet_x;
                    curr_bullet->start_y=bullet_y;
                }
            }
        }
    }
}


void game::spawn_mobs(){
    if((curr_mob < mob_num) && ((value - start_value) > mob_to_spawn[wave-1][curr_mob][3]))
    {
        //std::cout<<"1"<<std::endl;
        //std::cout<<curr_mob<<std::endl;
        Monster* p_monster;
        if( mob_to_spawn[wave-1][curr_mob][0] == 0 ){
            p_monster=new Basic_Monster01(this,mob_to_spawn[wave-1][curr_mob][1],mob_to_spawn[wave-1][curr_mob][2],start_x,start_y);
        }
        else if( mob_to_spawn[wave-1][curr_mob][0] == 1 ){
            p_monster=new Basic_Monster02(this,mob_to_spawn[wave-1][curr_mob][1],mob_to_spawn[wave-1][curr_mob][2],start_x,start_y);
        }
        else if( mob_to_spawn[wave-1][curr_mob][0] == 2 ){
            p_monster=new Bomb_Monster01(this,mob_to_spawn[wave-1][curr_mob][1],mob_to_spawn[wave-1][curr_mob][2],start_x,start_y);
        }
        else if( mob_to_spawn[wave-1][curr_mob][0] == 3 ){
            p_monster=new Bomb_Monster02(this,mob_to_spawn[wave-1][curr_mob][1],mob_to_spawn[wave-1][curr_mob][2],start_x,start_y);
        }
        else if( mob_to_spawn[wave-1][curr_mob][0] == 4 ){
            p_monster=new Flying_Monster01(this,mob_to_spawn[wave-1][curr_mob][1],mob_to_spawn[wave-1][curr_mob][2],start_x,start_y);
        }
        else if( mob_to_spawn[wave-1][curr_mob][0] == 5 ){
            p_monster=new Flying_Monster02(this,mob_to_spawn[wave-1][curr_mob][1],mob_to_spawn[wave-1][curr_mob][2],start_x,start_y);
        }
        else if( mob_to_spawn[wave-1][curr_mob][0] == 6 ){
            p_monster=new Flying_Monster03(this,mob_to_spawn[wave-1][curr_mob][1],mob_to_spawn[wave-1][curr_mob][2],start_x,start_y);
        }
        else if( mob_to_spawn[wave-1][curr_mob][0] == 7 ){
            p_monster=new Basic_Monster03(this,mob_to_spawn[wave-1][curr_mob][1],mob_to_spawn[wave-1][curr_mob][2],start_x,start_y);
        }
        else if( mob_to_spawn[wave-1][curr_mob][0] == 8 ){
            p_monster=new Basic_Monster04(this,mob_to_spawn[wave-1][curr_mob][1],mob_to_spawn[wave-1][curr_mob][2],start_x,start_y);
        }
        else if( mob_to_spawn[wave-1][curr_mob][0] == 9 ){
            p_monster=new Heal_Monster01(this,mob_to_spawn[wave-1][curr_mob][1],mob_to_spawn[wave-1][curr_mob][2],start_x,start_y);
        }
        else if( mob_to_spawn[wave-1][curr_mob][0] == 10 ){
            p_monster=new Heal_Monster02(this,mob_to_spawn[wave-1][curr_mob][1],mob_to_spawn[wave-1][curr_mob][2],start_x,start_y);
        }
        else if( mob_to_spawn[wave-1][curr_mob][0] == 11 ){
            p_monster=new Boss_Monster01(this,mob_to_spawn[wave-1][curr_mob][1],mob_to_spawn[wave-1][curr_mob][2],start_x,start_y);
        }
        else if( mob_to_spawn[wave-1][curr_mob][0] == 12 ){
            p_monster=new Boss_Monster02(this,mob_to_spawn[wave-1][curr_mob][1],mob_to_spawn[wave-1][curr_mob][2],start_x,start_y);
        }
        else if( mob_to_spawn[wave-1][curr_mob][0] == 13 ){
            p_monster=new Boss_Monster03(this,mob_to_spawn[wave-1][curr_mob][1],mob_to_spawn[wave-1][curr_mob][2],start_x,start_y);
        }
        else{
            //避免空指针
            p_monster=new Basic_Monster01(this,mob_to_spawn[wave-1][curr_mob][1],mob_to_spawn[wave-1][curr_mob][2],start_x,start_y);
        }
        mob_on_field.push_back(p_monster);

        p_monster->setPixmap(p_monster->monster_pixmap);
        p_monster->show();
        curr_mob++;
    }
}


void game::march_mobs(){
    //对于在场上的怪物
    for(auto mob = mob_on_field.begin(); mob != mob_on_field.end(); mob++){
        if (*mob){
            //如果没有到达终点，让怪物自己前进
            if (!(*mob)->reachEnd(end_x, end_y)){
                (*mob)->forward();
                (*mob)->showHp();
                (*mob)->setPixmap((*mob)->monster_pixmap);

            }//到达终点，释放内存并从表中删除它
            else{
                //mob_on_field.erase(mob);
                delete (*mob);
                (*mob) = NULL;
                attentions* p_att = new attentions(this,"💔-=1",Qt::red, end_x*60, end_y*60+30,0);
                p_att->show();
                heart--;

                heartShow();

                onFieldNum--;
            }
        }
    }
}


void game::tower_shoot(){
    //std::cout<<"in_tower_shoot"<<curr_mob<<std::endl;
    for (int x = 0; x < board_width; x++)
    {
        for (int y = 0; y < board_height; y++)
        {
            //箭塔！
            if(Mymap[y][x]==4 && Myblocks[y][x]->block_type==4){
                //std::cout<<"in_arrow"<<y<<" "<<x<<std::endl;
                block* curr_block = Myblocks[y][x];
                int tower_x = curr_block->x_position;
                int tower_y = curr_block->y_position;
                //是时候射击了……
                if(curr_block->to_shoot==0){
                    curr_block->to_shoot=curr_block->shoot_speed*pow(0.8, curr_block->enhance_speed);
                    int target_x=-1;
                    int target_y=-1;
                    int min_distance=0x3f3f3f3f;
                    //
                    if(!mob_on_field.empty()){
                        for(Monster* curr_mob : mob_on_field){
                            if(curr_mob){
                                int mob_x=curr_mob->x_position;
                                int mob_y=curr_mob->y_position;
                                int distance = (mob_y-tower_y)*(mob_y-tower_y)+(mob_x-tower_x)*(mob_x-tower_x);
                                if(distance < curr_block->shoot_range * curr_block->shoot_range && distance < min_distance){
                                    min_distance=distance;
                                    target_x=mob_x;
                                    target_y=mob_y;
                                }
                            }
                        }

                        //如果有敌人在攻击范围内……
                        if(target_x!=-1&&target_y!=-1){
                            //std::cout<<"in_find_over"<<min_distance<<std::endl;
                            bullet* new_bullet=new arrow_bullet(this,curr_block,tower_x+30,tower_y+30,target_x+30,target_y+30);
                            bullet_on_field.push_back(new_bullet);
                            new_bullet->setPixmap(QPixmap::fromImage(new_bullet->bullet_img));
                            new_bullet->show();
                            //std::cout<<new_bullet->moving_x<<" "<<new_bullet->moving_y<<std::endl;
                        }
                        else{
                            curr_block->to_shoot=0;
                        }
                    }
                    else{
                        curr_block->to_shoot=0;
                    }
                }
                //还不是时候……
                else{
                    //std::cout<<"not_in_shoot"<<curr_block->to_shoot<<std::endl;
                    curr_block->to_shoot--;
                }
            }
        }
    }
}


void game::game_win(){
    game_state = 1;
    tim->stop();
    QTimer::singleShot(2000, this, [this](){
        attentions* p_att = new attentions(this,QString::asprintf("通关！"),Qt::white,0,0,2); //胜利条幅
        p_att->show();});
    QTimer::singleShot(4000, this, [this](){
        game::ifWaveOver = true;
        parent->state[0] = stage;
        parent->state[1] = 1;
        parent->state[2] = diamond;
        parent->state[3] = heart;
        parent->state[4] = kill;
        parent->state[5] = sec;
        closeAnd2();});
}


void game::game_lose(){
    game_state = 2;
    tim->stop();
    QTimer::singleShot(0, this, [this](){
        attentions* p_att = new attentions(this,QString::asprintf("失败！"),Qt::white,0,0,2); //失败条幅
        p_att->show();});
    QTimer::singleShot(2000, this, [this](){
        game::ifWaveOver = true;
        parent->state[0] = stage;
        parent->state[1] = 2;
        parent->state[2] = diamond;
        parent->state[3] = heart;
        parent->state[4] = kill;
        parent->state[5] = sec;
        closeAnd2();});
}


void game::heal_mobs(){
    for (int x = 0; x < board_width; x++)
    {
        for (int y = 0; y < board_height; y++)
        {
            //丰饶孽物
            if(Mymap[y][x]==9 && Myblocks[y][x]->block_type==9){
                block* curr_block = Myblocks[y][x];
                int tower_x = curr_block->x_position;
                int tower_y = curr_block->y_position;
                //是时候治愈了……
                if(curr_block->to_shoot==0){
                    curr_block->to_shoot=curr_block->shoot_speed;
                    int target_x=-1;
                    int target_y=-1;
                    int min_distance=0x3f3f3f3f;
                    if(!mob_on_field.empty()){
                        for(Monster* curr_mob : mob_on_field){
                            if(curr_mob){
                                int mob_x=curr_mob->x_position;
                                int mob_y=curr_mob->y_position;
                                int distance = (mob_y-tower_y)*(mob_y-tower_y)+(mob_x-tower_x)*(mob_x-tower_x);
                                if(distance < curr_block->shoot_range * curr_block->shoot_range && distance < min_distance){
                                    min_distance=distance;
                                    target_x=mob_x;
                                    target_y=mob_y;
                                }
                            }
                        }
                        //如果有敌人在治愈范围内……
                        if(target_x!=-1&&target_y!=-1){
                            for(auto &curr_mob: mob_on_field){
                                if(curr_mob){
                                    int mob_x=curr_mob->x_position;
                                    int mob_y=curr_mob->y_position;
                                    int distance = (mob_y-tower_y)*(mob_y-tower_y)+(mob_x-tower_x)*(mob_x-tower_x);

                                    if (distance < curr_block->shoot_range * curr_block->shoot_range){
                                        QString report_diamond="💚HEAL💚";
                                        attentions* p_att = new attentions(this,report_diamond,Qt::green, curr_mob->x_position+10,curr_mob->y_position+45,0);
                                        p_att->show();
                                        //怪物被治愈
                                        curr_mob->now_hp = std::min(curr_mob->now_hp+curr_block->atk, curr_mob->sum_hp);
                                        curr_mob->setPixmap(curr_mob->monster_pixmap);
                                    }
                                }
                            }
                        }
                        else{
                            curr_block->to_shoot=0;
                        }
                    }
                    else{
                        curr_block->to_shoot=0;
                    }
                }
                //还不是时候……
                else{
                    curr_block->to_shoot--;
                }
            }
        }
    }
}


void game::heal_mobs2(){
    for(Monster* curr_mob : mob_on_field){
        if(curr_mob && curr_mob->kind == 3){
            Heal_Monster* curr_heal_mob = (Heal_Monster*)curr_mob;
            if(curr_heal_mob->to_heal==0){
                //怪物被治愈
                QString report_diamond="💚HEAL💚";
                attentions* p_att = new attentions(this,report_diamond,Qt::green, curr_heal_mob->x_position+10,curr_heal_mob->y_position+45,0);
                p_att->show();
                curr_heal_mob->now_hp = std::min(curr_heal_mob->now_hp+curr_heal_mob->heal, curr_heal_mob->sum_hp);
                curr_heal_mob->setPixmap(curr_heal_mob->monster_pixmap);
                curr_heal_mob->to_heal=curr_heal_mob->heal_speed;
            }
            else{
                curr_heal_mob->to_heal--;
            }
        }
    }
}


void game::bomb_block(){
    for(Monster* curr_mob : mob_on_field){
        if(curr_mob && curr_mob->kind == 4){
            Boss_Monster02* curr_bomb_mob = (Boss_Monster02* )curr_mob;
            if(curr_bomb_mob->to_bomb==0){
                //怪物爆破
                for (int x = 0; x < board_width; x++)
                {
                    for (int y = 0; y < board_height; y++)
                    {
                        if (destroy_update_and_check_and_display(y, x, 1)){
                            QString report_diamond="💥BOMB💥";
                            attentions* p_att = new attentions(this,report_diamond,Qt::red, x*60, y*60+30,0);
                            p_att->show();
                        }
                    }
                }
                for (int x = 0; x < board_width; x++)
                {
                    for (int y = 0; y < board_height; y++)
                    {
                        if(Mymap[y][x]==6 && Myblocks[y][x]->block_type==6){
                            QString report_diamond="💥BOMB💥";
                            attentions* p_att = new attentions(this,report_diamond,Qt::red, x*60,y*60+30,0);
                            p_att->show();
                            destroy_update_and_check_and_display(y, x, 0);
                        }
                    }
                }
                curr_bomb_mob->to_bomb=curr_bomb_mob->bomb_speed;
            }
            else{
                curr_bomb_mob->to_bomb--;
            }
        }
    }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////


void game::closeAnd(){
    emit SignalInGame_openArkMidnight();
    this->close();
}


void game::closeAnd2(){
    emit SignalInGame_openArkMidnight2();
    this->close();
}


void game::putOnWaveNumber() {
    ui->label_5->setText(QString::number(game::wave));
}


void game::heartShow(){
    //显示爱心，波数时间和钻石数不用在此考虑
    QString now_heart = "";
    int _i_ = 0;
    for(; _i_ < game::heart; _i_++){
        if(_i_ == 5){ now_heart = now_heart + "\n";}
        now_heart = now_heart + "💖";
    }
    for(; _i_ < game::heart_total; _i_++){
        if(_i_ == 5){ now_heart = now_heart + "\n";}
        now_heart = now_heart + "💘";
    }

    ui->label_9->setText(now_heart);
}


void game::continueTim(){
    tim->start();
}


void game::on_pushButton_clicked()
{
    if (game::ifWaveOver) {
        tim->stop();
        nextWave* w = new nextWave(0, this);
        connect(w, &nextWave::SignalInNextWave_TimC, this, &game::continueTim);
        connect(w, &nextWave::SignalInNextWave_WavePutOn, this, &game::putOnWaveNumber);
        connect(w, &nextWave::SignalInNextWave_Close2, this, &game::closeAnd);
        int x = this->pos().x() + 180;
        int y = this->pos().y();
        w->setWindowModality(Qt::ApplicationModal);
        w->setWindowTitle("确定吗？");
        w->move(x, y);
        w->show();
    }
    else {
        tim->stop();
        nextWave* w = new nextWave(2, this);
        connect(w, &nextWave::SignalInNextWave_TimC, this, &game::continueTim);
        connect(w, &nextWave::SignalInNextWave_Close2, this, &game::closeAnd);
        int x = this->pos().x() + 180;
        int y = this->pos().y();
        w->setWindowModality(Qt::ApplicationModal);
        w->setWindowTitle("你先别急！");
        w->move(x, y);
        w->show();
    }
}


