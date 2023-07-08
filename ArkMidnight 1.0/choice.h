#ifndef CHOICE_H
#define CHOICE_H
#include "qlabel.h"
#include "QObject"


class choice: public QLabel
{
    Q_OBJECT;
public:
    QImage choice_img;
    QImage selected_img;
    QPixmap choice_pixmap;
    QPixmap selected_pixmap;
    explicit choice(QWidget *parent = nullptr, int k = 1);
};

#endif // CHOICE_H
