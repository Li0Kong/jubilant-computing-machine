#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

// 清空屏幕
void clearScreen() {
    system("clear");
}

// 设置光标位置
void setCursorPosition(int x, int y) {
    printf("\033[%d;%dH", y, x);
}

int main() {
    FILE* fp;
    char buf[150], add[100], ai[5];
    int i = 1, delay = 33000; // 延迟时间单位改为微秒
    clock_t stime = 0, ftime = 0;
    stime = clock();

    while (i <= 7) { // 修改为6帧
        if (i % 2 == 0) {
            delay = 43000;
        } else {
            delay = 33000;
        }

        sprintf(add, "C:/TXT/a (%d)", i); // 修改文件路径表示方法

        ftime = clock();
        if (ftime - stime >= delay) {
            fp = fopen(add, "r");
            if (NULL == fp) {
                // 处理文件打开失败情况
            } else {
                clearScreen(); // 清空屏幕
                while (fgets(buf, 150, fp)) {
                    printf("%s", buf);
                }
                fclose(fp);
                setCursorPosition(0, 0); // 设置光标位置
                i++;
                stime += delay;
            }
        }
    }

    return 0;
}
