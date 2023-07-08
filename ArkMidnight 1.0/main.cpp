
#include "arkmidnight.h"

#include <QApplication>
#include <QScreen>
#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ArkMidnight widget;
    widget.resize(777, 541);


    QScreen *scr = a.primaryScreen();
    int scr_w = scr->size().width();
    int scr_h = scr->size().height();
    widget.move((scr_w - widget.width()) / 2, (scr_h - widget.height()) / 2);

    widget.show();

    return a.exec();
}
