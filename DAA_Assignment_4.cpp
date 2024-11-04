#include <iostream>
#include <vector>
using namespace std;

// Function to print the n-Queens matrix (solution)
void printSolution(const vector<vector<int>>& board, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << (board[i][j] == 1 ? "Q " : ". ");
        }
        cout << endl;
    }
}

// Function to check if a queen can be placed at board[row][col]
bool isSafe(const vector<vector<int>>& board, int row, int col, int N) {
    // Check the current column for conflicts
    for (int i = 0; i < row; i++) {
        if (board[i][col] == 1) {
            return false;
        }
    }

    // Check the upper-left diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 1) {
            return false;
        }
    }

    // Check the upper-right diagonal
    for (int i = row, j = col; i >= 0 && j < N; i--, j++) {
        if (board[i][j] == 1) {
            return false;
        }
    }

    return true;
}

// Function to solve the n-Queens problem using backtracking
bool solveNQueens(vector<vector<int>>& board, int row, int N) {
    // Base case: If all queens are placed, return true
    if (row >= N) {
        return true;
    }

    // Try placing a queen in each column of the current row
    for (int col = 0; col < N; col++) {
        if (isSafe(board, row, col, N)) {
            // Place the queen
            board[row][col] = 1;

            // Recur to place the next queen
            if (solveNQueens(board, row + 1, N)) {
                return true;
            }

            // If placing queen at board[row][col] does not lead to a solution,
            // remove the queen (backtrack)
            board[row][col] = 0;
        }
    }

    // If no place is found for the queen in the current row, return false
    return false;
}

// Function to set up the board with the first queen placed at a specified position
bool generateNQueens(int N, int row, int col) {
    vector<vector<int>> board(N, vector<int>(N, 0));

    // Place the first queen at the specified (row, col)
    board[row][col] = 1;

    // Solve the remaining N-1 queens problem starting from the next row
    if (!solveNQueens(board, row + 1, N)) {
        cout << "No solution exists.\n";
        return false;
    }

    // Print the final solution
    printSolution(board, N);
    return true;
}

int main() {
    int N, row, col;

    cout << "Enter the value of N (size of the board): ";
    cin >> N;

    cout << "Enter the position of the first queen (row and column): ";
    cin >> row >> col;

    // Check if the row and col are within the board limits
    if (row < 0 || row >= N || col < 0 || col >= N) {
        cout << "Invalid position for the first queen.\n";
        return 1;
    }

    // Generate the N-Queens solution with the first queen placed
    generateNQueens(N, row, col);

    return 0;
}
