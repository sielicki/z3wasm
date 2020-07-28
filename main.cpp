#include <array>
#include <vector>
//#include <format>
#include "z3++.h"
#include <fmt/core.h>

using namespace z3;

void apply_standard_sudoku(context &c, solver &s,
                           std::vector<expr_vector> &board) {
  // assert uniqueness in each row, column, and ennearant
  for (auto i = 0; i < 9; i++) {
    expr_vector this_row(c);
    for (auto j = 0; j < 9; j++)
      this_row.push_back(board[i][j]);
    s.add(distinct(this_row));
  }
  for (auto j = 0; j < 9; j++) {
    expr_vector this_col(c);
    for (auto i = 0; i < 9; i++)
      this_col.push_back(board[i][j]);
    s.add(distinct(this_col));
  }
  for (auto ii = 0; ii < 3; ii++) {
    for (auto jj = 0; jj < 3; jj++) {
      expr_vector this_ennearant(c);
      for (auto i = 0; i < 3; i++) {
        for (auto j = 0; j < 3; j++) {
          this_ennearant.push_back(board[ii * 3 + i][jj * 3 + j]);
        }
      }
      s.add(distinct(this_ennearant));
    }
  }
}

std::vector<expr_vector> create_board(context &c, solver &s) {
  // create board of positive integer constants
  std::vector<expr_vector> board;
  for (auto i = 0; i < 9; i++) {
    board.push_back(expr_vector(c));
    for (auto j = 0; j < 9; j++)
      board[i].push_back(c.int_const(fmt::format("{}{}", i, j).c_str()));
  }
  for (auto k : board)
    for (auto i : k)
      s.add(i > 0 && i < 10);

  return board;
}

void sudoku() {
  context c;
  solver s(c);

  auto board = create_board(c, s);
  //apply_standard_sudoku(c, s, board);

  //std::cout << s << std::endl;
  //std::cout << s.to_smt2() << std::endl;

  int instance[9][9] = {
      {0, 0, 0, 0, 9, 4, 0, 3, 0}, {0, 0, 0, 5, 1, 0, 0, 0, 7},
      {0, 8, 9, 0, 0, 0, 0, 4, 0}, {0, 0, 0, 0, 0, 0, 2, 0, 8},
      {0, 6, 0, 2, 0, 1, 0, 5, 0}, {1, 0, 2, 0, 0, 0, 0, 0, 0},
      {0, 7, 0, 0, 0, 0, 5, 2, 0}, {9, 0, 0, 0, 6, 5, 0, 0, 0},
      {0, 4, 0, 9, 7, 0, 0, 0, 0}};

  for (auto i = 0; i < 9; i++)
    for (auto j = 0; j < 9; j++)
      if (instance[i][j] != 0)
        s.add(board[i][j] == instance[i][j]);

  //std::cout << "added instance reqs" << std::endl;
  auto res = s.check();
  //std::cout << res << std::cout;
  std::cout << "didn't get here? 1" << std::endl;

  switch (res) {
  case sat:
    std::cout << "sudoku is solvable\n";
    break;
  case unsat:
    std::cout << "sudoku is not solvable\n";
    break;
  case unknown:
    std::cout << "unknown\n";
    break;
  }
  std::cout << "didn't get here? 2" << std::endl;
}

int main() {
  sudoku();
  return 0;
}
