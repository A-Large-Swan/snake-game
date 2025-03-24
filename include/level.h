#ifndef LEVEL_H
#define LEVEL_H

#define MAX_OBSTACLES 100

#include "snake.h"

// 关卡结构
typedef struct Level {
    Point obstacles[MAX_OBSTACLES];
    int num_obstacles;
    char description[100];
} Level;

// 关卡相关变量
extern Level levels[3];
extern Point obstacles[MAX_OBSTACLES];
extern int num_obstacles;

// 关卡相关函数
void init_levels(void);
void load_level(int level);
int is_obstacle(int x, int y);

#endif // LEVEL_H