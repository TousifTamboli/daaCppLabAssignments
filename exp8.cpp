#include <iostream>
#include <vector>
using namespace std;

void addSolution(vector<vector<int>> &ans, vector<vector<int>> &board, int n) {
    vector<int> temp;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            temp.push_back(board[i][j]);
        }
    }
    ans.push_back(temp);
}

bool isSafe(int row, int col, vector<vector<int>> &board, int n) {
    
    //check for row
    for (int y = 0; y < col; y++) {
        if (board[row][y] == 1)
            return false;
    }

    //upar wali diagonal
    for (int x = row, y = col; x >= 0 && y >= 0; x--, y--) {
        if (board[x][y] == 1)
            return false;
    }

    // niche wala diagonal
    for (int x = row, y = col; x < n && y >= 0; x++, y--) {
        if (board[x][y] == 1)
            return false;
    }

    return true;
}

void solve(int col, vector<vector<int>> &ans, vector<vector<int>> &board, int n) {
    // Base case: If all queens are placed
    if (col == n) {
        addSolution(ans, board, n);
        return;
    }

    //ek baar solve kar lo baki recurssion kar lega
    for (int row = 0; row < n; row++) {
        if (isSafe(row, col, board, n)) {
            //queen rakhna safe hai?
            board[row][col] = 1;
            //agle column ke liye rakho
            solve(col + 1, ans, board, n);
            //backtrack // queen ko hatana padega 
            board[row][col] = 0; 
        }
    }
}

vector<vector<int>> nQueens(int n) {
    vector<vector<int>> board(n, vector<int>(n, 0)); // Initialize board
    vector<vector<int>> ans; // to store result
    solve(0, ans, board, n); // Start solving from the first column
    return ans;
}

int main() {
    int n = 4; // Fixed number of queens

    vector<vector<int>> solutions = nQueens(n);

    cout << "Total solutions for 4 queens: " << solutions.size() << endl;
    for (int i = 0; i < solutions.size(); i++) {
        cout << "Solution " << i + 1 << ":" << endl;
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                cout << solutions[i][j * n + k] << " ";
            }
            cout << endl;
        }
        cout << endl; 
    }

    return 0;
}
