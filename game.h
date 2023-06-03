#ifndef GAME_H
#define GAME_H
#include <Qtimer>
#include <QWidget>
#include <nextwave.h>

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
    friend nextWave;
    void putOnWaveNumber();

private:
    Ui::game *ui;
    QTimer *tim;
    static int value;
    static int sec;
    static int wave;
    static bool ifWaveOver;

public slots:
    void onTimeOut();
private slots:
    void on_pushButton_clicked();
};

#endif // GAME_H
