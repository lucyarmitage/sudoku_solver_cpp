#include <iostream>
#include <cstdio>
#include "sudoku.h"

using namespace std;

int main() {

  char board[9][9];

  /* This section illustrates the use of the pre-supplied helper functions. */
  cout << "============= Pre-supplied functions =============\n\n";

  cout << "Calling load_board():\n";
  load_board("easy.dat", board);

  cout << '\n';
        cout << "Displaying Sudoku board with display_board():\n";
  display_board(board);
  cout << "Done!\n\n";

  cout << "=================== Question 1 ===================\n\n";

  load_board("easy.dat", board);
  cout << "Board is ";
  if (!is_complete(board)) {
    cout << "NOT ";
  }
  cout << "complete.\n\n";

  load_board("easy-solution.dat", board);
  cout << "Board is ";
  if (!is_complete(board)) {
    cout << "NOT ";
  }
  cout << "complete.\n\n";

  cout << "=================== Question 2 ===================\n\n";

  load_board("easy.dat", board);

  // Should be OK
  cout << "Putting '1' into I8 is ";
  if (!make_move("I8", '1', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:\n";
  display_board(board);

  // write more tests

  // Should be OK
  cout << "\nPutting '3' into B3 is ";
  if (!make_move("B3", '3', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:\n";
  display_board(board);  

  // All tests below should be invalid:
  cout << "\nPutting 'a' into I8 is ";       // 'a' not in range 1-9
  if (!make_move("I8", 'a', board)) {
    cout << "NOT ";
  }
  cout << "a valid move.\n";

  cout << "Putting '1' into J8 is ";        // 'J8' not in range of board
  if (!make_move("J8", '1', board)) {
    cout << "NOT ";
  }
  cout << "a valid move.\n";;

  cout << "Putting '6' into I8 is ";        // '6' already in same row
  if (!make_move("I8", '6', board)) {
    cout << "NOT ";
  }
  cout << "a valid move.\n";

  cout << "Putting '7' into I8 is ";        // '7' already in same column
  if (!make_move("I8", '7', board)) {
    cout << "NOT ";
  }
  cout << "a valid move.\n";

  cout << "Putting '9' into I8 is ";        // '9' already in same 3x3 grid
  if (!make_move("I8", '9', board)) {
    cout << "NOT ";
  }
  cout << "a valid move.\n\n";

  cout << "=================== Question 3 ===================\n\n";

  load_board("easy.dat", board);
  if (save_board("easy-copy.dat", board)) {
    cout << "Save board to 'easy-copy.dat' successful.\n";
  } else {
    cout << "Save board failed.\n";
  }
  cout << '\n';

  cout << "=================== Question 4 ===================\n\n";

  load_board("easy.dat", board);
  if (solve_board(board)) {
    cout << "The 'easy' board has a solution:\n";
    display_board(board);
  } else {
    cout << "A solution cannot be found.\n";
  }
  cout << '\n';

  load_board("medium.dat", board);
  if (solve_board(board)) {
    cout << "The 'medium' board has a solution:\n";
    display_board(board);
  } else {
    cout << "A solution cannot be found.\n";
  }
  cout << '\n';

  // write more tests

  load_board("mystery1.dat", board);
  if (solve_board(board)) {
    cout << "The 'mystery 1' board has a solution:\n";
    display_board(board);
  } else {
    cout << "A solution cannot be found for mystery 1.\n";
  }
  cout << '\n';

  load_board("mystery2.dat", board);
  if (solve_board(board)) {
    cout << "The 'mystery 2' board has a solution:\n";
    display_board(board);
  } else {
    cout << "A solution cannot be found for mystery 2.\n";
  }
  cout << '\n';

  load_board("mystery3.dat", board);
  if (solve_board(board)) {
    cout << "The 'mystery 3' board has a solution:\n";
    display_board(board);
  } else {
    cout << "A solution cannot be found for mystery 3.\n";
  }
  cout << '\n';
  
  cout << "=================== Question 5 ===================\n\n";

  // write more tests

  int recursion_count = 0;
  load_board("mystery1.dat", board);
  if (solve_board(board, recursion_count)) {
    cout << "Mystery 1 solved in " << recursion_count << " recursions!\n";
  } else {
    cout << "No solution exists for Mystery 1.\n";
    }

  recursion_count = 0;
  load_board("mystery2.dat", board);
  if (solve_board(board, recursion_count)) {
    cout << "Mystery 2 solved in " << recursion_count << " recursions!\n";
  } else {
    cout << "No solution exists for Mystery 2.\n";
  }

  recursion_count = 0;
  load_board("mystery3.dat", board);
  if (solve_board(board, recursion_count)) {
    cout << "Mystery 3 solved in " << recursion_count << " recursions!\n\n";
  } else {
    cout << "No solution exists for Mystery 3.\n\n";
  }

  return 0;
}
