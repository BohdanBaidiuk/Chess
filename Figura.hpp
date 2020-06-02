#pragma once
#include <string>
#include <utility>
    using FigurePoint = std::pair<size_t, size_t>;
enum Color { WHITE, BLACK, NONE };
enum Type { KING, QUEEN, BISHOP, KNIGHT, ROOK, PAWN, EMPTY };

class ChessPiece {
public:
  ChessPiece(Type type, Color color) : type_figure(type), color_figure(color){};
  ChessPiece(){};
  Color get_color() const { return color_figure; };
  Type get_type() const { return type_figure; };
  void clean_figure() {
    type_figure = EMPTY;
    color_figure = NONE;
  }

private:
  Type type_figure{EMPTY};
  Color color_figure{NONE};
};
