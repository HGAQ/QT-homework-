#ifndef GUIDE1_H
#define GUIDE1_H

#include <QWidget>

namespace Ui {
class guide1;
}

class guide1 : public QWidget
{
    Q_OBJECT

public:
    explicit guide1(QWidget *parent = nullptr);
    ~guide1();
    void switchPage();//切换函数

private slots:

    void on_btn_quit_2_clicked();

    void on_btn_last_to_guide1_clicked();

    void on_btn_next_to_guide3_clicked();

    void on_btn_next_to_guide2_clicked();

    void on_btn_quit_3_clicked();

    void on_btn_last_to_guide2_clicked();

    void on_btn_quit_1_clicked();

private:
    Ui::guide1 *ui;
};

#endif // GUIDE1_H
