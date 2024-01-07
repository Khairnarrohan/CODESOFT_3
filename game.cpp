#include <iostream>
#include <vector>

using namespace std;

// Function prototypes
void displayBoard(const vector<vector<char>>& board);
bool makeMove(vector<vector<char>>& board, char player, int row, int col);
bool checkWin(const vector<vector<char>>& board, char player);
bool checkDraw(const vector<vector<char>>& board);
void switchPlayer(char& currentPlayer);

int main() {
    vector<vector<char>> board(3, vector<char>(3, ' '));  // Initialize empty 3x3 board
    char currentPlayer = 'X';

    do {
        displayBoard(board);

        // Player input
        int row, col;
        cout << "Player " << currentPlayer << ", enter your move (row and column): ";
        cin >> row >> col;

        // Make the move and check if it's valid
        if (makeMove(board, currentPlayer, row, col)) {
            // Check for win or draw
            if (checkWin(board, currentPlayer)) {
                displayBoard(board);
                cout << "Player " << currentPlayer << " wins! Congratulations!" << endl;
                break;
            } else if (checkDraw(board)) {
                displayBoard(board);
                cout << "It's a draw!" << endl;
                break;
            }

            // Switch to the other player
            switchPlayer(currentPlayer);
        } else {
            cout << "Invalid move! Try again." << endl;
        }

    } while (true);

    // Ask if players want to play again
    char playAgain;
    cout << "Do you want to play again? (y/n): ";
    cin >> playAgain;

    if (playAgain == 'y' || playAgain == 'Y') {
        // Reset the board for a new game
        board = vector<vector<char>>(3, vector<char>(3, ' '));
        main();  // Restart the game
    }

    return 0;
}

void displayBoard(const vector<vector<char>>& board) {
    cout << "  0 1 2" << endl;
    for (int i = 0; i < 3; ++i) {
        cout << i << " ";
        for (int j = 0; j < 3; ++j) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

bool makeMove(vector<vector<char>>& board, char player, int row, int col) {
    if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != ' ') {
        return false;  // Invalid move
    }

    board[row][col] = player;
    return true;
}

bool checkWin(const vector<vector<char>>& board, char player) {
    // Check rows, columns, and diagonals for a win
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
            return true;  // Row win
        }
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) {
            return true;  // Column win
        }
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) {
        return true;  // Diagonal win
    }
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) {
        return true;  // Diagonal win
    }

    return false;
}

bool checkDraw(const vector<vector<char>>& board) {
    // Check if the board is full
    for (const auto& row : board) {
        for (char cell : row) {
            if (cell == ' ') {
                return false;  // Game still ongoing
            }
        }
    }
    return true;  // Board is full, and it's a draw
}

void switchPlayer(char& currentPlayer) {
    // Switch between 'X' and 'O'
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}