#include <stdio.h>
#include <stdlib.h>

#define N 8

int board[N][N];

// Kiểm tra xem có thể đặt quân hậu vào vị trí (row, col) hay không
int isSafe(int row, int col) {
    int i, j;

    // Kiểm tra hàng ngang
    for (i = 0; i < col; i++) {
        if (board[row][i] == 1) {
            return 0;
        }
    }

    // Kiểm tra đường chéo trái trên
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 1) {
            return 0;
        }
    }

    // Kiểm tra đường chéo trái dưới
    for (i = row, j = col; i < N && j >= 0; i++, j--) {
        if (board[i][j] == 1) {
            return 0;
        }
    }

    return 1;
}

// Giải bài toán Tám quân hậu bằng thuật toán quay lui
int solveNQueens(int col) {
    if (col >= N) {
        return 1; // Đã đặt tất cả quân hậu thành công
    }

    for (int i = 0; i < N; i++) {
        if (isSafe(i, col)) {
            board[i][col] = 1; // Đặt quân hậu vào vị trí (i, col)

            if (solveNQueens(col + 1)) {
                return 1; // Tìm thấy lời giải
            }

            board[i][col] = 0; // Quay lui nếu không tìm được lời giải
        }
    }

    return 0; // Không tìm thấy lời giải
}

// In bàn cờ với các quân hậu đã được đặt
void printBoard() {
    printf("Lời giải của bài toán Tám quân hậu:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

int main() {
    // Khởi tạo bàn cờ
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            board[i][j] = 0;
        }
    }

    // Giải bài toán Tám quân hậu
    if (solveNQueens(0)) {
        printBoard();
    } else {
        printf("Không tìm thấy lời giải cho bài toán Tám quân hậu.\n");
    }

    return 0;
}