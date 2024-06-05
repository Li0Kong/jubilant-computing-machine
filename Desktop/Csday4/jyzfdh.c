#include <stdio.h>
#include <unistd.h>

void clearScreen() {
    printf("\033[H\033[J"); // ANSI 转义码清空屏幕
}

int main() {
    const int numRows = 25; // 垂直方向行数
    const int delayMillis = 500 * 1000; // 每帧的延迟时间（以微秒为单位）

    for (int frame = 0; frame < numRows; frame++) {
        clearScreen();

        // 输出空行，模拟字符 'L' 的掉落
        for (int row = 0; row < frame; row++) {
            printf("\n");
        }

        // 输出字符 'L'
        printf("\033[36m%d\033[m\n",8);
        printf("\033[35m%d\033[m\n",8);
        printf("\033[34m%d\033[m\n",8);
        printf("\033[33m%d\033[m\n",8);
        printf("\033[32m%d\033[m",8);
        printf("\033[31m%d\033[m",8);
        printf("\033[35m%d\033[m",8);
        printf("\033[37m%d\033[m",8);
        printf("\033[36m%d\033[m\n",8);
        

        // 延迟一段时间，实现动画效果
        usleep(delayMillis);
    }

    return 0;
}
