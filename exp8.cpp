#include <iostream>
using namespace std;

const int N = 4; // Define the size of the chessboard

// Function to print the board configuration
void printBoard(int board[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Function to check if a queen can be placed at board[row][col]
bool isSafe(int board[N][N], int row, int col) {
    // Check if there is a queen in the same column above
    for (int i = 0; i < row; i++) {
        if (board[i][col])
            return false;
    }

    // Check upper left diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j])
            return false;
    }

    // Check upper right diagonal
    for (int i = row, j = col; i >= 0 && j < N; i--, j++) {
        if (board[i][j])
            return false;
    }

    return true;
}

// Function to solve N-Queens problem using backtracking
bool solveNQueens(int board[N][N], int row) {
    // If all queens are placed, return true
    if (row >= N)
        return true;

    // Try placing queen in each column of the current row
    for (int col = 0; col < N; col++) {
        if (isSafe(board, row, col)) {
            // Place the queen
            board[row][col] = 1;

            // Recur to place the rest of the queens
            if (solveNQueens(board, row + 1))
                return true;

            // If placing queen in board[row][col] doesn't lead to a solution, backtrack
            board[row][col] = 0; // Backtrack
        }
    }

    // If no column is suitable in this row, return false
    return false;
}

int main() {
    int board[N][N] = { {0, 0, 0, 0},
                        {0, 0, 0, 0},
                        {0, 0, 0, 0},
                        {0, 0, 0, 0} };

    if (solveNQueens(board, 0)) {
        cout << "Solution found:" << endl;
        printBoard(board);
    } else {
        cout << "No solution exists for N=" << N << endl;
    }

    return 0;
}
