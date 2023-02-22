#include <iostream>

#include "board.hpp"

int main() {
  Board same_player1;
  InitBoard(same_player1);
  for (unsigned int i = 0; i < 4; ++i) {
    DropDiskToBoard(same_player1, DiskType::kPlayer1, i);
  }
  for (unsigned int i = 0; i < 3; ++i) {
    DropDiskToBoard(same_player1, DiskType::kPlayer1, 0);
  }
  std::cout << BoardToStr(same_player1) << std::endl;
}