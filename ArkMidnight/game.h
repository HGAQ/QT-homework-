#ifndef GAME_H
#define GAME_H
#include <Qtimer>
#include <QWidget>

#define timegap 20

namespace Ui {
class game;
}

class game : public QWidget
{
    Q_OBJECT

public:
    explicit game(QWidget *parent = nullptr);
    ~game();

private:
    Ui::game *ui;
    QTimer *tim;

public slots:
    void onTimeOut();
    void waveInc();
};

#endif // GAME_H
