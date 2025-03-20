#ifndef SNAKE_H
#define SNAKE_H

#include <ncursesw/ncurses.h>

#define WIDTH 40
#define HEIGHT 20
#define SNAKE_LENGTH 5
#define DELAY 50000

typedef struct Point {
    int x;
    int y;
} Point;

typedef struct Snake {
    Point body[WIDTH * HEIGHT];
    int length;
    int direction;  // 0: up, 1: right, 2: down, 3: left
} Snake;

// 蛇的相关函数
void init_snake(void);
void update_snake(int ch);
int check_snake_collision(void);
int is_snake_position(int x, int y);

// 获取蛇的状态
Snake* get_snake(void);

#endif // SNAKE_H