#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <time.h>

#define WIDTH 80
#define HEIGHT 24
#define DENSITY 0.05
#define SPEED 15000

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

int main() {
    hide_cursor();
    set_terminal_mode();

    srand(time(NULL));

    char chars[WIDTH][HEIGHT];
    int positions[WIDTH] = {0};

    // 设置终端背景颜色为绿色
    printf("\033[42m");
    fflush(stdout);

    while (1) {
        if ((double) rand() / RAND_MAX < DENSITY) {
            int x = rand() % WIDTH;
            if (positions[x] < HEIGHT) {
                chars[x][positions[x]] = ' ';
                positions[x]++;
            }
        }

        for (int x = 0; x < WIDTH; x++) {
            for (int y = positions[x] - 1; y >= 0; y--) {
                move_cursor(x + 1, y + 1);
                putchar(chars[x][y]);
                fflush(stdout);

                usleep(SPEED);

                move_cursor(x + 1, y + 1);
                putchar(' ');
                fflush(stdout);

                if (y == 0) {
                    positions[x]--;
                } else {
                    chars[x][y] = chars[x][y - 1];
                }
            }
        }
    }

    // 恢复终端背景颜色为默认
    printf("\033[49m");
    fflush(stdout);

    reset_terminal_mode();
    show_cursor();

    return 0;
}
