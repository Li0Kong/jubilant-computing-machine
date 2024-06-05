#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

// 延时的时间（毫秒）
#define DELAY 100

int main() {
    initscr(); // 初始化 ncurses
    cbreak(); // 允许读取字符而不需要按下 Enter
    noecho(); // 禁止输入时显示字符
    curs_set(0); // 隐藏光标

    int rows, cols;
    getmaxyx(stdscr, rows, cols); // 获取终端的行数和列数

    srand(time(NULL)); // 随机种子

    // 使用循环来模拟字符掉落
    while (1) {
        int start_col = rand() % cols; // 随机选择列
        int ch = 'A' + (rand() % 26); // 随机选择字母 A-Z

        // 让字符从顶部到底部
        for (int row = 0; row < rows; row++) {
            mvaddch(row, start_col, ch); // 在指定位置显示字符
            refresh(); // 刷新屏幕
            napms(DELAY); // 延时

            // 清除当前行字符
            if (row > 0) {
                mvaddch(row - 1, start_col, ' ');
            }
        }

        // 清除最后一行的字符
        mvaddch(rows - 1, start_col, ' ');
        
        // 检查是否有键盘输入，如果有，退出循环
        timeout(0); // 不阻塞
        if (getch() != ERR) {
            break;
        }
    }

    endwin(); // 结束 ncurses
    return 0;
}
