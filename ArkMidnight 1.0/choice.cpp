#include "choice.h"
#include <QDebug>

choice::choice(QWidget*parent, int k)
    :QLabel(parent)
{

    switch (k) {
    case 1:
        choice_img.load(":/tower/image/destroy.png");
        break;
    case 2:
        choice_img.load(":/tower/image/wall.png");
        break;
    case 3:
        choice_img.load(":/tower/image/arrow.png");
        break;
    case 4:
        choice_img.load(":/tower/image/laser.png");
        break;
    case 5:
        choice_img.load(":/tower/image/shield.png");
        break;
    case 6:
        choice_img.load(":/tower/image/attack.png");
        break;
    case 7:
        choice_img.load(":/tower/image/speed.png");
        break;
    }
    choice_pixmap = QPixmap::fromImage(choice_img);
    selected_img.load(":/setting/image/selected.png");
    selected_pixmap = QPixmap::fromImage(selected_img);
}
