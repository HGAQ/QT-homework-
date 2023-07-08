
#ifndef ARKMIDNIGHT_H
#define ARKMIDNIGHT_H

#include <QMainWindow>



QT_BEGIN_NAMESPACE
namespace Ui { class ArkMidnight; }
QT_END_NAMESPACE

class ArkMidnight : public QMainWindow

{
    Q_OBJECT

public:
    ArkMidnight(QWidget *parent = nullptr, int _n = 0);
    ~ArkMidnight();
    void vis();
    void vis2();
    static int state[10];

private slots:
    void on_btn_guide_clicked();

    void on_btn_start_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_return_clicked();

    void on_pushButton_return_2_clicked();

private:
    Ui::ArkMidnight *ui;
};

#endif // ARKMIDNIGHT_H
