#include <iostream>
#include <vector>

using namespace std;

class SudokuSolver {
public:
    // Constructor accepts a 9x9 board (0 represents empty cells)
    SudokuSolver(vector<vector<int>> board) : board(board) {}

    // Solve the puzzle using backtracking
    bool solve() {
        int row, col;
        if (!findUnassignedLocation(row, col))
            return true; // Puzzle solved

        for (int num = 1; num <= 9; num++) {
            if (isSafe(row, col, num)) {
                board[row][col] = num;
                if (solve())
                    return true;
                board[row][col] = 0; // Backtrack
            }
        }
        return false; // Trigger backtracking
    }

    // Print the board to the console
    void printBoard() {
        for (int row = 0; row < 9; row++) {
            if (row % 3 == 0 && row != 0)
                cout << "---------------------\n";
            for (int col = 0; col < 9; col++) {
                if (col % 3 == 0 && col != 0)
                    cout << "| ";
                cout << board[row][col] << " ";
            }
            cout << "\n";
        }
    }

private:
    vector<vector<int>> board;

    // Find an unassigned cell; returns true if found and sets row and col
    bool findUnassignedLocation(int &row, int &col) {
        for (row = 0; row < 9; row++)
            for (col = 0; col < 9; col++)
                if (board[row][col] == 0)
                    return true;
        return false;
    }

    // Check if 'num' is already used in the given row
    bool usedInRow(int row, int num) {
        for (int col = 0; col < 9; col++)
            if (board[row][col] == num)
                return true;
        return false;
    }

    // Check if 'num' is already used in the given column
    bool usedInCol(int col, int num) {
        for (int row = 0; row < 9; row++)
            if (board[row][col] == num)
                return true;
        return false;
    }

    // Check if 'num' is used in the 3x3 box
    bool usedInBox(int boxStartRow, int boxStartCol, int num) {
        for (int row = 0; row < 3; row++)
            for (int col = 0; col < 3; col++)
                if (board[row + boxStartRow][col + boxStartCol] == num)
                    return true;
        return false;
    }

    // Determine if it’s safe to place 'num' at board[row][col]
    bool isSafe(int row, int col, int num) {
        return !usedInRow(row, num) &&
               !usedInCol(col, num) &&
               !usedInBox(row - row % 3, col - col % 3, num) &&
               board[row][col] == 0;
    }
};

int main() {
    vector<vector<int>> puzzle(9, vector<int>(9, 0));

    cout << "Enter the Sudoku puzzle:\n";
    cout << "Provide 9 lines with 9 numbers each (use 0 for empty cells).\n\n";

    // Read input from the user
    for (int i = 0; i < 9; i++) {
        cout << "Row " << i + 1 << ": ";
        for (int j = 0; j < 9; j++) {
            cin >> puzzle[i][j];
        }
    }

    SudokuSolver solver(puzzle);

    if (solver.solve()) {
        cout << "\nSudoku puzzle solved:\n";
        solver.printBoard();
    } else {
        cout << "\nNo solution exists for the provided puzzle.\n";
    }

    return 0;
}
