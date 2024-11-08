#include<bits/stdc++.h>
using namespace std;

void printsol(vector<vector<int>>& board) {
    int n = board.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j]) {
                cout << "Q ";
            } else {
                cout << ". ";
            }
        }
        cout << endl;
    }
    cout << "\n*******************\n";
}

bool issafe(vector<vector<int>>& board, int row, int col) {
    int n = board.size();
    for (int i = 0; i < col; i++) {
        if (board[row][i]) {
            return false;
        }
    }
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j]) {
            return false;
        }
    }
    for (int i = row, j = col; i < n && j >= 0; i++, j--) {
        if (board[i][j]) {
            return false;
        }
    }
    return true;
}

void solve(vector<vector<int>>& board, int col, int& count) {
    int n = board.size();
    if (col >= n) {
        printsol(board);
        count++;
        return;
    }

    for (int i = 0; i < n; i++) {
        if (issafe(board, i, col)) {
            board[i][col] = 1;
            solve(board, col + 1, count);
            board[i][col] = 0;
        }
    }
}

void solveNQ(int n) {
    vector<vector<int>> board(n, vector<int>(n, 0)); 
    int count = 0;
    solve(board, 0, count);
    cout << "Total number of solutions: " << count << endl;
}

int main() {
    int n;
    cout << "Enter the value of n in matrix N x N: ";
    cin >> n;
    solveNQ(n);
    return 0;
}
