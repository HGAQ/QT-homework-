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
    explicit nextWave(int _n, QWidget *parent = nullptr);
    ~nextWave();
signals:
    void SignalInNextWave_WavePutOn();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::nextWave *ui;
};

#endif // NEXTWAVE_H
