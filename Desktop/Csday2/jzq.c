#include <stdio.h>

// 定义棋盘大小
#define SIZE 3

// 初始化棋盘
void initialize(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = ' ';
        }
    }
}

// 打印棋盘
void printBoard(char board[SIZE][SIZE]) {
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf(" %c ", board[i][j]);
            if (j != SIZE - 1) {
                printf("|");
            }
        }
        printf("\n");
        if (i != SIZE - 1) {
            printf("---+---+---\n");
        }
    }
    printf("\n");
}

// 检查是否有玩家赢得比赛
char checkWin(char board[SIZE][SIZE]) {
    // 检查每一行
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') {
            return board[i][0];
        }
    }
    // 检查每一列
    for (int j = 0; j < SIZE; j++) {
        if (board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[0][j] != ' ') {
            return board[0][j];
        }
    }
    // 检查对角线
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') {
        return board[0][0];
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ') {
        return board[0][2];
    }
    return ' ';
}

// 主函数
int main() {
    char board[SIZE][SIZE];
    char currentPlayer = 'X';
    int row, col;
    char winner = ' ';

    // 初始化棋盘
    initialize(board);

    // 游戏循环
    while (1) {
        // 打印当前棋盘
        printBoard(board);

        // 玩家输入行和列
        printf("玩家 %c，请输入行和列（例如：1 2）：", currentPlayer);
        scanf("%d %d", &row, &col);

        // 检查输入是否合法
        if (row < 1 || row > SIZE || col < 1 || col > SIZE || board[row-1][col-1] != ' ') {
            printf("输入无效，请重新输入。\n");
            continue;
        }

        // 更新棋盘
        board[row-1][col-1] = currentPlayer;

        // 检查是否有玩家获胜
        winner = checkWin(board);
        if (winner != ' ') {
            printf("恭喜玩家 %c 赢得比赛！\n", winner);
            printBoard(board);
            break;
        }

        // 切换玩家
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    return 0; 
}
