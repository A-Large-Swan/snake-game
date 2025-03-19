#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

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

Point food;
Snake snake;
int score = 0;
int game_over = 0;

void setup() {
    // 初始化ncurses
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    timeout(100);
    
    // 初始化随机数生成器
    srand(time(NULL));
    
    // 初始化蛇
    snake.length = SNAKE_LENGTH;
    snake.direction = 1;
    for (int i = 0; i < snake.length; i++) {
        snake.body[i].x = WIDTH/4 - i;
        snake.body[i].y = HEIGHT/2;
    }
    
    // 生成第一个食物
    food.x = rand() % (WIDTH - 2) + 1;
    food.y = rand() % (HEIGHT - 2) + 1;
}

void draw() {
    // 使用erase()代替clear()，减少闪烁
    erase();
    
    // 绘制边界
    attron(A_BOLD);  // 使边界更明显
    for (int i = 0; i < WIDTH; i++) {
        mvprintw(0, i, "#");
        mvprintw(HEIGHT-1, i, "#");
    }
    for (int i = 0; i < HEIGHT; i++) {
        mvprintw(i, 0, "#");
        mvprintw(i, WIDTH-1, "#");
    }
    attroff(A_BOLD);
    
    // 绘制蛇
    for (int i = 0; i < snake.length; i++) {
        mvprintw(snake.body[i].y, snake.body[i].x, "O");
    }
    
    // 绘制食物
    mvprintw(food.y, food.x, "*");
    
    // 显示分数
    mvprintw(HEIGHT + 1, 0, "Score: %d", score);
    
    refresh();
}

void generate_food() {
    food.x = rand() % (WIDTH - 2) + 1;
    food.y = rand() % (HEIGHT - 2) + 1;
}

int check_collision() {
    // 检查是否撞到墙
    if (snake.body[0].x == 0 || snake.body[0].x == WIDTH-1 ||
        snake.body[0].y == 0 || snake.body[0].y == HEIGHT-1)
        return 1;
    
    // 检查是否撞到自己
    for (int i = 1; i < snake.length; i++) {
        if (snake.body[0].x == snake.body[i].x &&
            snake.body[0].y == snake.body[i].y)
            return 1;
    }
    
    return 0;
}

void update() {
    int ch = getch();
    
    // 更新方向
    switch(ch) {
        case KEY_UP:
            if (snake.direction != 2) snake.direction = 0;
            break;
        case KEY_RIGHT:
            if (snake.direction != 3) snake.direction = 1;
            break;
        case KEY_DOWN:
            if (snake.direction != 0) snake.direction = 2;
            break;
        case KEY_LEFT:
            if (snake.direction != 1) snake.direction = 3;
            break;
        case 'q':
            game_over = 1;
            break;
    }
    
    // 保存蛇头的旧位置
    Point old_head = snake.body[0];
    
    // 移动蛇身
    for (int i = snake.length-1; i > 0; i--) {
        snake.body[i] = snake.body[i-1];
    }
    
    // 根据方向移动蛇头
    snake.body[0] = old_head;
    switch(snake.direction) {
        case 0: // up
            snake.body[0].y--;
            break;
        case 1: // right
            snake.body[0].x++;
            break;
        case 2: // down
            snake.body[0].y++;
            break;
        case 3: // left
            snake.body[0].x--;
            break;
    }
    
    // 检查是否吃到食物
    if (snake.body[0].x == food.x && snake.body[0].y == food.y) {
        score += 10;
        snake.length++;
        generate_food();
    }
    
    // 检查碰撞
    if (check_collision()) {
        game_over = 1;
    }
}

int main() {
    setup();
    
    while (!game_over) {
        draw();
        update();
        usleep(DELAY);
    }
    
    // 游戏结束
    clear();
    mvprintw(HEIGHT/2, WIDTH/2 - 5, "Game Over!");
    mvprintw(HEIGHT/2 + 1, WIDTH/2 - 7, "Final Score: %d", score);
    refresh();
    sleep(2);
    
    endwin();
    return 0;
}