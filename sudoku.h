#ifndef SUDOKU_H
#define SUDOKU_H

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char* filename, char board[9][9]);

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]);

/* returns true if the Sudoku board is complete */
bool is_complete(const char board[9][9]);

/* attempts to place a digit on the board at a given position */
bool make_move(const char position[2], const char digit, char board[9][9]);

/* saves the board to a file and checks successful */
bool save_board(const char* filename, const char board[9][9]);

/* recursively makes moves until board is solved */
bool solve_board(char board[9][9], int& recursion_count);

/* overloaded function to solve the board without outputting number of recursions */
bool solve_board(char board[9][9]);

#endif