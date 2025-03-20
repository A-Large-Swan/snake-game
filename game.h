#ifndef GAME_H
#define GAME_H

#include "snake.h"

#define LEVEL_SCORE 100
#define MAX_OBSTACLES 100

// 游戏模式
#define MODE_CLASSIC 0
#define MODE_LEVELS 1

// 游戏状态
extern int score;
extern int game_over;
extern int current_level;
extern int game_mode;

// 用户输入
int get_user_input(void);

// 食物相关
extern Point food;
void generate_food(void);

// 游戏初始化和更新
void setup(void);
void update(void);
int check_collision(void);

// 游戏模式选择
int show_mode_selection(void);
int show_level_complete(void);

#endif // GAME_H