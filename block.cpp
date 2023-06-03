#include "block.h"

block::block(QWidget*parent, int x ,int y)
    :QLabel(parent)
{
    x_index = x;
    y_index = y;
    x_position = x * 60;
    y_position = y * 60;

}

road::road(QWidget*parent, int x ,int y):block(parent, x , y){
    can_destroy=0;
    can_through=1;
    is_start=0;
    is_end=0;
    block_type=0;
    block_img.load(":/tower/image/empty.png");
}


wall::wall(QWidget*parent, int x ,int y):block(parent, x , y){
    can_destroy=1;
    can_through=0;
    is_start=0;
    is_end=0;
    block_type=1;
    block_img.load(":/tower/image/wall.png");
}

start::start(QWidget*parent, int x ,int y):block(parent, x , y){
    can_destroy=0;
    can_through=0;
    is_start=1;
    is_end=0;
    block_type=2;
    block_img.load(":/tower/image/start.png");
}

end::end(QWidget*parent, int x ,int y):block(parent, x , y){
    can_destroy=0;
    can_through=0;
    is_start=0;
    is_end=1;
    block_type=3;
    block_img.load(":/tower/image/end.png");
}
