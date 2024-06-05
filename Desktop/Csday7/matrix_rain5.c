#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <time.h>

#define WIDTH 80
#define HEIGHT 24
#define DENSITY 0.05
#define SPEED 15000
#define BLANK ' '

void hide_cursor() {
    printf("\033[?25l");
    fflush(stdout);
}

void show_cursor() {
    printf("\033[?25h");
    fflush(stdout);
}

void set_terminal_mode() {
    struct termios t;
    tcgetattr(0, &t);
    t.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(0, TCSANOW, &t);
}

void reset_terminal_mode() {
    struct termios t;
    tcgetattr(0, &t);
    t.c_lflag |= (ICANON | ECHO);
    tcsetattr(0, TCSANOW, &t);
}

void move_cursor(int x, int y) {
    printf("\033[%d;%dH", y, x);
    fflush(stdout);
}

void change_color(int color) {
    printf("\033[0;34m");  // 设置为蓝色
    fflush(stdout);
}

void fade_color() {
    for (int i = 44; i <= 47; i++) {
        printf("\033[0;%dm", i);  // 渐变颜色为蓝色
        fflush(stdout);
        usleep(50000);
    }
}

int main() {
    hide_cursor();
    set_terminal_mode();

    srand(time(NULL));

    char chars[WIDTH][HEIGHT];
    int positions[WIDTH] = {0};

    while (1) {
        for (int x = 0; x < WIDTH; x++) {
            if ((double)rand() / RAND_MAX < DENSITY) {
                if (positions[x] < HEIGHT) {
                    chars[x][positions[x]] = 'A' + rand() % 26; // 使用字母表示字符
                    positions[x]++;
                }
            }
            for (int y = 0; y < positions[x]; y++) {
                move_cursor(x, y);
                change_color(34); // 设置为蓝色
                putchar(chars[x][y]);
            }
        }

        usleep(SPEED);  // 控制下落速度

        for (int x = 0; x < WIDTH; x++) {
            for (int y = 0; y < positions[x]; y++) {
                move_cursor(x, y);
                putchar(BLANK);
            }
        }

        for (int x = 0; x < WIDTH; x++) {
            if (positions[x] > 0) {
                if (positions[x] == HEIGHT || (rand() / (double)RAND_MAX < 0.1)) {
                    fade_color(); // 渐变颜色为蓝色
                    positions[x]--;
                } else {
                    chars[x][positions[x]] = chars[x][positions[x]-1];
                }
            }
        }
    }

    reset_terminal_mode();
    show_cursor();

    return 0;
}
