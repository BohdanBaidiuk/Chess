#pragma once
#include "Figura.hpp"
#include <map>

class Board {
public:
  Board(){};
  void draws_started_figurines_on_the_board();
  void show_map();
  void all_game_logic();
  void saveGame();
  void loadGame();
  bool exit_from_match();

private:
  bool get_winner(bool winner, Color color_king);
  bool checking_for_pieces_between_coordinates(FigurePoint first_coordinates,
                                               FigurePoint second_coordinates);
  bool checking_for_pieces_between_coordinates_continuation(
      FigurePoint first_coordinates, FigurePoint second_coordinates);
  bool
  checking_the_correctness_of_moves_of_pieces(FigurePoint first_coordinates,
                                              FigurePoint second_coordinates);
  bool check_checkmate(Color color_king, FigurePoint king_coordinates);
  void draw_white_piece();
  void draw_black_piece();
  void draw_none_piece();
  std::map<FigurePoint, ChessPiece> mFigures{};
};
