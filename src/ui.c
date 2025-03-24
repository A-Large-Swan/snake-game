#include "../include/ui.h"
#include <ncursesw/ncurses.h>

void init_ui(void) {
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    timeout(50); // 减少输入检测的超时时间
    
    // 启用双缓冲区减少闪烁
    if (has_colors()) {
        start_color();
    }
}

void draw(void) {
    // 使用erase()代替clear()，减少闪烁
    erase();
    
    // 优化绘制顺序
    // 1. 先绘制边框
    draw_border();
    
    // 2. 再绘制障碍物
    draw_obstacles();
    
    // 3. 接着绘制蛇身体（除了头部）
    draw_snake_body();
    
    // 4. 然后绘制食物，确保食物在蛇身上方
    draw_food();
    
    // 5. 最后绘制蛇头，确保蛇头在最上层
    draw_snake_head();
    
    // 6. 绘制分数和其他信息
    draw_score();
    
    // 使用refresh而不是全屏刷新，减少闪烁
    refresh();
}

void draw_border(void) {
    attron(A_BOLD);
    for (int i = 0; i < WIDTH; i++) {
        mvprintw(0, i, "#");
        mvprintw(HEIGHT-1, i, "#");
    }
    for (int i = 0; i < HEIGHT; i++) {
        mvprintw(i, 0, "#");
        mvprintw(i, WIDTH-1, "#");
    }
    attroff(A_BOLD);
}

void draw_snake(void) {
    Snake* snake = get_snake();
    for (int i = 0; i < snake->length; i++) {
        if (i == 0) {
            attron(A_BOLD);
            mvprintw(snake->body[i].y, snake->body[i].x, "@"); // 蛇头用不同符号
            attroff(A_BOLD);
        } else {
            mvprintw(snake->body[i].y, snake->body[i].x, "O");
        }
    }
}

void draw_food(void) {
    // 先确保食物位置是空的
    mvprintw(food.y, food.x, " ");
    
    // 根据关卡使用不同的食物表示和属性
    attron(A_BOLD);
    
    if (game_mode == MODE_LEVELS) {
        // 不同关卡使用不同的食物符号
        switch (current_level) {
            case 0:
                mvprintw(food.y, food.x, "*");
                break;
            case 1:
                mvprintw(food.y, food.x, "+");
                break;
            case 2:
                mvprintw(food.y, food.x, "$");
                break;
            default:
                mvprintw(food.y, food.x, "*");
                break;
        }
    } else {
        // 经典模式使用普通的食物符号
        mvprintw(food.y, food.x, "*");
    }
    
    attroff(A_BOLD);
}

void draw_obstacles(void) {
    if (game_mode == MODE_LEVELS) {
        attron(A_BOLD | A_STANDOUT);
        for (int i = 0; i < num_obstacles; i++) {
            mvprintw(obstacles[i].y, obstacles[i].x, "X");
        }
        attroff(A_BOLD | A_STANDOUT);
    }
}

void draw_score(void) {
    mvprintw(HEIGHT + 1, 0, "Score: %d", score);
    if (game_mode == MODE_LEVELS) {
        mvprintw(HEIGHT + 1, WIDTH/2 - 10, "Level: %d - %s", current_level + 1, levels[current_level].description);
        mvprintw(HEIGHT + 2, WIDTH/2 - 10, "目标: 得到 %d 分进入下一关", LEVEL_SCORE);
    }
}

int get_user_input(void) {
    return getch();
}

void handle_input(int ch) {
    switch(ch) {
        case KEY_UP:
        case KEY_RIGHT:
        case KEY_DOWN:
        case KEY_LEFT:
            update_snake(ch);
            break;
        case 'q':
            game_over = 1;
            break;
    }
}

// 绘制蛇身体（不包括头部）
void draw_snake_body(void) {
    Snake* snake = get_snake();
    
    // 只绘制蛇身（从索引1开始，跳过蛇头）
    for (int i = 1; i < snake->length; i++) {
        mvprintw(snake->body[i].y, snake->body[i].x, "O");
    }
}

// 绘制蛇头
void draw_snake_head(void) {
    Snake* snake = get_snake();
    
    // 只绘制蛇头（索引0）
    attron(A_BOLD);
    mvprintw(snake->body[0].y, snake->body[0].x, "@");
    attroff(A_BOLD);
}