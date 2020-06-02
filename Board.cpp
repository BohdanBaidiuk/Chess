#pragma once
#include "Board.hpp"
#include "Figura.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
namespace {
constexpr int SIZE = 8;
const int vertical_coordinate_line[SIZE]{1, 2, 3, 4, 5, 6, 7, 8};
const char horizontal_coordinate_line[SIZE]{'a', 'b', 'c', 'd',
                                            'e', 'f', 'g', 'h'};
const char empty_figure[]{"  "};
const size_t frame_drawing_constant_1 = 23;
const size_t frame_drawing_constant_2 = 15;
enum ASCII_CHESS_CODE : unsigned char {
  VERTICAL_LINE = 179,
  DOUBLE_VERTICAL_LINE = 186,
  TOP_RIGHT_CORNER = 187,
  BOTTOM_RIGHT_CORNER = 188,
  HORISONTAL_LINE = 196,
  BOTTOM_LEFT_CORNER = 200,
  TOP_LEFT_CORNER = 201,
  DOUBLE_HORISONTAL_LINE = 205,
};
bool step_white_king = true;
bool step_black_king = true;
bool step_left_white_rook = true;
bool step_right_white_rook = true;
bool step_left_black_rook = true;
bool step_right_black_rook = true;
bool flag_to_exit_chess = false;
bool turn_players = true;
enum { CHECK = 1, CHECKMATE };
bool checkand_check_flag = false;

} // namespace

void Board::draw_white_piece() {
  mFigures.emplace(FigurePoint(0, 0), ChessPiece{ROOK, WHITE});
  mFigures.emplace(FigurePoint(0, 1), ChessPiece{KNIGHT, WHITE});
  mFigures.emplace(FigurePoint(0, 2), ChessPiece{BISHOP, WHITE});
  mFigures.emplace(FigurePoint(0, 3), ChessPiece{QUEEN, WHITE});
  mFigures.emplace(FigurePoint(0, 4), ChessPiece{KING, WHITE});
  mFigures.emplace(FigurePoint(0, 5), ChessPiece{BISHOP, WHITE});
  mFigures.emplace(FigurePoint(0, 6), ChessPiece{KNIGHT, WHITE});
  mFigures.emplace(FigurePoint(0, 7), ChessPiece{ROOK, WHITE});
  mFigures.emplace(FigurePoint(1, 0), ChessPiece{PAWN, WHITE});
  mFigures.emplace(FigurePoint(1, 1), ChessPiece{PAWN, WHITE});
  mFigures.emplace(FigurePoint(1, 2), ChessPiece{PAWN, WHITE});
  mFigures.emplace(FigurePoint(1, 3), ChessPiece{PAWN, WHITE});
  mFigures.emplace(FigurePoint(1, 4), ChessPiece{PAWN, WHITE});
  mFigures.emplace(FigurePoint(1, 5), ChessPiece{PAWN, WHITE});
  mFigures.emplace(FigurePoint(1, 6), ChessPiece{PAWN, WHITE});
  mFigures.emplace(FigurePoint(1, 7), ChessPiece{PAWN, WHITE});
}

void Board::draw_black_piece() {
  mFigures.emplace(FigurePoint(6, 0), ChessPiece{PAWN, BLACK});
  mFigures.emplace(FigurePoint(6, 1), ChessPiece{PAWN, BLACK});
  mFigures.emplace(FigurePoint(6, 2), ChessPiece{PAWN, BLACK});
  mFigures.emplace(FigurePoint(6, 3), ChessPiece{PAWN, BLACK});
  mFigures.emplace(FigurePoint(6, 4), ChessPiece{PAWN, BLACK});
  mFigures.emplace(FigurePoint(6, 5), ChessPiece{PAWN, BLACK});
  mFigures.emplace(FigurePoint(6, 6), ChessPiece{PAWN, BLACK});
  mFigures.emplace(FigurePoint(6, 7), ChessPiece{PAWN, BLACK});
  mFigures.emplace(FigurePoint(7, 0), ChessPiece{ROOK, BLACK});
  mFigures.emplace(FigurePoint(7, 1), ChessPiece{KNIGHT, BLACK});
  mFigures.emplace(FigurePoint(7, 2), ChessPiece{BISHOP, BLACK});
  mFigures.emplace(FigurePoint(7, 3), ChessPiece{QUEEN, BLACK});
  mFigures.emplace(FigurePoint(7, 4), ChessPiece{KING, BLACK});
  mFigures.emplace(FigurePoint(7, 5), ChessPiece{BISHOP, BLACK});
  mFigures.emplace(FigurePoint(7, 6), ChessPiece{KNIGHT, BLACK});
  mFigures.emplace(FigurePoint(7, 7), ChessPiece{ROOK, BLACK});
}

void Board::draw_none_piece() {
  const size_t constant_number_start_of_the_cycle_one = 2;
  const size_t constant_number_finish_of_the_cycle_one = 6;
  const size_t constant_number_start_of_the_cycle_two = 0;
  const size_t constant_number_finish_of_the_cycle_two = 8;
  for (size_t i = constant_number_start_of_the_cycle_one;
       i < constant_number_finish_of_the_cycle_one; ++i) {
    for (size_t j = constant_number_start_of_the_cycle_two;
         j < constant_number_finish_of_the_cycle_two; ++j) {
      Type type = EMPTY;
      Color color = NONE;
      FigurePoint none_figure_position{i, j};
      ChessPiece none_chess_piece{type, color};
      mFigures.emplace(std::move(none_figure_position),
                       std::move(none_chess_piece));
    }
  }
};
void Board::draws_started_figurines_on_the_board() {
  draw_white_piece();
  draw_black_piece();
  draw_none_piece();
}

const char *draw_name_figure(ChessPiece figure) {
  const size_t SIZE_ARRAY = 6;
  const char *array[][SIZE_ARRAY]{{"WK", "WQ", "WB", "WN", "WR", "WP"},
                                  {"BK", "BQ", "BB", "BN", "BR", "BP"}};
  if (figure.get_type() == EMPTY) {
    return empty_figure;
  }
  return array[figure.get_color()][figure.get_type()];
}

void Board::show_map() {
  std::cout << "\t  White\n";
  std::cout << "  ";
  for (size_t i = 0; i < SIZE; ++i) {
    std::cout << horizontal_coordinate_line[i] << "  ";
  }
  std::cout << std::endl;
  std::cout << " " << TOP_LEFT_CORNER; // ASCII_CHESS_CODE::
  for (size_t i = 0; i < frame_drawing_constant_1; ++i) {
    std::cout << DOUBLE_HORISONTAL_LINE;
  }
  std::cout << TOP_RIGHT_CORNER << "\n";
  for (size_t i = 0, k = 0; i < frame_drawing_constant_2; ++i) {
    if (i % 2 != 0) {
      std::cout << " ";
      ++k;
    } else {
      std::cout << vertical_coordinate_line[k];
    }
    std::cout << DOUBLE_VERTICAL_LINE;
    for (int j = 0; j < SIZE; ++j) {
      if (i % 2 == 0) {
        std::cout << draw_name_figure(mFigures[(FigurePoint(k, j))]);
      } else {
        std::cout << HORISONTAL_LINE << HORISONTAL_LINE;
      }
      if (j < 7) {
        std::cout << VERTICAL_LINE;
      }
      if (j == 7) {
        std::cout << DOUBLE_VERTICAL_LINE;
      }
    }
    if (i % 2 == 0) {
      std::cout << vertical_coordinate_line[k];
    }
    std::cout << std::endl;
  }
  std::cout << " " << BOTTOM_LEFT_CORNER;
  for (size_t i = 0; i < frame_drawing_constant_1; ++i) {
    std::cout << DOUBLE_HORISONTAL_LINE;
  }
  std::cout << BOTTOM_RIGHT_CORNER << "\n";
  std::cout << "  ";
  for (size_t i = 0; i < SIZE; ++i) {
    std::cout << horizontal_coordinate_line[i] << "  ";
  }
  std::cout << std::endl;
  std::cout << "\t  Black\n";
}

void figure_replacement(ChessPiece &figure_one, ChessPiece &figure_two) {
  if (figure_one.get_color() != figure_two.get_color()) {
    std::swap(figure_one, figure_two);
    figure_one.clean_figure();
  }
};

void castling_swap(ChessPiece &figure_one, ChessPiece &figure_two) {
  std::swap(figure_one, figure_two);
}

void castling_king(std::map<FigurePoint, ChessPiece> &mFigures,
                   ChessPiece &figure_one, ChessPiece &figure_two,
                   const FigurePoint &figure_point1,
                   const FigurePoint &figure_point2) {
  const auto [x2, y2] = figure_point2;
  const auto [x1, y1] = figure_point1;
  FigurePoint full_figure_for_king{};
  FigurePoint full_figure_for_rook{};
  if (figure_one.get_color() == WHITE && step_white_king == true) {
    if (x2 == 0 && y2 == 0 && step_left_white_rook == true) {
      full_figure_for_king.first = 0;
      full_figure_for_king.second = 2;
      full_figure_for_rook.first = 0;
      full_figure_for_rook.second = 3;
    } else if (x2 == 0 && y2 == 7 && step_right_white_rook == true) {
      full_figure_for_king.first = 0;
      full_figure_for_king.second = 6;
      full_figure_for_rook.first = 0;
      full_figure_for_rook.second = 5;
    }
  } else if (figure_one.get_color() == BLACK && step_black_king == true) {
    if (x2 == 7 && y2 == 0 && step_left_black_rook == 0) {
      full_figure_for_king.first = 7;
      full_figure_for_king.second = 2;
      full_figure_for_rook.first = 7;
      full_figure_for_rook.second = 3;
    } else if (x2 == 7 && y2 == 7 && step_right_black_rook == true) {
      full_figure_for_king.first = 7;
      full_figure_for_king.second = 6;
      full_figure_for_rook.first = 7;
      full_figure_for_rook.second = 5;
    }
  }
  castling_swap(mFigures[figure_point1], mFigures[full_figure_for_king]);
  castling_swap(mFigures[figure_point2], mFigures[full_figure_for_rook]);
  std::cout << "You did the castling\n";
}

bool move_king_figure(std::map<FigurePoint, ChessPiece> &mFigures,
                      const FigurePoint &figure_point1,
                      const FigurePoint &figure_point2) {
  auto [x1, y1] = figure_point1;
  auto [x2, y2] = figure_point2;
  int variable_to_delete_characterX =
      x1 - 1; // this variable to remove the character to correctly check the
              // coordinates along the axis X
  int variable_to_delete_characterY =
      y1 - 1; // this variable to remove the character to correctly check the
              // coordinates along the axis Y
  if (mFigures[figure_point1].get_color() == WHITE && step_white_king == true) {
    castling_king(mFigures, mFigures[figure_point1], mFigures[figure_point2],
                  figure_point1, figure_point2);
    step_white_king = false;
    return true;
  } else if (mFigures[figure_point1].get_color() == BLACK &&
             step_black_king == true) {
    castling_king(mFigures, mFigures[figure_point1], mFigures[figure_point2],
                  figure_point1, figure_point2);
    step_black_king = false;
    return true;
  }
  // this if checks the correct move of the King
  if (((x1 + 1) == x2 && y1 == y2) ||
      (x1 == x2 && ((y1 + 1) == y2) || ((x1 + 1) == x2 && (y1 + 1) == y2) ||
       ((x1 + 1) == x2 && std::abs(variable_to_delete_characterY) == y2) ||
       ((x1 == x2) && std::abs(variable_to_delete_characterY) == y2) ||
       (std::abs(variable_to_delete_characterX) == x2 &&
        std::abs(variable_to_delete_characterY) == y2) ||
       (std::abs(variable_to_delete_characterX) == x2 && y1 == y2) ||
       (std::abs(variable_to_delete_characterX) == x2 && (y1 + 1) == y2))) {
    // this if checks the color of the king and the possibility of castling
    figure_replacement(mFigures[figure_point1], mFigures[figure_point2]);
    if (mFigures[figure_point1].get_color() == WHITE) {
      step_white_king = false;
    } else {
      step_black_king = false;
    }
    return true;
  }
  std::cout << "Error: The King walks in all directions but only for 1 step \n";
  return false;
}

bool move_queen_figure(std::map<FigurePoint, ChessPiece> &mFigures,
                       const FigurePoint &figure_point1,
                       const FigurePoint &figure_point2) {
  auto [x1, y1] = figure_point1;
  auto [x2, y2] = figure_point2;
  int variable_to_delete_characterX =
      x1 - x2; // this variable to remove the character to correctly check the
               // coordinates along the axis X
  int variable_to_delete_characterY =
      y1 - y2; // this variable to remove the character to correctly check the
               // coordinates along the axis Y
  // this if checks the correct move of the Queen
  if ((x2 <= 7 && y1 == y2) || (y2 <= 7 && x1 == x2) ||
      (std::abs(variable_to_delete_characterX)) ==
          std::abs(variable_to_delete_characterY)) {
    figure_replacement(mFigures[figure_point1], mFigures[figure_point2]);
    return true;
  }

  std::cout << "Error: Queen walks in straight lines and diagonally for the "
               "entire distance of the board\n";
  return false;
}

bool move_bishop_figure(std::map<FigurePoint, ChessPiece> &mFigures,
                        const FigurePoint &figure_point1,
                        const FigurePoint &figure_point2) {
  auto [x1, y1] = figure_point1;
  auto [x2, y2] = figure_point2;
  int variable_to_delete_characterX =
      x1 - x2; // this variable to remove the character to correctly check the
               // coordinates along the axis X
  int variable_to_delete_characterY =
      y1 - y2; // this variable to remove the character to correctly check the
               // coordinates along the axis Y
  // this if checks the correct move of the Bishop
  if ((std::abs(variable_to_delete_characterX)) ==
      std::abs(variable_to_delete_characterY)) {
    figure_replacement(mFigures[figure_point1], mFigures[figure_point2]);
    return true;
  }

  std::cout << "Error: Bishop walks diagonally\n";
  return false;
}

bool move_knight_figure(std::map<FigurePoint, ChessPiece> &mFigures,
                        const FigurePoint &figure_point1,
                        const FigurePoint &figure_point2) {
  auto [x1, y1] = figure_point1;
  auto [x2, y2] = figure_point2;
  // this if checks the correct move of the Knight
  if (((x1 + 2) == x2 && (y1 - 1) == y2) ||
      ((x1 + 2) == x2 && (y1 + 1) == y2) ||
      ((x1 - 2) == x2 && (y1 + 1) == y2) ||
      ((x1 - 2) == x2 && (y1 - 1) == y2) ||
      ((x1 - 1) == x2 && (y1 + 2) == y2) ||
      ((x1 - 1) == x2 && (y1 - 2) == y2) ||
      ((x1 + 1) == x2 && (y1 - 2) == y2) ||
      ((x1 + 1) == x2 && (y1 + 2) == y2)) {
    figure_replacement(mFigures[figure_point1], mFigures[figure_point2]);
    return true;
  }

  std::cout << "Error: Knight is a cheater, he walks through figures and does "
               "not walk along straight lines and diagonals \n";
  return false;
}

bool move_rook_figure(std::map<FigurePoint, ChessPiece> &mFigures,
                      const FigurePoint &figure_point1,
                      const FigurePoint &figure_point2) {
  auto [x1, y1] = figure_point1;
  auto [x2, y2] = figure_point2;
  // this if checks the correct move of the Rook
  if ((x2 <= 7 && y1 == y2) || (y2 <= 7 && x1 == x2)) {
    // this if checks the possibility of castling
    if (x1 == 0 && y1 == 0) {
      step_left_white_rook = false;
    } else if (x1 == 0 && y1 == 7) {
      step_right_white_rook = false;
    } else if (x1 == 7 && y1 == 0) {
      step_left_black_rook = false;
    } else if (x1 == 7 && y1 == 7) {
      step_right_black_rook = false;
    }
    figure_replacement(mFigures[figure_point1], mFigures[figure_point2]);
    return true;
  }
  std::cout << "Error: Rook walks only in straight lines for the entire "
               "distance of the board\n";
  return false;
}

bool move_pawn_figure(std::map<FigurePoint, ChessPiece> &mFigures,
                      const FigurePoint &figure_point1,
                      const FigurePoint &figure_point2) {
  auto [x1, y1] = figure_point1;
  auto [x2, y2] = figure_point2;
  auto color_figure_1 = mFigures[figure_point1].get_color();
  auto color_figure_2 = mFigures[figure_point2].get_color();
  int variable_for_choosing_code_validity_one =
      color_figure_1 == WHITE
          ? 1
          : 6; // this variable so as not to write additional checks
  int variable_for_choosing_code_validity_two =
      color_figure_1 == WHITE
          ? 3
          : 4; // this variable so as not to write additional checks
  int pawn_color_check = color_figure_1 == Color::WHITE ? 1 : -1;
  // this if checks the correct move of the Pawn
  if (((x1 + pawn_color_check) == x2 && y1 == y2) ||
      ((x1 == variable_for_choosing_code_validity_one) &&
       x2 == variable_for_choosing_code_validity_two && y1 == y2)) {
    if (color_figure_2 == NONE) {
      figure_replacement(mFigures[figure_point1], mFigures[figure_point2]);
      return true;
    }
  }
  // this if checks possibility of attack of white piece
  else if (((x1 + 1) == x2 && (y1 + 1) == y2) ||
           ((x1 + 1) == x2 && (y1 - 1) == y2)) {
    if (color_figure_1 != color_figure_2) {
      figure_replacement(mFigures[figure_point1], mFigures[figure_point2]);
      return true;
    }
  }
  // this if checks possibility of attack of black piece
  else if ((((x1 - 1) == x2 && (y1 + 1) == y2) ||
            ((x1 - 1) == x2 && (y1 - 1) == y2))) {
    if (color_figure_1 != color_figure_2) {
      figure_replacement(mFigures[figure_point1], mFigures[figure_point2]);
      return true;
    }
  }
  std::cout << "Error: Pawn walks only in front one square, and attacks "
               "diagonally on one square\n";
  return false;
}

bool Board::checking_the_correctness_of_moves_of_pieces(
    FigurePoint first_coordinates, FigurePoint second_coordinates) {

  const auto &start_coordinates = mFigures.at(first_coordinates);
  const auto &finish_coordinates = mFigures.at(second_coordinates);
  if (start_coordinates.get_color() == finish_coordinates.get_color() &&
      start_coordinates.get_type() != KING) {
    std::cout << "Error: You can’t walk on your color figures\n";
    return false;
  }
  if (checking_for_pieces_between_coordinates(first_coordinates,
                                              second_coordinates)) {
    std::cout << "Error: A piece cannot walk through the pieces\n";
    return false;
  }
  auto type_start_figure = start_coordinates.get_type();
  switch (Type(type_start_figure)) {
  case KING:
    if (!move_king_figure(mFigures, first_coordinates, second_coordinates)) {
      return false;
    }
    break;
  case QUEEN:
    if (!move_queen_figure(mFigures, first_coordinates, second_coordinates)) {
      return false;
    }
    break;
  case BISHOP:
    if (!move_bishop_figure(mFigures, first_coordinates, second_coordinates)) {
      return false;
    }
    break;
  case KNIGHT:
    if (!move_knight_figure(mFigures, first_coordinates, second_coordinates)) {
      return false;
    }
    break;
  case ROOK:
    if (!move_rook_figure(mFigures, first_coordinates, second_coordinates)) {
      return false;
    }
    break;
  case PAWN:
    if (!move_pawn_figure(mFigures, first_coordinates, second_coordinates)) {
      return false;
    }
    break;
  case EMPTY:
    break;
  default:
    break;
  }
  return true;
}

// These functions are checked for the presence of a check or checkmate to the
// King
bool check_of_the_check_in_a_straight_descending_line_y(
    std::map<FigurePoint, ChessPiece> mFigures, FigurePoint king_coordinates) {
  auto [x_king, y_king] = king_coordinates;
  auto figure_positin = mFigures.find(FigurePoint(x_king, y_king));
  if (figure_positin == mFigures.end()) {
    return false;
  }
  const auto king_color = figure_positin->second.get_color();
  if (y_king == 0) {
    return false;
  }
  for (int i = y_king - 1; i >= 0; --i) {
    if (mFigures[FigurePoint(x_king, i)].get_color() == king_color) {
      return false;
    } else if (mFigures[FigurePoint(x_king, i)].get_type() != EMPTY &&
               mFigures[FigurePoint(x_king, i)].get_color() != king_color) {
      if (mFigures[FigurePoint(x_king, i)].get_type() == ROOK ||
          mFigures[FigurePoint(x_king, i)].get_type() == QUEEN) {
        return true;
      }
      return false;
    }
  }
  return false;
}

bool check_of_the_check_in_a_straight_ascending_line_y(
    std::map<FigurePoint, ChessPiece> mFigures, FigurePoint king_coordinates) {
  auto [x_king, y_king] = king_coordinates;
  auto figure_positin = mFigures.find(FigurePoint(x_king, y_king));
  if (figure_positin == mFigures.end()) {
    return false;
  }
  const auto king_color = figure_positin->second.get_color();
  if (y_king == 7) {
    return false;
  }
  for (size_t i = y_king + 1; i < 8; ++i) {
    if (mFigures[FigurePoint(x_king, i)].get_type() != EMPTY &&
        mFigures[FigurePoint(x_king, i)].get_color() == king_color) {
      return false;
    } else if (mFigures[FigurePoint(x_king, i)].get_type() != EMPTY &&
               mFigures[FigurePoint(x_king, i)].get_color() != king_color) {
      if (mFigures[FigurePoint(x_king, i)].get_type() == ROOK ||
          mFigures[FigurePoint(x_king, i)].get_type() == QUEEN) {
        return true;
      }
      return false;
    }
  }
  return false;
}

bool check_of_the_check_in_a_straight_descending_line_x(
    std::map<FigurePoint, ChessPiece> mFigures, FigurePoint king_coordinates) {
  auto [x_king, y_king] = king_coordinates;
  auto figure_positin = mFigures.find(FigurePoint(x_king, y_king));
  if (figure_positin == mFigures.end()) {
    return false;
  }
  const auto king_color = figure_positin->second.get_color();
  if (x_king == 0) {
    return false;
  }
  for (int i = x_king - 1; i >= 0; --i) {
    if (mFigures[FigurePoint(i, y_king)].get_type() != EMPTY &&
        mFigures[FigurePoint(i, y_king)].get_color() == king_color) {
      return false;
    } else if (mFigures[FigurePoint(i, y_king)].get_type() != EMPTY &&
               mFigures[FigurePoint(i, y_king)].get_color() != king_color) {
      if (mFigures[FigurePoint(i, y_king)].get_type() == ROOK ||
          mFigures[FigurePoint(i, y_king)].get_type() == QUEEN) {
        return true;
      }
      return false;
    }
  }
  return false;
}

bool check_of_the_check_in_a_straight_ascending_line_x(
    std::map<FigurePoint, ChessPiece> mFigures, FigurePoint king_coordinates) {
  auto [x_king, y_king] = king_coordinates;
  auto figure_positin = mFigures.find(FigurePoint(x_king, y_king));
  if (figure_positin == mFigures.end()) {
    return false;
  }
  const auto king_color = figure_positin->second.get_color();
  if (x_king == 7) {
    return false;
  }
  for (size_t i = x_king + 1; i < 8; ++i) {
    if (mFigures[FigurePoint(i, y_king)].get_type() != EMPTY &&
        mFigures[FigurePoint(i, y_king)].get_color() == king_color) {
      return false;
    } else if (mFigures[FigurePoint(i, y_king)].get_type() != EMPTY &&
               mFigures[FigurePoint(i, y_king)].get_color() != king_color) {
      if (mFigures[FigurePoint(i, y_king)].get_type() == ROOK ||
          mFigures[FigurePoint(i, y_king)].get_type() == QUEEN) {
        return true;
      }
      return false;
    }
  }
  return false;
}

bool check_the_check_on_the_first_diagonal_from_left_to_right(
    std::map<FigurePoint, ChessPiece> mFigures, FigurePoint king_coordinates) {
  auto [x_king, y_king] = king_coordinates;
  auto figure_positin = mFigures.find(FigurePoint(x_king, y_king));
  if (figure_positin == mFigures.end()) {
    return false;
  }
  const auto king_color = figure_positin->second.get_color();
  if (x_king == 7 || y_king == 7) {
    return false;
  }
  for (size_t i = x_king + 1, j = y_king + 1; i < 8 && j < 8; ++i, ++j) {
    if (mFigures[FigurePoint(i, j)].get_type() != EMPTY &&
        mFigures[FigurePoint(i, j)].get_color() == king_color) {
      return false;
    } else if (mFigures[FigurePoint(i, j)].get_type() != EMPTY &&
               mFigures[FigurePoint(i, j)].get_color() != king_color) {
      if (mFigures[FigurePoint(i, j)].get_type() == BISHOP ||
          mFigures[FigurePoint(i, j)].get_type() == QUEEN) {
        return true;
      }
      return false;
    }
  }
  return false;
}

bool check_the_check_on_the_first_diagonal_from_right_to_left(
    std::map<FigurePoint, ChessPiece> mFigures, FigurePoint king_coordinates) {
  auto [x_king, y_king] = king_coordinates;
  auto figure_positin = mFigures.find(FigurePoint(x_king, y_king));
  if (figure_positin == mFigures.end()) {
    return false;
  }
  const auto king_color = figure_positin->second.get_color();
  if (x_king == 0 || y_king == 0) {
    return false;
  }
  for (size_t i = x_king - 1, j = y_king - 1; i >= 0 && j >= 0; --i, --j) {
    if (mFigures[FigurePoint(i, j)].get_type() != EMPTY &&
        mFigures[FigurePoint(i, j)].get_color() == king_color) {

      return false;
    } else if (mFigures[FigurePoint(i, j)].get_type() != EMPTY &&
               mFigures[FigurePoint(i, j)].get_color() != king_color) {
      if (mFigures[FigurePoint(i, j)].get_type() == BISHOP ||
          mFigures[FigurePoint(i, j)].get_type() == QUEEN) {
        return true;
      }
      return false;
    }
  }
  return false;
}

bool check_the_check_on_the_second_diagonal_from_right_to_left(
    std::map<FigurePoint, ChessPiece> mFigures, FigurePoint king_coordinates) {
  auto [x_king, y_king] = king_coordinates;
  auto figure_positin = mFigures.find(FigurePoint(x_king, y_king));
  if (figure_positin == mFigures.end()) {
    return false;
  }
  const auto king_color = figure_positin->second.get_color();
  if (x_king == 0 || y_king == 7) {
    return false;
  }
  for (size_t i = x_king - 1, j = y_king + 1; i >= 0 && j < 8; --i, ++j) {
    if (mFigures[FigurePoint(i, j)].get_type() != EMPTY &&
        mFigures[FigurePoint(i, j)].get_color() == king_color) {
      return false;
    } else if (mFigures[FigurePoint(i, j)].get_type() != EMPTY &&
               mFigures[FigurePoint(i, j)].get_color() != king_color) {
      if (mFigures[FigurePoint(i, j)].get_type() == BISHOP ||
          mFigures[FigurePoint(i, j)].get_type() == QUEEN) {
        return true;
      }
      return false;
    }
  }
  return false;
}

bool check_the_check_on_the_second_diagonal_from_left_to_right(
    std::map<FigurePoint, ChessPiece> mFigures, FigurePoint king_coordinates) {
  auto [x_king, y_king] = king_coordinates;
  auto figure_positin = mFigures.find(FigurePoint(x_king, y_king));
  if (figure_positin == mFigures.end()) {
    return false;
  }
  const auto king_color = figure_positin->second.get_color();
  if (x_king == 7 || y_king == 0) {
    return false;
  }
  for (size_t i = x_king + 1, j = y_king - 1; i < 8 && j >= 0; ++i, --j) {
    if (mFigures[FigurePoint(i, j)].get_type() != EMPTY &&
        mFigures[FigurePoint(i, j)].get_color() == king_color) {
      return false;
    } else if (mFigures[FigurePoint(i, j)].get_type() != EMPTY &&
               mFigures[FigurePoint(i, j)].get_color() != king_color) {
      if (mFigures[FigurePoint(i, j)].get_type() == BISHOP ||
          mFigures[FigurePoint(i, j)].get_type() == QUEEN) {
        return true;
      }
      return false;
    }
  }
  return false;
}
// this function check if Knight looks in the direction of a King
bool check_for_check_knigth(std::map<FigurePoint, ChessPiece> mFigures,
                            FigurePoint king_coordinates, size_t x_enemy,
                            size_t y_enemy) {
  auto [x_king, y_king] = king_coordinates;
  auto figure_positin = mFigures.find(FigurePoint(x_enemy, y_enemy));
  if (figure_positin == mFigures.end()) {
    return false;
  }
  const auto king_color = figure_positin->second.get_color();
  auto king = mFigures[FigurePoint(x_king, y_king)];
  auto enemy = mFigures[FigurePoint(x_enemy, y_enemy)];
  if (x_enemy > SIZE || y_enemy > SIZE) {
    return false;
  } else {
    if (enemy.get_type() == KNIGHT && enemy.get_color() != king.get_color()) {
      return true;
    }
  }
  return false;
}

void find_koordinate_king(std::map<FigurePoint, ChessPiece> mFigures,
                          FigurePoint &king_coordinates, Color color_king) {

  for (size_t i = 0; i < SIZE; ++i) {
    for (size_t j = 0; j < SIZE; ++j) {
      if (mFigures[FigurePoint(i, j)].get_type() == KING &&
          mFigures[FigurePoint(i, j)].get_color() == color_king) {
        king_coordinates.first = i;
        king_coordinates.second = j;
        break;
      }
    }
  }
}

// this method checks all moves from the king to check
bool Board::check_checkmate(Color color_king, FigurePoint king_coordinates) {
  const size_t SIZE_ARRAY_FOR_CHECK_CHECKMATE = 17;
  bool array_check_checkmate[SIZE_ARRAY_FOR_CHECK_CHECKMATE] = {};
  auto xK = king_coordinates.first;
  auto yK = king_coordinates.second;
  size_t check_for_checkmate = 0;

  array_check_checkmate[0] = check_of_the_check_in_a_straight_descending_line_y(
      mFigures, king_coordinates);
  array_check_checkmate[1] = check_of_the_check_in_a_straight_ascending_line_y(
      mFigures, king_coordinates);
  array_check_checkmate[2] = check_of_the_check_in_a_straight_descending_line_x(
      mFigures, king_coordinates);
  array_check_checkmate[3] = check_of_the_check_in_a_straight_ascending_line_x(
      mFigures, king_coordinates);

  array_check_checkmate[4] =
      check_the_check_on_the_first_diagonal_from_right_to_left(
          mFigures, king_coordinates);
  array_check_checkmate[5] =
      check_the_check_on_the_second_diagonal_from_right_to_left(
          mFigures, king_coordinates);
  array_check_checkmate[6] =
      check_the_check_on_the_second_diagonal_from_right_to_left(
          mFigures, king_coordinates);
  array_check_checkmate[7] =
      check_the_check_on_the_second_diagonal_from_left_to_right(
          mFigures, king_coordinates);

  array_check_checkmate[8] =
      check_for_check_knigth(mFigures, king_coordinates, xK + 2, yK + 1);
  array_check_checkmate[9] =
      check_for_check_knigth(mFigures, king_coordinates, xK + 2, yK + 1);
  array_check_checkmate[10] =
      check_for_check_knigth(mFigures, king_coordinates, xK + 2, yK - 1);
  array_check_checkmate[11] =
      check_for_check_knigth(mFigures, king_coordinates, xK - 2, yK + 1);
  array_check_checkmate[12] =
      check_for_check_knigth(mFigures, king_coordinates, xK - 2, yK - 1);
  array_check_checkmate[13] =
      check_for_check_knigth(mFigures, king_coordinates, xK + 1, yK + 2);
  array_check_checkmate[14] =
      check_for_check_knigth(mFigures, king_coordinates, xK + 1, yK - 2);
  array_check_checkmate[15] =
      check_for_check_knigth(mFigures, king_coordinates, xK - 1, yK + 2);
  array_check_checkmate[16] =
      check_for_check_knigth(mFigures, king_coordinates, xK - 1, yK - 2);
  for (size_t i = 0; i < SIZE_ARRAY_FOR_CHECK_CHECKMATE; ++i) {
    if (array_check_checkmate[i] == true) {
      return true;
    }
  }
  return false;
}
void check_input_coordinate(FigurePoint &input_coordinates) {
  auto &[x, y] = input_coordinates;
  const size_t const_variable_instead_of_literal = 2;
  const size_t coconst_variable_instead = 1;
  const size_t convert_char_into_internal_logic_chess_position = 97;
  const size_t convert_char_digit_into_size_t = 49;
  while (true) {
    std::string input_coordinates;
    std::getline(std::cin, input_coordinates);
    if (input_coordinates.size() == const_variable_instead_of_literal) {
      if (input_coordinates[0] >= 'a' && input_coordinates[0] <= 'h') {
        if (input_coordinates[1] > '0' && input_coordinates[1] <= '8') {
          y = input_coordinates[0] -
              convert_char_into_internal_logic_chess_position;
          x = input_coordinates[1] - convert_char_digit_into_size_t;
          break;
        }
      }
    } else if (input_coordinates.size() == coconst_variable_instead &&
               input_coordinates[0] == 'q') {
      flag_to_exit_chess = true;
      break;
    }
  };
}

void Board::all_game_logic() {
  FigurePoint first_coordinates_xy;
  FigurePoint second_coordinates_xy;
  FigurePoint coordinates_for_king{};
  auto &[x1, y1] = first_coordinates_xy;
  auto &[x2, y2] = second_coordinates_xy;

  if (turn_players) {
    std::cout << "White turn\n";
    if (checkand_check_flag) {
      std::cout << "Info: The White player is set to CHECK!!!\n";
    }
  } else {
    std::cout << "Black turn\n";
    if (checkand_check_flag) {
      std::cout << "Info: The Black player is set to CHECK!!!\n";
    }
  }
  check_input_coordinate(first_coordinates_xy);
  auto figure_position_1 = mFigures.find(FigurePoint(x1, y1));
  if (figure_position_1 == mFigures.end()) {
    std::cout << "Error: This position is not on the Chess board\n";
    return;
  }
  auto color_figures = figure_position_1->second.get_color();
  check_input_coordinate(second_coordinates_xy);
  auto figure_position_2 = mFigures.find(FigurePoint(x2, y2));
  if (figure_position_2 == mFigures.end()) {
    std::cout << "Error: This position is not on the Chess board\n";
    return;
  }
  // this if checks if move belongs to WHITE or BLACK player
  if (color_figures == WHITE && turn_players == true) {
    // this if checks if move is allowed
    if (checking_the_correctness_of_moves_of_pieces(first_coordinates_xy,
                                                    second_coordinates_xy)) {
      // this if checks a check or checkmate
      if (checkand_check_flag == true) {
        find_koordinate_king(mFigures, coordinates_for_king, WHITE);
        get_winner(check_checkmate(WHITE, coordinates_for_king), WHITE);
        checkand_check_flag = false;
      }
      turn_players = false;
    }
  } else if (color_figures == BLACK && turn_players == false) {
    if (checking_the_correctness_of_moves_of_pieces(first_coordinates_xy,
                                                    second_coordinates_xy)) {
      if (checkand_check_flag == true) {
        find_koordinate_king(mFigures, coordinates_for_king, BLACK);
        get_winner(check_checkmate(WHITE, coordinates_for_king), BLACK);
        checkand_check_flag = false;
      }
      turn_players = true;
    }
  } else {
    std::cout << "error: wrong input\n";
    return;
  }
  // check for the check after the player’s turn
  find_koordinate_king(mFigures, coordinates_for_king,
                       color_figures == WHITE ? BLACK : WHITE);
  checkand_check_flag = check_checkmate(color_figures == WHITE ? BLACK : WHITE,
                                        coordinates_for_king);
}

bool Board::checking_for_pieces_between_coordinates_continuation(
    FigurePoint first_coordinates, FigurePoint second_coordinates) {
  auto [x1, y1] = first_coordinates;
  auto [x2, y2] = second_coordinates;
  // checks for the presence of figures between the points of movement along the
  // axis x+
  if (x1 < x2 && y1 == y2) {
    for (size_t i = x1 + 1; i < x2; ++i) {
      if (mFigures[FigurePoint(i, y1)].get_type() != EMPTY) {
        return false;
      }
    }
    return true;
  }
  // checks for the presence of figures between the points of movement along the
  // axis y+
  else if (x1 == x2 && y1 < y2) {
    for (size_t i = y1 + 1; i < y2; ++i) {
      if (mFigures[FigurePoint(x1, i)].get_type() != EMPTY) {
        return false;
      }
    }
    return true;
  }
  // checks for the presence of figures between the points of movement along the
  // axis y-
  else if (x1 == x2 && y1 > y2) {
    for (size_t i = y1 - 1; i > y2; --i) {
      if (mFigures[FigurePoint(x1, i)].get_type() != EMPTY) {
        return false;
      }
    }
    return true;
  }
  // checks for the presence of figures between the points of movement along the
  // axis x-
  else if (x1 > x2 && y1 == y2) {
    for (size_t i = x1 - 1; i > x2; --i) {
      if (mFigures[FigurePoint(i, y1)].get_type() != EMPTY) {
        return false;
      }
    }
    return true;
  }
  // checks for the presence of figures between the points of movement along the
  // diagonal x+ y+
  else if (x1 < x2 && y1 < y2) {
    for (size_t i = x1 + 1, j = y1 + 1; i < x2 && j < y2; ++i, ++j) {
      if (mFigures[FigurePoint(i, j)].get_type() != EMPTY) {
        return false;
      }
    }
    return true;
  }
  // checks for the presence of figures between the points of movement along the
  // diagonal x+ y-
  else if (x1 < x2 && y1 > y2) {
    for (size_t i = x1 + 1, j = y1 - 1; i < x2 && j > y2; ++i, --j) {
      if (mFigures[FigurePoint(i, j)].get_type() != EMPTY) {
        return false;
      }
    }
    return true;
  }
  // checks for the presence of figures between the points of movement along the
  // diagonal x- y-
  else if (x1 > x2 && y1 > y2) {
    for (size_t i = x1 - 1, j = y1 - 1; i > x2 && j > y2; --i, --j) {
      if (mFigures[FigurePoint(i, j)].get_type() != EMPTY) {
        return false;
      }
    }
    return true;
  }
  // checks for the presence of figures between the points of movement along the
  // diagonal x- y+
  else if (x1 > x2 && y1 < y2) {
    for (size_t i = x1 - 1, j = y1 + 1; i > x2 && j < y2; --i, ++j) {
      if (mFigures[FigurePoint(i, j)].get_type() != EMPTY) {
        return false;
      }
    }
    return true;
  }
  return true;
}

bool Board::checking_for_pieces_between_coordinates(
    FigurePoint first_coordinates, FigurePoint second_coordinates) {
  auto [x1, y1] = first_coordinates;
  auto [x2, y2] = second_coordinates;
  auto figure_positin = mFigures.find(FigurePoint(x1, y1));
  if (figure_positin == mFigures.end()) {
    return false;
  }
  const auto start_color_figure = figure_positin->second.get_color();
  const auto start_type_figure = mFigures.at(FigurePoint(x1, y1)).get_type();
  const auto finish_color_figure = mFigures.at(FigurePoint(x2, y2)).get_color();
  int variable_for_checking_for_short_stepX = x1 - x2;
  int variable_for_checking_for_short_stepY = y1 - y2;
  if (start_type_figure == Type::KNIGHT) {
    return false;
  } // this if checks if there is a knight figure
  // this if checks the stroke length of the piece
  if ((std::abs(variable_for_checking_for_short_stepX) > 1 &&
       variable_for_checking_for_short_stepY == 0) ||
      (std::abs(variable_for_checking_for_short_stepX) > 1 &&
       std::abs(variable_for_checking_for_short_stepX) > 1) ||
      (variable_for_checking_for_short_stepX == 0 &&
       std::abs(variable_for_checking_for_short_stepY) > 1)) {
    if (checking_for_pieces_between_coordinates_continuation(
            first_coordinates, second_coordinates)) {
      return false;
    }
    return true;
  }
  return false;
}

void Board::saveGame() {
  std::string file_name;
  std::cout << "Type file name to be saved (no extension): ";
  std::cin >> file_name;
  file_name += ".txt";
  std::ofstream ofs(file_name);
  std::ofstream fout;
  fout.open(file_name, std::ofstream::app);
  if (!fout.is_open()) {
    std::cout << "File not open ";
    return;
  }
  for (size_t i = 0; i < SIZE; ++i) {
    for (size_t j = 0; j < SIZE; ++j) {
      const ChessPiece &figure = mFigures.at(FigurePoint(i, j));
      fout << i << " " << j << " " << figure.get_type() << figure.get_color()
           << "\n";
      std::cout << std::endl;
    }
  }
  fout.close();
  return;
}
void Board::loadGame() {
  std::string file_name;
  std::cout << "Input name save fiels \n";
  std::cin >> file_name;
  std::ifstream fin{file_name + ".txt"};
  if (!fin.is_open()) {
    std::cout << "File not open ";
    return;
  }
  std::string str;
  while (!fin.eof()) {

    FigurePoint figure_point;
    int color;
    int type;
    fin >> figure_point.first >> figure_point.second >> type >> color;
    ChessPiece figure{static_cast<Type>(type), static_cast<Color>(color)};
    mFigures.emplace(figure_point, figure);
    char last;
    fin >> last;
  }
}

bool Board::get_winner(bool winner, Color color_king) {
  if (color_king == WHITE && winner == true) {
    std::cout << "Congratulations!!! Black player won this match\n";
    flag_to_exit_chess = true;
  } else if (color_king == BLACK && winner == true) {
    std::cout << "Congratulations!!! White player won this match\n";
    flag_to_exit_chess = true;
  }
  return true;
}

bool Board::exit_from_match() {
  if (flag_to_exit_chess) {
    return true;
  }
  return false;
}
