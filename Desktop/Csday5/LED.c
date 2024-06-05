#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ncurses.h>

#define LED_COLOR_PAIR 1

int main() {
    // 初始化ncurses
    initscr();
    start_color();
    init_pair(LED_COLOR_PAIR, COLOR_RED, COLOR_BLACK); // 定义彩色对

    // 获取终端窗口尺寸
    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);

    // 输入字符
    char input[100];
    printf("请输入要滚动显示的字符串: ");
    scanf("%s", input);

    // 设置滚动速度和消失速度
    int scroll_speed = 50000; // 微秒级
    int fade_speed = 100000;   // 微秒级

    // 滚动显示
    int i, j;
    for (i = 0; i < strlen(input) + max_x; i++) {
        clear();
        for (j = 0; j < strlen(input); j++) {
            if (i - j >= 0 && i - j < max_x) {
                mvaddch(max_y / 2, max_x - (i - j), input[j] | COLOR_PAIR(LED_COLOR_PAIR));
            }
        }
        refresh();
        usleep(scroll_speed);
    }

    // 渐隐消失
    for (i = max_x; i >= 0; i--) {
        clear();
        for (j = 0; j < strlen(input); j++) {
            if (i - j >= 0 && i - j < max_x) {
                mvaddch(max_y / 2, max_x - (i - j), input[j] | COLOR_PAIR(LED_COLOR_PAIR));
            }
        }
        refresh();
        usleep(fade_speed);
    }

    // 清理并退出
    endwin();
    return 0;
}
