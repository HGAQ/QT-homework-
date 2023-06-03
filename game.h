#ifndef GAME_H
#define GAME_H
#include <Qtimer>
#include <QWidget>
#include <vector>
#include "block.h"

namespace Ui {
class game;
}

class game : public QWidget
{
    Q_OBJECT

public:
    int board_width;
    int board_height;
    std::vector<std::vector<int>> Mymap;
    block*** Myblocks;
    explicit game(QWidget *parent = nullptr);
    ~game();

private:
    Ui::game *ui;
    QTimer *tim;

public slots:
    void onTimeOut();
};

#endif // GAME_H
