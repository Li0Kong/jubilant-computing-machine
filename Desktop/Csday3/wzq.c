#include <stdio.h>
#include <stdbool.h>

#define SIZE 15

char board[SIZE][SIZE];

// 初始化棋盘
void initialize() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = ' ';
        }
    }
}

// 打印棋盘
void printBoard() {
    printf("\n  ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", i);
    }
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", i);
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

// 检查是否有玩家赢得比赛
bool checkWin(char player) {
    // 检查水平方向
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j <= SIZE - 5; j++) {
            bool win = true;
            for (int k = 0; k < 5; k++) {
                if (board[i][j + k] != player) {
                    win = false;
                    break;
                }
            }
            if (win) return true;
        }
    }

    // 检查垂直方向
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j <= SIZE - 5; j++) {
            bool win = true;
            for (int k = 0; k < 5; k++) {
                if (board[j + k][i] != player) {
                    win = false;
                    break;
                }
            }
            if (win) return true;
        }
    }

    // 检查主对角线方向
    for (int i = 0; i <= SIZE - 5; i++) {
        for (int j = 0; j <= SIZE - 5; j++) {
            bool win = true;
            for (int k = 0; k < 5; k++) {
                if (board[i + k][j + k] != player) {
                    win = false;
                    break;
                }
            }
            if (win) return true;
        }
    }

    // 检查副对角线方向
    for (int i = 0; i <= SIZE - 5; i++) {
        for (int j = SIZE - 1; j >= 4; j--) {
            bool win = true;
            for (int k = 0; k < 5; k++) {
                if (board[i + k][j - k] != player) {
                    win = false;
                    break;
                }
            }
            if (win) return true;
        }
    }

    return false;
}

// 主函数
int main() {
    initialize();
    printBoard();
    int row, col;
    char currentPlayer = 'X';
    bool gameOver = false;

    while (!gameOver) {
        printf("玩家 %c，请输入您要下棋的行和列（例如：1 2）：", currentPlayer);
        scanf("%d %d", &row, &col);

        if (row < 0 || row >= SIZE || col < 0 || col >= SIZE || board[row][col] != ' ') {
            printf("输入无效，请重新输入。\n");
            continue;
        }

        board[row][col] = currentPlayer;
        printBoard();

        if (checkWin(currentPlayer)) {
            printf("恭喜玩家 %c 赢得比赛！\n", currentPlayer);
            gameOver = true;
        } else {
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }

    return 0;
}
