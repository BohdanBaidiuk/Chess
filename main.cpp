#include "Board.hpp"

bool exit_the_match = true;
enum class Optional_choice { RESTART = 1, START, LOAD, SAVE, EXIT };

int main() {
  Board ChessGame;
  bool out_game = true;

  std::cout << "Hello, this is a chess game for 2 people on one computer.\n";

  size_t choice;
  while (out_game) {
    std::cout << "To start playing select options on the screen.\n  Please "
                 "input your choice\n"
                 "1 - Restart game\n"
                 "2 - Start game\n"
                 "3 - Loade game\n"
                 "4 - Save game\n"
                 "5 - Exit the game\n";
    std::cin >> choice;
    if (!std::cin) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }
    switch (Optional_choice(choice)) {
    case Optional_choice::RESTART:
    case Optional_choice::START:
      ChessGame.draws_started_figurines_on_the_board();
      while (exit_the_match) {
        ChessGame.show_map();
        std::cout << "Which piece would you like to move? \n"
                     "info: should be like on example  d2  k-enter then d3  or "
                     " g1  k-enter then  f3 \n"
                     "if you need to exit k-enter  q \n";
        ChessGame.all_game_logic();
        if (ChessGame.exit_from_match()) {
          exit_the_match = false;
        }
      }
      break;
    case Optional_choice::LOAD:
      ChessGame.loadGame();
      break;
    case Optional_choice::SAVE:
      ChessGame.saveGame();
      break;
    case Optional_choice::EXIT:
      out_game = false;
    default:
      std::cout << "Invalid selection entered, try again\n";
      break;
    }
  }

  return 0;
}
