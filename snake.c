#include "snake.h"
#include "game.h"
#include "level.h"
#include "ui.h"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <wchar.h>

extern Point food;
extern Level levels[3];
extern Point obstacles[MAX_OBSTACLES];
extern int num_obstacles;
extern int score;
extern int game_over;
extern int current_level;
extern int game_mode;

// 全局蛇变量
static Snake snake;

// 获取蛇的状态
Snake* get_snake(void) {
    return &snake;
}

// 初始化蛇
void init_snake(void) {
    snake.length = SNAKE_LENGTH;
    snake.direction = 1; // 初始向右移动
    
    // 设置蛇的初始位置在屏幕中间
    int start_x = WIDTH / 4;
    int start_y = HEIGHT / 2;
    
    for (int i = 0; i < snake.length; i++) {
        snake.body[i].x = start_x - i;
        snake.body[i].y = start_y;
    }
}

// 更新蛇的位置
void update_snake(int ch) {
    // 根据输入更新方向
    if (ch == KEY_UP && snake.direction != 2) snake.direction = 0;
    else if (ch == KEY_RIGHT && snake.direction != 3) snake.direction = 1;
    else if (ch == KEY_DOWN && snake.direction != 0) snake.direction = 2;
    else if (ch == KEY_LEFT && snake.direction != 1) snake.direction = 3;
    
    // 保存蛇头的当前位置
    int head_x = snake.body[0].x;
    int head_y = snake.body[0].y;
    
    // 根据方向移动蛇头
    switch (snake.direction) {
        case 0: head_y--; break; // 上
        case 1: head_x++; break; // 右
        case 2: head_y++; break; // 下
        case 3: head_x--; break; // 左
    }
    
    // 移动蛇身
    for (int i = snake.length - 1; i > 0; i--) {
        snake.body[i] = snake.body[i-1];
    }
    
    // 更新蛇头位置
    snake.body[0].x = head_x;
    snake.body[0].y = head_y;
}

// 检查蛇是否碰撞到自己或边界
int check_snake_collision(void) {
    // 检查是否撞到边界
    if (snake.body[0].x <= 0 || snake.body[0].x >= WIDTH-1 ||
        snake.body[0].y <= 0 || snake.body[0].y >= HEIGHT-1) {
        return 1;
    }
    
    // 检查是否撞到自己
    for (int i = 1; i < snake.length; i++) {
        if (snake.body[0].x == snake.body[i].x &&
            snake.body[0].y == snake.body[i].y) {
            return 1;
        }
    }
    
    return 0;
}

// 检查某个位置是否是蛇的身体
int is_snake_position(int x, int y) {
    for (int i = 0; i < snake.length; i++) {
        if (snake.body[i].x == x && snake.body[i].y == y) {
            return 1;
        }
    }
    return 0;
}

// 显示模式选择界面
int show_mode_selection() {
    clear();
    int choice = 0;
    int key;
    
    while (1) {
        clear();
        mvaddwstr(HEIGHT/2 - 5, WIDTH/2 - 10, L"贪吃蛇游戏 - 模式选择");
        
        if (choice == 0) attron(A_REVERSE);
        mvaddwstr(HEIGHT/2 - 2, WIDTH/2 - 5, L"经典模式");
        if (choice == 0) attroff(A_REVERSE);
        
        if (choice == 1) attron(A_REVERSE);
        mvaddwstr(HEIGHT/2, WIDTH/2 - 5, L"闯关模式");
        if (choice == 1) attroff(A_REVERSE);
        
        mvaddwstr(HEIGHT/2 + 3, WIDTH/2 - 15, L"使用上下键选择，回车确认");
        
        refresh();
        key = getch();
        
        if (key == KEY_UP) {
            choice = 0;
        } else if (key == KEY_DOWN) {
            choice = 1;
        } else if (key == 10) { // 回车键
            return choice;
        }
    }
}

// 显示关卡完成界面
int show_level_complete() {
    clear();
    int choice = 0;
    int key;
    wchar_t buf[100];
    
    while (1) {
        clear();
        swprintf(buf, sizeof(buf)/sizeof(wchar_t), L"恭喜！关卡 %d 完成！", current_level + 1);
        mvaddwstr(HEIGHT/2 - 5, WIDTH/2 - 10, buf);
        swprintf(buf, sizeof(buf)/sizeof(wchar_t), L"得分: %d", score);
        mvaddwstr(HEIGHT/2 - 3, WIDTH/2 - 10, buf);
        
        if (choice == 0) attron(A_REVERSE);
        mvaddwstr(HEIGHT/2, WIDTH/2 - 5, L"下一关");
        if (choice == 0) attroff(A_REVERSE);
        
        if (choice == 1) attron(A_REVERSE);
        mvaddwstr(HEIGHT/2 + 2, WIDTH/2 - 5, L"退出游戏");
        if (choice == 1) attroff(A_REVERSE);
        
        mvaddwstr(HEIGHT/2 + 5, WIDTH/2 - 15, L"使用上下键选择，回车确认");
        
        refresh();
        key = getch();
        
        if (key == KEY_UP) {
            choice = 0;
        } else if (key == KEY_DOWN) {
            choice = 1;
        } else if (key == 10) { // 回车键
            return choice;
        }
    }
}