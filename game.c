#include "game.h"
#include "snake.h"
#include "level.h"
#include <stdlib.h>
#include <time.h>
#include <locale.h>

// 全局变量定义
Point food;
Level levels[3];
Point obstacles[MAX_OBSTACLES];
int num_obstacles = 0;
int score = 0;
int game_over = 0;
int current_level = 0;
int game_mode = MODE_CLASSIC;

void generate_food(void) {
    int valid = 0;
    while (!valid) {
        food.x = rand() % (WIDTH - 2) + 1;
        food.y = rand() % (HEIGHT - 2) + 1;
        
        // 确保食物不在障碍物或蛇身上
        if (!is_obstacle(food.x, food.y) && !is_snake_position(food.x, food.y)) {
            valid = 1;
        }
    }
}

void setup(void) {
    // 初始化ncurses
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    timeout(100);
    
    // 初始化随机数生成器
    srand(time(NULL));
    
    // 初始化关卡
    init_levels();
    
    // 选择游戏模式
    game_mode = show_mode_selection();
    
    if (game_mode == MODE_LEVELS) {
        // 加载第一关
        current_level = 0;
        load_level(current_level);
    }
    
    // 初始化蛇
    init_snake();
    
    // 生成第一个食物
    generate_food();
    
    // 重置分数
    score = 0;
    game_over = 0;
}

int check_collision(void) {
    // 检查蛇的碰撞
    if (check_snake_collision()) {
        return 1;
    }
    
    // 检查是否撞到障碍物
    if (game_mode == MODE_LEVELS) {
        if (is_obstacle(get_snake()->body[0].x, get_snake()->body[0].y)) {
            return 1;
        }
    }
    
    return 0;
}

void update(void) {
    int ch = get_user_input();
    
    if (ch == 'q') {
        game_over = 1;
        return;
    }
    
    // 更新蛇的位置
    update_snake(ch);
    
    // 检查是否吃到食物
    Snake* snake = get_snake();
    if (snake->body[0].x == food.x && snake->body[0].y == food.y) {
        snake->length++;
        score += 10;
        generate_food();
        
        // 检查是否完成关卡
        if (game_mode == MODE_LEVELS && score >= LEVEL_SCORE) {
            int choice = show_level_complete();
            if (choice == 0 && current_level < 2) {
                current_level++;
                load_level(current_level);
                score = 0;
            } else {
                game_over = 1;
            }
        }
    }
    
    // 检查碰撞
    if (check_collision()) {
        game_over = 1;
        if (game_mode == MODE_CLASSIC) {
            clear();
            wchar_t buf[100];
            swprintf(buf, sizeof(buf)/sizeof(wchar_t), L"游戏结束！最终得分: %d", score);
            mvaddwstr(HEIGHT/2, WIDTH/2 - 15, buf);
            refresh();
            sleep(5);
        }
    }
}