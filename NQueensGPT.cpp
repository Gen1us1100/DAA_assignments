#include <iostream>
#include <vector>
#include <set>

// Function to print the solution board
void printSolution(const std::vector<std::vector<char>>& board) {
    for (const auto& row : board) {
        for (const auto& cell : row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// Backtracking function to solve N-Queens using sets for optimization
void solveNQueens(int row, int n, std::vector<std::vector<char>>& board,
                  std::set<int>& cols, std::set<int>& diag1, std::set<int>& diag2) {
    if (row == n) {
        printSolution(board);
        return;
    }

    for (int col = 0; col < n; col++) {
        if (cols.find(col) == cols.end() && diag1.find(row - col) == diag1.end() &&
            diag2.find(row + col) == diag2.end()) {
            // Place the queen
            board[row][col] = 'Q';
            cols.insert(col);
            diag1.insert(row - col);
            diag2.insert(row + col);

            // Recurse for the next row
            solveNQueens(row + 1, n, board, cols, diag1, diag2);

            // Backtrack and remove the queen
            board[row][col] = '.';
            cols.erase(col);
            diag1.erase(row - col);
            diag2.erase(row + col);
        }
    }
}

int main() {
    int n;
    std::cout << "Enter the value of N: ";
    std::cin >> n;

    // Initialize the board
    std::vector<std::vector<char>> board(n, std::vector<char>(n, '.'));
    std::set<int> cols;   // Columns where queens are placed
    std::set<int> diag1;  // Diagonal (row - col)
    std::set<int> diag2;  // Anti-diagonal (row + col)

    std::cout << "Solutions to the " << n << "-Queens problem:\n";
    solveNQueens(0, n, board, cols, diag1, diag2);

    return 0;
}

