#include "../include/level.h"
#include <string.h>

extern Level levels[3];
extern Point obstacles[MAX_OBSTACLES];
extern int num_obstacles;

void init_levels(void) {
    // 第一关：简单的障碍物
    levels[0].num_obstacles = 10;
    strcpy(levels[0].description, "Level 1: 简单障碍");
    for (int i = 0; i < 5; i++) {
        levels[0].obstacles[i].x = WIDTH/2;
        levels[0].obstacles[i].y = 5 + i;
    }
    for (int i = 5; i < 10; i++) {
        levels[0].obstacles[i].x = WIDTH/2;
        levels[0].obstacles[i].y = HEIGHT - 5 - (i - 5);
    }
    
    // 第二关：迷宫式障碍物
    levels[1].num_obstacles = 20;
    strcpy(levels[1].description, "Level 2: 迷宫挑战");
    // 左侧障碍
    for (int i = 0; i < 8; i++) {
        levels[1].obstacles[i].x = WIDTH/4;
        levels[1].obstacles[i].y = 5 + i;
    }
    // 右侧障碍
    for (int i = 8; i < 16; i++) {
        levels[1].obstacles[i].x = WIDTH*3/4;
        levels[1].obstacles[i].y = 5 + (i - 8);
    }
    // 中间障碍
    for (int i = 16; i < 20; i++) {
        levels[1].obstacles[i].x = WIDTH/2 - 2 + (i - 16);
        levels[1].obstacles[i].y = HEIGHT/2;
    }
    
    // 第三关：复杂障碍物
    levels[2].num_obstacles = 30;
    strcpy(levels[2].description, "Level 3: 终极挑战");
    // 十字形障碍
    for (int i = 0; i < 10; i++) {
        levels[2].obstacles[i].x = WIDTH/2;
        levels[2].obstacles[i].y = 5 + i;
    }
    for (int i = 10; i < 20; i++) {
        levels[2].obstacles[i].x = 10 + (i - 10);
        levels[2].obstacles[i].y = HEIGHT/2;
    }
    // 角落障碍
    for (int i = 20; i < 25; i++) {
        levels[2].obstacles[i].x = 5 + (i - 20);
        levels[2].obstacles[i].y = 5;
    }
    for (int i = 25; i < 30; i++) {
        levels[2].obstacles[i].x = WIDTH - 10 + (i - 25);
        levels[2].obstacles[i].y = HEIGHT - 5;
    }
}

void load_level(int level) {
    num_obstacles = levels[level].num_obstacles;
    for (int i = 0; i < num_obstacles; i++) {
        obstacles[i] = levels[level].obstacles[i];
    }
}

int is_obstacle(int x, int y) {
    for (int i = 0; i < num_obstacles; i++) {
        if (obstacles[i].x == x && obstacles[i].y == y) {
            return 1;
        }
    }
    return 0;
}