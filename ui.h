#ifndef UI_H
#define UI_H

#include "snake.h"
#include "game.h"
#include "level.h"

// 界面绘制相关函数
void init_ui(void);
void draw(void);
void draw_border(void);
void draw_snake(void);
void draw_food(void);
void draw_obstacles(void);
void draw_score(void);

// 用户输入相关函数
int get_user_input(void);
void handle_input(int ch);

#endif // UI_H