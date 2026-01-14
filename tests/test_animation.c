#define _DEFAULT_SOURCE
#include <ncurses.h>
#include <locale.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include "ui/visual/deity_art.h"
#include "calendar/lunar.h"
#include "utils/common.h"

static unsigned long get_current_time_ms(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
}

int main(void) {
    setlocale(LC_ALL, "");

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    timeout(300);

    AnimationState anim_state;
    deity_animation_init(&anim_state, 4, 300);

    mvprintw(0, 0, "测试月老动画 (DEITY_YUELAO) - 按任意键切换神祇，q 退出");
    mvprintw(1, 0, "帧延迟: 300ms, getch 超时: 300ms");

    DeityType current_deity = DEITY_YUELAO;
    int frame_count = 0;
    unsigned long last_frame_time = 0;

    while (1) {
        unsigned long now = get_current_time_ms();

        // 清空屏幕
        erase();

        mvprintw(0, 0, "测试动画: %s (第 %d 帧切换)",
                 current_deity == DEITY_YUELAO ? "月老" :
                 current_deity == DEITY_ZAOSHEN ? "灶神" :
                 current_deity == DEITY_CAISHEN ? "财神" :
                 current_deity == DEITY_MENSHEN ? "门神" : "土地公",
                 frame_count);

        // 显示当前帧信息
        mvprintw(2, 0, "当前时间: %lu ms", now);
        mvprintw(3, 0, "上次更新: %lu ms", anim_state.last_update_ms);
        mvprintw(4, 0, "时间差: %lu ms", now - anim_state.last_update_ms);
        mvprintw(5, 0, "当前帧: %d", anim_state.current_frame);

        // 绘制神祇
        deity_draw(stdscr, 7, 2, current_deity, &anim_state);

        // 检查帧是否切换
        if (anim_state.last_update_ms != last_frame_time) {
            frame_count++;
            last_frame_time = anim_state.last_update_ms;
            mvprintw(6, 0, "帧已切换! 总切换次数: %d", frame_count);
        }

        refresh();

        int ch = getch();
        if (ch == 'q' || ch == 27) {
            break;
        } else if (ch != ERR) {
            // 切换神祇
            current_deity = (current_deity + 1) % DEITY_COUNT;
            frame_count = 0;
        }
    }

    endwin();
    printf("测试完成，总共切换了 %d 次帧\n", frame_count);
    return 0;
}
