#include "../include/game.h"
#include "../include/snake.h"
#include "../include/level.h"
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
    // 为避免与障碍物和蛇重叠，先构建一个可用位置列表
    Point valid_positions[WIDTH * HEIGHT];
    int num_valid_positions = 0;
    
    // 遍历地图，找出所有可用位置
    for (int y = 1; y < HEIGHT - 1; y++) {
        for (int x = 1; x < WIDTH - 1; x++) {
            // 确保食物不会生成在蛇或障碍物上
            if (!is_obstacle(x, y) && !is_snake_position(x, y)) {
                valid_positions[num_valid_positions].x = x;
                valid_positions[num_valid_positions].y = y;
                num_valid_positions++;
            }
        }
    }
    
    // 如果有可用位置，随机选择一个
    if (num_valid_positions > 0) {
        int index = rand() % num_valid_positions;
        food.x = valid_positions[index].x;
        food.y = valid_positions[index].y;
    } else {
        // 如果没有可用位置，默认放在安全位置
        food.x = 1;
        food.y = 1;
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
                // 重置蛇的长度和位置
                init_snake();
                // 生成新的食物
                generate_food();
            } else {
                game_over = 1;
            }
        }
    }
    
    // 检查碰撞
    if (check_collision()) {
        game_over = 1;
        clear();
        wchar_t buf[100];
        
        if (game_mode == MODE_CLASSIC) {
            swprintf(buf, sizeof(buf)/sizeof(wchar_t), L"游戏结束！最终得分: %d", score);
            mvaddwstr(HEIGHT/2, WIDTH/2 - 15, buf);
            refresh();
            sleep(5);
        } else if (game_mode == MODE_LEVELS) {
            swprintf(buf, sizeof(buf)/sizeof(wchar_t), L"关卡 %d 失败！", current_level + 1);
            mvaddwstr(HEIGHT/2 - 3, WIDTH/2 - 10, buf);
            
            swprintf(buf, sizeof(buf)/sizeof(wchar_t), L"最终得分: %d / %d", score, LEVEL_SCORE);
            mvaddwstr(HEIGHT/2 - 1, WIDTH/2 - 10, buf);
            
            mvaddwstr(HEIGHT/2 + 1, WIDTH/2 - 10, L"按任意键退出游戏...");
            refresh();
            timeout(-1); // 等待用户按键
            getch();
            timeout(100); // 恢复原来的超时设置
        }
    }
}