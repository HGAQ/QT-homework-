#ifndef ATTENTIONS_H
#define ATTENTIONS_H
#include <QLabel>
#include <qstring.h>
#include <qtimer.h>
#include <qpalette.h>

class attentions:public QLabel
{
    Q_OBJECT
public:
    attentions(QWidget* parent=nullptr,QString str="", Qt::GlobalColor=Qt::red,int _x=0,int _y=0,int shaketype=1);
    QString information;
    attentions* p_att2 = NULL; // 文字显示
    int type;
    int time;
    ~attentions(){}
    int x;
    int y;
    int num = 0;
private slots:
    void onTimeupDestroy();
    void onTimeupDestroy_2();
    void onTimeupDestroy_3();
};


#endif // ATTENTIONS_H
