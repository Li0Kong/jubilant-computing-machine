#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <time.h>
#include <signal.h>

#define SCREEN_WIDTH 180
#define SCREEN_HEIGHT 24
#define MAX_DROPS 50
#define MIN_SPEED 1
#define MAX_SPEED 5
#define COLUMN_GAP 3  // 列间隔

typedef struct {
    int x, y;  // 坐标
    int speed; // 速度
    char symbol; // 符号
    char color; // 颜色
} Drop;

int interrupted = 0;

void sigint_handler(int signal) {
    printf("Ctrl+C pressed, stopping the loop.\n");
    interrupted = 1;
}

void clear_screen() {
    printf("\033[H\033[J");
}

void set_cursor_position(int x, int y) {
    printf("\033[%d;%dH", y, x);
}

void hide_cursor() {
    printf("\033[?25l");
}

void show_cursor() {
    printf("\033[?25h");
}

void set_text_color(char color) {
    printf("\033[1;%dm", color);
}

void reset_text_attributes() {
    printf("\033[0m");
}

void init_terminal() {
    hide_cursor();
    clear_screen();
}

void restore_terminal() {
    reset_text_attributes();
    show_cursor();
    clear_screen();
}

int random_int(int min, int max) {
    return min + rand() % (max - min + 1);
}

char random_char() {
    return (char)random_int(33, 126); // ASCII 可打印字符范围
}

char random_color() {
    return random_int(31, 36); // ANSI 色彩范围
}

void init_drop(Drop *drop, int column) {
    drop->x = column * (COLUMN_GAP + 1);  // 每列之间的间隔为 COLUMN_GAP
    drop->y = random_int(-SCREEN_HEIGHT, 0);
    drop->speed = random_int(MIN_SPEED, MAX_SPEED);
    drop->symbol = random_char();
    drop->color = random_color();
}

void update_drop(Drop *drop) {
    set_cursor_position(drop->x, drop->y);
    printf("%c", drop->symbol);

    // 产生新的随机字符
    drop->symbol = random_char();

    drop->y += drop->speed;

    // 如果雨滴超出屏幕，重新初始化它
    if (drop->y >= SCREEN_HEIGHT) {
        init_drop(drop, drop->x / (COLUMN_GAP + 1));  // 根据 x 坐标确定当前是第几列
    }
}

int main() {
    Drop drops[MAX_DROPS];

    srand(time(NULL));

    init_terminal();

    // 初始化雨滴
    for (int i = 0; i < MAX_DROPS; i++) {
        init_drop(&drops[i], i % ((SCREEN_WIDTH - 1) / (COLUMN_GAP + 1)));  // 初始化时根据列数分配
    }

    // 注册Ctrl+C信号的处理函数
    signal(SIGINT, sigint_handler);

    while (!interrupted) {
        for (int i = 0; i < MAX_DROPS; i++) {
            set_text_color(drops[i].color);
            update_drop(&drops[i]);
        }
        fflush(stdout);
        usleep(100000); // 延迟 100 毫秒
    }

    restore_terminal();
    clear_screen();

    return 0;
}
