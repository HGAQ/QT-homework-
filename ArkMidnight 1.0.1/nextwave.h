#ifndef NEXTWAVE_H
#define NEXTWAVE_H

#include <QWidget>

namespace Ui {
class nextWave;
}

class nextWave : public QWidget
{
    Q_OBJECT

public:

    //所属游戏关卡
    class game* game;

    explicit nextWave(int _n, class game *parent = nullptr);
    ~nextWave();
signals:
    void SignalInNextWave_WavePutOn();
    void SignalInNextWave_TimC();
    void SignalInNextWave_Close();
    void SignalInNextWave_Close2();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void onTimeupDestroy();
    void on_pushButton_6_clicked();

private:
    Ui::nextWave *ui;
};

#endif // NEXTWAVE_H
