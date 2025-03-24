#include "../include/snake.h"
#include "../include/game.h"
#include "../include/level.h"
#include "../include/ui.h"
#include <unistd.h>
#include <time.h>

int main() {
    // 初始化游戏
    setup();
    
    struct timespec last_frame_time, current_time;
    clock_gettime(CLOCK_MONOTONIC, &last_frame_time);
    
    // 游戏主循环
    while (!game_over) {
        // 获取当前时间
        clock_gettime(CLOCK_MONOTONIC, &current_time);
        
        // 计算距离上一帧的时间（纳秒）
        long time_elapsed = (current_time.tv_sec - last_frame_time.tv_sec) * 1000000000 + 
                            (current_time.tv_nsec - last_frame_time.tv_nsec);
        
        // 如果时间间隔足够，则更新并渲染
        if (time_elapsed >= DELAY * 1000) { // 将微秒转换为纳秒
            // 绘制界面
            draw();
            
            // 更新游戏状态
            update();
            
            // 更新上一帧时间
            last_frame_time = current_time;
        } else {
            // 短暂休眠减少CPU使用
            usleep(1000);
        }
    }
    
    // 游戏结束，清理资源
    endwin();
    return 0;
}