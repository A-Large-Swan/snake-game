#include "ui.h"
#include <ncursesw/ncurses.h>

void init_ui(void) {
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    timeout(100);
}

void draw(void) {
    // 使用erase()代替clear()，减少闪烁
    erase();
    
    draw_border();
    draw_obstacles();
    draw_snake();
    draw_food();
    draw_score();
    
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
    attron(A_BOLD | A_BLINK);
    mvprintw(food.y, food.x, "*");
    attroff(A_BOLD | A_BLINK);
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