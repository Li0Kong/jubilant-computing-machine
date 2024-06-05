#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <time.h>

#define WIDTH 80
#define HEIGHT 24
#define DENSITY 0.05
#define SPEED 15000

struct falling_char {
    int x;
    int y;
    char c;
};

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

    struct falling_char chars[WIDTH * HEIGHT];
    int num_chars = 0;

    while (1) {
        if ((double) rand() / RAND_MAX < DENSITY) {
            struct falling_char new_char = {rand() % WIDTH, 0, ' '};
            chars[num_chars++] = new_char;
        }

        for (int i = 0; i < num_chars; i++) {
            struct falling_char *chr = &chars[i];
            if (chr->y >= HEIGHT) {
                chr->y = 0;
                chr->x = rand() % WIDTH;
            }

            move_cursor(chr->x, chr->y);
            printf("\033[32m%c\033[0m", chr->c); // 设置为绿色
            fflush(stdout);

            usleep(SPEED);

            move_cursor(chr->x, chr->y);
            putchar(' ');
            fflush(stdout);

            chr->y++;
        }
    }

    reset_terminal_mode();
    show_cursor();

    return 0;
}
