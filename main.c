#include "snake.h"
#include "game.h"
#include "level.h"
#include "ui.h"
#include <unistd.h>

int main() {
    // 初始化游戏
    setup();
    
    // 游戏主循环
    while (!game_over) {
        // 绘制界面
        draw();
        
        // 更新游戏状态
        update();
        
        // 控制游戏速度
        usleep(DELAY);
    }
    
    // 游戏结束，清理资源
    endwin();
    return 0;
}