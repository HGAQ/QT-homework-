
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
    ArkMidnight(QWidget *parent = nullptr);
    ~ArkMidnight();

private slots:
    void on_btn_guide_clicked();

    void on_btn_start_clicked();

private:
    Ui::ArkMidnight *ui;
};

#endif // ARKMIDNIGHT_H
