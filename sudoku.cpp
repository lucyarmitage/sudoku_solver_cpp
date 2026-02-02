#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "sudoku.h"

using namespace std;

void load_board(const char* filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in) {
    cout << "Failed!\n";
  }
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << '\n';
  assert(row == 9);
}

/* internal helper function */
void print_frame(int row) {
  if (!(row % 3)) {
    cout << "  +===========+===========+===========+\n";
  } else {
    cout << "  +---+---+---+---+---+---+---+---+---+\n";
  }
}

/* internal helper function */
void print_row(const char* data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|\n";
}

/* function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) {
    cout << (char) ('1'+r) << "   ";
  }
  cout << '\n';
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}

/* function that returns true if the Sudoku board is complete */
bool is_complete(const char board[9][9]) {

    // iterates over every position in the board
    for (int row = 0; row < 9; row++) {
        for (int column = 0; column < 9; column++) {
            // if a position on board is empty, function returns false
            if (board[row][column] < '1' || board[row][column] > '9') {
                return false;
            }
        }
    }
    return true;
}

/* function to check whether a board position is within the valid Sudoku range*/
bool position_in_range(const char position[2]) {
    return position[0] >= 'A' && position[0] <= 'I'
        && position[1] >= '1' && position[1] <= '9';
}

/* function to check whether a digit character is valid for Sudoku */
bool digit_in_range(char digit) {
    return digit >= '1' && digit <= '9';
}

/* function to check whether a given square on the board is empty */
bool square_is_empty(const char board[9][9], int row, int column) {
    return board[row][column] == '.';
}

/* function to check whether a digit already exists in the specified row */
bool digit_in_row(const char board[9][9], int row, char digit) {
    for (int c = 0; c < 9; c++) {
        if (board[row][c] == digit) {
            return true;
        }
    }
    return false;
}

/* function to check whether a digit already exists in the specified column */
bool digit_in_column(const char board[9][9], int column, char digit) {
    for (int r = 0; r < 9; r++) {
        if (board[r][column] == digit) {
            return true;
        }
    }
    return false;
}

/* function to check whether a digit already exists in the 3x3 sub-grid */
bool digit_in_box(const char board[9][9], int row, int column, char digit) {
    int start_row = (row / 3) * 3;
    int start_column = (column / 3) * 3;

    for (int r = start_row; r < start_row + 3; r++) {
        for (int c = start_column; c < start_column + 3; c++) {
            if (board[r][c] == digit) {
                return true;
            }
        }
    }
    return false;
}

/* function to attempt to place a digit on the board at a given position */
bool make_move(const char position[2], char digit, char board[9][9]) {
    // check position and digit validity
    if (!position_in_range(position)) {
        return false;
    }

    if (!digit_in_range(digit)) {
        return false;
    }

    // convert position to indices
    int row = position[0] - 'A';
    int column = position[1] - '1';

    // check square is empty
    if (!square_is_empty(board, row, column)) {
        return false;
    }

    // check Sudoku constraints
    if (digit_in_row(board, row, digit)) {
        return false;
    }

    if (digit_in_column(board, column, digit)) {
        return false;
    }

    if (digit_in_box(board, row, column, digit)) {
        return false;
    }

    // make the move
    board[row][column] = digit;
    return true;
}

/* function to save the board to a file and check successful*/
bool save_board(const char filename[], const char board[9][9]) {

    // create and open output file stream
    ofstream out_stream;
    out_stream.open(filename);
    // returns false if file opening fails
    if (!out_stream) {
        return false;
    }

    // iterates through each board position and writes current digit to the file
    for (int row = 0; row < 9; row++) {
        for (int column = 0; column < 9; column++) {
            out_stream << board[row][column];
        }
        out_stream << '\n';
    }

    out_stream.close();
    // returns true if no errors occurred
    return !out_stream.fail();
}

/* function to recursively make moves until board is solved */
bool solve_board(char board[9][9], int& recursion_count) {

    // base case: board already complete
    if (is_complete(board)) {
        return true;
    }

    // increment recursion count each time function called
    recursion_count++;

    // loops through board positions
    for (char row = 'A'; row <= 'I'; row++) {
        for (char column = '1'; column <= '9'; column++) {
            char position[2] = { row, column };

            // checks if board position empty
            if (board[row - 'A'][column - '1'] == '.') {

                // loops through digits 1-9 and makes move if valid
                for (char digit = '1'; digit <= '9'; digit++) {
                    if (make_move(position, digit, board)) {

                        // recursively tries to solve rest of board
                        if (solve_board(board, recursion_count)) {
                            return true;
                        }

                        // backtrack if move doesn't lead to solution
                        board[row - 'A'][column - '1'] = '.';
                    }
                }

                // no valid digit fits in this empty square
                return false;
            }
        }
    }
    return true;
}

/* overloaded function to solve the board without outputting number of recursions */
bool solve_board(char board[9][9]) {

    int counter = 0;

    // calls function with a default counter
    return solve_board(board, counter);

}