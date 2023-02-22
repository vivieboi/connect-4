// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Michael R. Nowak                Environment : ubuntu:latest               //
//  Date ......: 2022/02/07                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "board.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////
constexpr int kBoardWidth = 7;
constexpr int kBoardHeight = 6;

bool AreEqual(DiskType solution[][kBoardWidth],
              DiskType student[][kBoardWidth]) {
  for (int i = 0; i < kBoardHeight; ++i) {
    for (int j = 0; j < kBoardWidth; ++j) {
      if (solution[i][j] != student[i][j]) return false;
    }
  }
  return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Board initialization", "[board_init]") {
  // SECTION("Can use sections") {}
  // clang-format off
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);
  REQUIRE(AreEqual(solution, student.board));
}

// Write a test case to test the drop disk to board method
TEST_CASE("Dropping disk into board", "[drop_disk]") {
  // making a board to compare to later

  DiskType solution[kBoardHeight][kBoardWidth] = {
    {DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };

  Board b;
  InitBoard(b);
  REQUIRE_FALSE(AreEqual(solution, b.board));
  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  DropDiskToBoard(b, DiskType::kPlayer2, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  for (unsigned int i = 0; i < kBoardHeight; ++i) {
    DropDiskToBoard(b, DiskType::kPlayer1, 2);
  }

  REQUIRE(AreEqual(solution, b.board));
  REQUIRE_THROWS_AS(DropDiskToBoard(b, DiskType::kPlayer2, -1), std::runtime_error);
  REQUIRE_THROWS_AS(DropDiskToBoard(b, DiskType::kPlayer2, 2), std::runtime_error);
  REQUIRE_THROWS_AS(DropDiskToBoard(b, DiskType::kPlayer2, kBoardWidth), std::runtime_error);

  DropDiskToBoard(b, DiskType::kPlayer2, 5);
  REQUIRE_FALSE(AreEqual(solution, b.board));
}

TEST_CASE("Check if board location is in bounds", "[check_location_in_bounds]") {
  REQUIRE(BoardLocationInBounds(0, 0));
  REQUIRE(BoardLocationInBounds(kBoardHeight - 1, kBoardWidth - 1));
  REQUIRE(BoardLocationInBounds(0, kBoardWidth - 1));
  REQUIRE(BoardLocationInBounds(kBoardHeight - 1, 0));
  REQUIRE_FALSE(BoardLocationInBounds(kBoardHeight, kBoardWidth));
  REQUIRE_FALSE(BoardLocationInBounds(0, kBoardWidth));
  REQUIRE_FALSE(BoardLocationInBounds(kBoardHeight, 0));

  REQUIRE_FALSE(BoardLocationInBounds(-1, -4));
  REQUIRE_FALSE(BoardLocationInBounds(6, 7));
  REQUIRE_FALSE(BoardLocationInBounds(10, 11));
  REQUIRE(BoardLocationInBounds(4, 5));
  REQUIRE_FALSE(BoardLocationInBounds(2, -4));
  REQUIRE_FALSE(BoardLocationInBounds(8,0));
}

TEST_CASE("Search for winner in a specific direction", "[search_winner_in_direction]") {
  // Section 1: Search vertical
  Board vertical_test_1;
  InitBoard(vertical_test_1);
  for (unsigned int i = 0; i < 3; ++i) {
    DropDiskToBoard(vertical_test_1, DiskType::kPlayer1, 2);
  }
  REQUIRE_FALSE(SearchForWinner(vertical_test_1, DiskType::kPlayer1, WinningDirection::kVertical));
  DropDiskToBoard(vertical_test_1, DiskType::kPlayer1, 2);
  REQUIRE(SearchForWinner(vertical_test_1, DiskType::kPlayer1, WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(vertical_test_1, DiskType::kPlayer2, WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(vertical_test_1, DiskType::kPlayer1, WinningDirection::kHorizontal));
  REQUIRE_FALSE(SearchForWinner(vertical_test_1, DiskType::kPlayer1, WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(vertical_test_1, DiskType::kPlayer1, WinningDirection::kLeftDiag));

  Board vertical_test_2;
  InitBoard(vertical_test_2);
  for (unsigned int i = 0; i < 3; ++i) {
    DropDiskToBoard(vertical_test_2, DiskType::kPlayer2, 2);
  }
  REQUIRE_FALSE(SearchForWinner(vertical_test_2, DiskType::kPlayer2, WinningDirection::kVertical));
  DropDiskToBoard(vertical_test_2, DiskType::kPlayer2, 2);
  REQUIRE(SearchForWinner(vertical_test_2, DiskType::kPlayer2, WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(vertical_test_2, DiskType::kPlayer1, WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(vertical_test_2, DiskType::kPlayer2, WinningDirection::kHorizontal));
  REQUIRE_FALSE(SearchForWinner(vertical_test_2, DiskType::kPlayer2, WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(vertical_test_2, DiskType::kPlayer2, WinningDirection::kLeftDiag));


  // Section 2: Search horizontal
  Board horizontal_test_1;
  InitBoard(horizontal_test_1);
  for (unsigned int i = 1; i < 4; ++i) {
    DropDiskToBoard(horizontal_test_1, DiskType::kPlayer1, i);
  }
  REQUIRE_FALSE(SearchForWinner(horizontal_test_1, DiskType::kPlayer1, WinningDirection::kHorizontal));
  DropDiskToBoard(horizontal_test_1, DiskType::kPlayer1, 4);
  REQUIRE(SearchForWinner(horizontal_test_1, DiskType::kPlayer1, WinningDirection::kHorizontal));
  REQUIRE_FALSE(SearchForWinner(horizontal_test_1, DiskType::kPlayer2, WinningDirection::kHorizontal));
  REQUIRE_FALSE(SearchForWinner(horizontal_test_1, DiskType::kPlayer1, WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(horizontal_test_1, DiskType::kPlayer1, WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(horizontal_test_1, DiskType::kPlayer1, WinningDirection::kLeftDiag));

  Board horizontal_test_2;
  InitBoard(horizontal_test_2);
  for (unsigned int i = 1; i < 4; ++i) {
    DropDiskToBoard(horizontal_test_2, DiskType::kPlayer2, i);
  }
  REQUIRE_FALSE(SearchForWinner(horizontal_test_2, DiskType::kPlayer2, WinningDirection::kHorizontal));
  DropDiskToBoard(horizontal_test_2, DiskType::kPlayer2, 4);
  REQUIRE(SearchForWinner(horizontal_test_2, DiskType::kPlayer2, WinningDirection::kHorizontal));
  REQUIRE_FALSE(SearchForWinner(horizontal_test_2, DiskType::kPlayer1, WinningDirection::kHorizontal));
  REQUIRE_FALSE(SearchForWinner(horizontal_test_2, DiskType::kPlayer2, WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(horizontal_test_2, DiskType::kPlayer2, WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(horizontal_test_2, DiskType::kPlayer2, WinningDirection::kLeftDiag));


  // Section 3: Search left diagonal
  Board left_diagonal_test_1;
  InitBoard(left_diagonal_test_1);
  for (unsigned int i = 0; i < 4; ++i) {
    for (unsigned int j = 3; j > i; --j) {
      DropDiskToBoard(left_diagonal_test_1, DiskType::kPlayer2, i + 1);
    }
  }
  for (unsigned int i = 0; i < 3; ++i) {
    DropDiskToBoard(left_diagonal_test_1, DiskType::kPlayer1, i + 1);
  }
  REQUIRE_FALSE(SearchForWinner(left_diagonal_test_1, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  DropDiskToBoard(left_diagonal_test_1, DiskType::kPlayer1, 4);
  REQUIRE(SearchForWinner(left_diagonal_test_1, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(left_diagonal_test_1, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(left_diagonal_test_1, DiskType::kPlayer1, WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(left_diagonal_test_1, DiskType::kPlayer1, WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(left_diagonal_test_1, DiskType::kPlayer1, WinningDirection::kHorizontal));

  Board left_diagonal_test_2;
  InitBoard(left_diagonal_test_2);
  for (unsigned int i = 0; i < 4; ++i) {
    for (unsigned int j = 3; j > i; --j) {
      DropDiskToBoard(left_diagonal_test_2, DiskType::kPlayer1, i + 1);
    }
  }
  for (unsigned int i = 0; i < 3; ++i) {
    DropDiskToBoard(left_diagonal_test_2, DiskType::kPlayer2, i + 1);
  }
  REQUIRE_FALSE(SearchForWinner(left_diagonal_test_2, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  DropDiskToBoard(left_diagonal_test_2, DiskType::kPlayer2, 4);
  REQUIRE(SearchForWinner(left_diagonal_test_2, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(left_diagonal_test_2, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(left_diagonal_test_2, DiskType::kPlayer2, WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(left_diagonal_test_2, DiskType::kPlayer2, WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(left_diagonal_test_2, DiskType::kPlayer2, WinningDirection::kHorizontal));


  // Section 4: Search right diagonal
  Board right_diagonal_test_1;
  InitBoard(right_diagonal_test_1);
  for (unsigned int i = 0; i < 4; ++i) {
    for (unsigned int j = 0; j <= i; ++j) {
      DropDiskToBoard(right_diagonal_test_1, DiskType::kPlayer2, i + 2);
    }
  }
  for (unsigned int i = 0; i < 3; ++i) {
    DropDiskToBoard(right_diagonal_test_1, DiskType::kPlayer1, i + 2);
  }
  REQUIRE_FALSE(SearchForWinner(right_diagonal_test_1, DiskType::kPlayer1, WinningDirection::kRightDiag));
  DropDiskToBoard(right_diagonal_test_1, DiskType::kPlayer1, 5);
  REQUIRE(SearchForWinner(right_diagonal_test_1, DiskType::kPlayer1, WinningDirection::kRightDiag));
  // Below these require false were commented out
  /* REQUIRE_FALSE(SearchForWinner(right_diagonal_test_1, DiskType::kPlayer2, WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(right_diagonal_test_1, DiskType::kPlayer1, WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(right_diagonal_test_1, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(right_diagonal_test_1, DiskType::kPlayer1, WinningDirection::kHorizontal)); */

  Board right_diagonal_test_2;
  InitBoard(right_diagonal_test_2);
  for (unsigned int i = 0; i < 4; ++i) {
    for (unsigned int j = 0; j <= i; ++j) {
      DropDiskToBoard(right_diagonal_test_2, DiskType::kPlayer1, i + 2);
    }
  }
  for (unsigned int i = 0; i < 3; ++i) {
    DropDiskToBoard(right_diagonal_test_2, DiskType::kPlayer2, i + 2);
  }
  REQUIRE_FALSE(SearchForWinner(right_diagonal_test_2, DiskType::kPlayer2, WinningDirection::kRightDiag));
  DropDiskToBoard(right_diagonal_test_2, DiskType::kPlayer2, 5);
  REQUIRE(SearchForWinner(right_diagonal_test_2, DiskType::kPlayer2, WinningDirection::kRightDiag));
  // Below these require false were commented out
  /* REQUIRE_FALSE(SearchForWinner(right_diagonal_test_2, DiskType::kPlayer1, WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(right_diagonal_test_2, DiskType::kPlayer2, WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(right_diagonal_test_2, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(right_diagonal_test_2, DiskType::kPlayer2, WinningDirection::kHorizontal)); */


  // Section 5: SearchForWinner doesn't find a winner
  REQUIRE_FALSE(SearchForWinner(left_diagonal_test_2, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(left_diagonal_test_2, DiskType::kPlayer2, WinningDirection::kHorizontal));
  REQUIRE_FALSE(SearchForWinner(left_diagonal_test_2, DiskType::kPlayer2, WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(left_diagonal_test_2, DiskType::kPlayer2, WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(horizontal_test_1, DiskType::kPlayer2, WinningDirection::kVertical));

  Board empty;
  REQUIRE_FALSE(SearchForWinner(empty, DiskType::kPlayer1, WinningDirection::kHorizontal));
  REQUIRE_FALSE(SearchForWinner(empty, DiskType::kPlayer1, WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(empty, DiskType::kPlayer1, WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(empty, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(empty, DiskType::kPlayer2, WinningDirection::kHorizontal));
  REQUIRE_FALSE(SearchForWinner(empty, DiskType::kPlayer2, WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(empty, DiskType::kPlayer2, WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(empty, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  InitBoard(empty);
  REQUIRE_FALSE(SearchForWinner(empty, DiskType::kPlayer1, WinningDirection::kHorizontal));
  REQUIRE_FALSE(SearchForWinner(empty, DiskType::kPlayer1, WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(empty, DiskType::kPlayer1, WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(empty, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(empty, DiskType::kPlayer2, WinningDirection::kHorizontal));
  REQUIRE_FALSE(SearchForWinner(empty, DiskType::kPlayer2, WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(empty, DiskType::kPlayer2, WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(empty, DiskType::kPlayer2, WinningDirection::kLeftDiag));

  // 3 in a row
  for (unsigned int i = 0; i < 3; ++i) {
    DropDiskToBoard(empty, DiskType::kPlayer1, i);
    DropDiskToBoard(empty, DiskType::kPlayer1, 4);
  }
  DropDiskToBoard(empty, DiskType::kPlayer1, 0);
  DropDiskToBoard(empty, DiskType::kPlayer1, 0);
  REQUIRE_FALSE(SearchForWinner(empty, DiskType::kPlayer1, WinningDirection::kHorizontal));
  REQUIRE_FALSE(SearchForWinner(empty, DiskType::kPlayer1, WinningDirection::kVertical));

  // Alternating player 1 and player 2
  Board alternate;
  InitBoard(alternate);
  for (unsigned int i = 0; i < 5; ++i) {
    if (i == 2) {
      DropDiskToBoard(alternate, DiskType::kPlayer2, 0);
    } else {
      DropDiskToBoard(alternate, DiskType::kPlayer1, 0);
    }
  }
  REQUIRE_FALSE(SearchForWinner(alternate, DiskType::kPlayer1, WinningDirection::kVertical));

  // Two winners
  Board two_winners_test_right;
  InitBoard(two_winners_test_right);
  for (unsigned int i = 0; i < 5; ++i) {
    if (i == 1) {
      DropDiskToBoard(two_winners_test_right, DiskType::kPlayer2, i);
    } else {
      DropDiskToBoard(two_winners_test_right, DiskType::kPlayer1, i);
    }
  }
  for (unsigned int i = 0; i < 5; ++i) {
    if (i == 0 || i == 2) {
      DropDiskToBoard(two_winners_test_right, DiskType::kPlayer2, i);
    } else {
      DropDiskToBoard(two_winners_test_right, DiskType::kPlayer1, i);
    }
  }
  for (unsigned int i = 0; i < 5; ++i) {
    if (i == 2 || i == 4) {
      DropDiskToBoard(two_winners_test_right, DiskType::kPlayer1, i);
    } else {
      DropDiskToBoard(two_winners_test_right, DiskType::kPlayer2, i);
    }
  }
  for (unsigned int i = 0; i < 5; ++i) {
    if (i == 3) {
      DropDiskToBoard(two_winners_test_right, DiskType::kPlayer1, i);
    } else {
      DropDiskToBoard(two_winners_test_right, DiskType::kPlayer2, i);
    }
  }
  REQUIRE(SearchForWinner(two_winners_test_right, DiskType::kPlayer1, WinningDirection::kRightDiag));
  REQUIRE(SearchForWinner(two_winners_test_right, DiskType::kPlayer2, WinningDirection::kRightDiag));


  Board two_winners_test_left;
  InitBoard(two_winners_test_left);
  for (unsigned int i = 0; i < 5; ++i) {
    if (i == 1) {
      DropDiskToBoard(two_winners_test_left, DiskType::kPlayer2, 6 - i);
    } else {
      DropDiskToBoard(two_winners_test_left, DiskType::kPlayer1, 6 - i);
    }
  }
  for (unsigned int i = 0; i < 5; ++i) {
    if (i == 2 || i == 0) {
      DropDiskToBoard(two_winners_test_left, DiskType::kPlayer2, 6 - i);
    } else {
      DropDiskToBoard(two_winners_test_left, DiskType::kPlayer1, 6 - i);
    }
  }
  for (unsigned int i = 0; i < 5; ++i) {
    if (i == 2 || i == 4) {
      DropDiskToBoard(two_winners_test_left, DiskType::kPlayer1, 6 - i);
    } else {
      DropDiskToBoard(two_winners_test_left, DiskType::kPlayer2, 6 - i);
    }
  }
  for (unsigned int i = 0; i < 5; ++i) {
    if (i == 3) {
      DropDiskToBoard(two_winners_test_left, DiskType::kPlayer1, 6 - i);
    } else {
      DropDiskToBoard(two_winners_test_left, DiskType::kPlayer2, 6 - i);
    }
  }
  REQUIRE(SearchForWinner(two_winners_test_left, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  REQUIRE(SearchForWinner(two_winners_test_left, DiskType::kPlayer2, WinningDirection::kLeftDiag));

  // Same winner two ways
  Board same_player1;
  InitBoard(same_player1);
  for (unsigned int i = 0; i < 4; ++i) {
    DropDiskToBoard(same_player1, DiskType::kPlayer1, i);
  }
  for (unsigned int i = 0; i < 3; ++i) {
    DropDiskToBoard(same_player1, DiskType::kPlayer1, 0);
  }
  REQUIRE(SearchForWinner(same_player1, DiskType::kPlayer1, WinningDirection::kHorizontal));
  REQUIRE(SearchForWinner(same_player1, DiskType::kPlayer1, WinningDirection::kVertical));

  Board same_player2;
  InitBoard(same_player2);
  for (unsigned int i = 0; i < 4; ++i) {
    DropDiskToBoard(same_player2, DiskType::kPlayer2, i);
  }
  for (unsigned int i = 0; i < 3; ++i) {
    DropDiskToBoard(same_player2, DiskType::kPlayer2, 0);
  }
  REQUIRE(SearchForWinner(same_player2, DiskType::kPlayer2, WinningDirection::kHorizontal));
  REQUIRE(SearchForWinner(same_player2, DiskType::kPlayer2, WinningDirection::kVertical));

  // Another test idea: someone wins with more than 4
  Board more_than_4;
  InitBoard(more_than_4);
  for (unsigned int i = 0; i < 5; ++i) {
    DropDiskToBoard(more_than_4, DiskType::kPlayer2, i);
  }
  REQUIRE(SearchForWinner(more_than_4, DiskType::kPlayer2, WinningDirection::kHorizontal));

  // Entire board is one player
  Board all_1;
  InitBoard(all_1);
  for (unsigned int i = 0; i < kBoardHeight; ++i) {
    for (unsigned int j = 0; j < kBoardWidth; ++j) {
      all_1.board[i][j] = DiskType::kPlayer1;
    }
  }
  REQUIRE(SearchForWinner(all_1, DiskType::kPlayer1, WinningDirection::kHorizontal));
  REQUIRE(SearchForWinner(all_1, DiskType::kPlayer1, WinningDirection::kVertical));
  REQUIRE(SearchForWinner(all_1, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  REQUIRE(SearchForWinner(all_1, DiskType::kPlayer1, WinningDirection::kRightDiag));

  Board all_2;
  InitBoard(all_2);
  for (unsigned int i = 0; i < kBoardHeight; ++i) {
    for (unsigned int j = 0; j < kBoardWidth; ++j) {
      all_2.board[i][j] = DiskType::kPlayer2;
    }
  }
  REQUIRE(SearchForWinner(all_2, DiskType::kPlayer2, WinningDirection::kHorizontal));
  REQUIRE(SearchForWinner(all_2, DiskType::kPlayer2, WinningDirection::kVertical));
  REQUIRE(SearchForWinner(all_2, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  REQUIRE(SearchForWinner(all_2, DiskType::kPlayer2, WinningDirection::kRightDiag));


  // Horizontal win in the middle
  Board ho_mid_1;
  InitBoard(ho_mid_1);
  for (unsigned int i = 0; i < 4; ++i) {
    for (unsigned int j = 0; j < 4; ++j) {
      ho_mid_1.board[i + 2][j + 2] = DiskType::kPlayer1;
    }
  }
  REQUIRE(SearchForWinner(ho_mid_1, DiskType::kPlayer1, WinningDirection::kHorizontal));

  Board ho_mid_2;
  InitBoard(ho_mid_2);
  for (unsigned int i = 0; i < 4; ++i) {
    for (unsigned int j = 0; j < 4; ++j) {
      ho_mid_2.board[i + 1][j + 1] = DiskType::kPlayer2;
    }
  }
  REQUIRE(SearchForWinner(ho_mid_2, DiskType::kPlayer2, WinningDirection::kHorizontal));
}

TEST_CASE("Search overall board for winner", "[search_winner]") {
  // Section 1: Vertical winner
  Board vertical_test_1;
  InitBoard(vertical_test_1);
  for (unsigned int i = 0; i < 3; ++i) {
    DropDiskToBoard(vertical_test_1, DiskType::kPlayer1, 2);
  }
  REQUIRE_FALSE(CheckForWinner(vertical_test_1, DiskType::kPlayer1));
  DropDiskToBoard(vertical_test_1, DiskType::kPlayer1, 2);
  REQUIRE(CheckForWinner(vertical_test_1, DiskType::kPlayer1));

  Board vertical_test_2;
  InitBoard(vertical_test_2);
  for (unsigned int i = 0; i < 3; ++i) {
    DropDiskToBoard(vertical_test_2, DiskType::kPlayer2, 4);
  }
  REQUIRE_FALSE(CheckForWinner(vertical_test_2, DiskType::kPlayer2));
  DropDiskToBoard(vertical_test_2, DiskType::kPlayer2, 4);
  REQUIRE(CheckForWinner(vertical_test_2, DiskType::kPlayer2));


  // Section 2: Horizontal winner
  Board horizontal_test_1;
  InitBoard(horizontal_test_1);
  for (unsigned int i = 1; i < 4; ++i) {
    DropDiskToBoard(horizontal_test_1, DiskType::kPlayer1, i);
  }
  REQUIRE_FALSE(CheckForWinner(horizontal_test_1, DiskType::kPlayer1));
  DropDiskToBoard(horizontal_test_1, DiskType::kPlayer1, 4);
  REQUIRE(CheckForWinner(horizontal_test_1, DiskType::kPlayer1));

  Board horizontal_test_2;
  InitBoard(horizontal_test_2);
  for (unsigned int i = 1; i < 4; ++i) {
    DropDiskToBoard(horizontal_test_2, DiskType::kPlayer2, i);
  }
  REQUIRE_FALSE(CheckForWinner(horizontal_test_2, DiskType::kPlayer2));
  DropDiskToBoard(horizontal_test_2, DiskType::kPlayer2, 4);
  REQUIRE(CheckForWinner(horizontal_test_2, DiskType::kPlayer2));


  // Section 3: Left diagonal winner
  Board left_diagonal_test_1;
  InitBoard(left_diagonal_test_1);
  for (unsigned int i = 0; i < 4; ++i) {
    for (unsigned int j = 3; j > i; --j) {
      DropDiskToBoard(left_diagonal_test_1, DiskType::kPlayer2, i + 1);
    }
  }
  for (unsigned int i = 0; i < 3; ++i) {
    DropDiskToBoard(left_diagonal_test_1, DiskType::kPlayer1, i + 1);
  }
  REQUIRE_FALSE(CheckForWinner(left_diagonal_test_1, DiskType::kPlayer1));
  DropDiskToBoard(left_diagonal_test_1, DiskType::kPlayer1, 4);
  REQUIRE(CheckForWinner(left_diagonal_test_1, DiskType::kPlayer1));

  Board left_diagonal_test_2;
  InitBoard(left_diagonal_test_2);
  for (unsigned int i = 0; i < 4; ++i) {
    for (unsigned int j = 3; j > i; --j) {
      DropDiskToBoard(left_diagonal_test_2, DiskType::kPlayer1, i + 1);
    }
  }
  for (unsigned int i = 0; i < 3; ++i) {
    DropDiskToBoard(left_diagonal_test_2, DiskType::kPlayer2, i + 1);
  }
  REQUIRE_FALSE(CheckForWinner(left_diagonal_test_2, DiskType::kPlayer2));
  DropDiskToBoard(left_diagonal_test_2, DiskType::kPlayer2, 4);
  REQUIRE(CheckForWinner(left_diagonal_test_2, DiskType::kPlayer2));


  // Section 4: Right diagonal winner
  Board right_diagonal_test_1;
  InitBoard(right_diagonal_test_1);
  for (unsigned int i = 0; i < 4; ++i) {
    for (unsigned int j = 0; j <= i; ++j) {
      DropDiskToBoard(right_diagonal_test_1, DiskType::kPlayer2, i + 2);
    }
  }
  for (unsigned int i = 0; i < 3; ++i) {
    DropDiskToBoard(right_diagonal_test_1, DiskType::kPlayer1, i + 2);
  }
  REQUIRE_FALSE(CheckForWinner(right_diagonal_test_1, DiskType::kPlayer1));
  DropDiskToBoard(right_diagonal_test_1, DiskType::kPlayer1, 5);
  REQUIRE(CheckForWinner(right_diagonal_test_1, DiskType::kPlayer1));

  Board right_diagonal_test_2;
  InitBoard(right_diagonal_test_2);
  for (unsigned int i = 0; i < 4; ++i) {
    for (unsigned int j = 0; j <= i; ++j) {
      DropDiskToBoard(right_diagonal_test_2, DiskType::kPlayer1, i + 2);
    }
  }
  for (unsigned int i = 0; i < 3; ++i) {
    DropDiskToBoard(right_diagonal_test_2, DiskType::kPlayer2, i + 2);
  }
  REQUIRE_FALSE(CheckForWinner(right_diagonal_test_2, DiskType::kPlayer2));
  DropDiskToBoard(right_diagonal_test_2, DiskType::kPlayer2, 5);
  REQUIRE(CheckForWinner(right_diagonal_test_2, DiskType::kPlayer2));


  // Section 5: No winner
  Board no_winner_test;
  REQUIRE_FALSE(CheckForWinner(no_winner_test, DiskType::kPlayer1));
  InitBoard(no_winner_test);
  REQUIRE_FALSE(CheckForWinner(no_winner_test, DiskType::kPlayer1));
  DropDiskToBoard(no_winner_test, DiskType::kPlayer1, 5);
  DropDiskToBoard(no_winner_test, DiskType::kPlayer1, 4);
  DropDiskToBoard(no_winner_test, DiskType::kPlayer1, 3);
  REQUIRE_FALSE(CheckForWinner(no_winner_test, DiskType::kPlayer1));
  REQUIRE_FALSE(CheckForWinner(no_winner_test, DiskType::kPlayer2));
  REQUIRE_FALSE(CheckForWinner(vertical_test_1, DiskType::kPlayer2));

  // Section 6: Multiple winners
  Board two_winners_test_right;
  InitBoard(two_winners_test_right);
  for (unsigned int i = 0; i < 5; ++i) {
    if (i == 1) {
      DropDiskToBoard(two_winners_test_right, DiskType::kPlayer2, i);
    } else {
      DropDiskToBoard(two_winners_test_right, DiskType::kPlayer1, i);
    }
  }
  for (unsigned int i = 0; i < 5; ++i) {
    if (i == 0 || i == 2) {
      DropDiskToBoard(two_winners_test_right, DiskType::kPlayer2, i);
    } else {
      DropDiskToBoard(two_winners_test_right, DiskType::kPlayer1, i);
    }
  }
  for (unsigned int i = 0; i < 5; ++i) {
    if (i == 2 || i == 4) {
      DropDiskToBoard(two_winners_test_right, DiskType::kPlayer1, i);
    } else {
      DropDiskToBoard(two_winners_test_right, DiskType::kPlayer2, i);
    }
  }
  for (unsigned int i = 0; i < 5; ++i) {
    if (i == 3) {
      DropDiskToBoard(two_winners_test_right, DiskType::kPlayer1, i);
    } else {
      DropDiskToBoard(two_winners_test_right, DiskType::kPlayer2, i);
    }
  }
  REQUIRE(CheckForWinner(two_winners_test_right, DiskType::kPlayer1));
  REQUIRE(CheckForWinner(two_winners_test_right, DiskType::kPlayer2));


  Board two_winners_test_left;
  InitBoard(two_winners_test_left);
  for (unsigned int i = 0; i < 5; ++i) {
    if (i == 1) {
      DropDiskToBoard(two_winners_test_left, DiskType::kPlayer2, 6 - i);
    } else {
      DropDiskToBoard(two_winners_test_left, DiskType::kPlayer1, 6 - i);
    }
  }
  for (unsigned int i = 0; i < 5; ++i) {
    if (i == 2 || i == 0) {
      DropDiskToBoard(two_winners_test_left, DiskType::kPlayer2, 6 - i);
    } else {
      DropDiskToBoard(two_winners_test_left, DiskType::kPlayer1, 6 - i);
    }
  }
  for (unsigned int i = 0; i < 5; ++i) {
    if (i == 2 || i == 4) {
      DropDiskToBoard(two_winners_test_left, DiskType::kPlayer1, 6 - i);
    } else {
      DropDiskToBoard(two_winners_test_left, DiskType::kPlayer2, 6 - i);
    }
  }
  for (unsigned int i = 0; i < 5; ++i) {
    if (i == 3) {
      DropDiskToBoard(two_winners_test_left, DiskType::kPlayer1, 6 - i);
    } else {
      DropDiskToBoard(two_winners_test_left, DiskType::kPlayer2, 6 - i);
    }
  }
  REQUIRE(CheckForWinner(two_winners_test_left, DiskType::kPlayer1));
  REQUIRE(CheckForWinner(two_winners_test_left, DiskType::kPlayer2));

  // Same winner two ways
  Board same_player1;
  InitBoard(same_player1);
  for (unsigned int i = 0; i < 4; ++i) {
    DropDiskToBoard(same_player1, DiskType::kPlayer1, i);
  }
  for (unsigned int i = 0; i < 3; ++i) {
    DropDiskToBoard(same_player1, DiskType::kPlayer1, 0);
  }
  REQUIRE(CheckForWinner(same_player1, DiskType::kPlayer1));

  Board same_player2;
  InitBoard(same_player2);
  for (unsigned int i = 0; i < 4; ++i) {
    DropDiskToBoard(same_player2, DiskType::kPlayer2, i);
  }
  for (unsigned int i = 0; i < 3; ++i) {
    DropDiskToBoard(same_player2, DiskType::kPlayer2, 0);
  }
  REQUIRE(CheckForWinner(same_player2, DiskType::kPlayer2));

  // Another test idea: someone wins with more than 4
  Board more_than_4;
  InitBoard(more_than_4);
  for (unsigned int i = 0; i < 5; ++i) {
    DropDiskToBoard(more_than_4, DiskType::kPlayer2, i);
  }
  REQUIRE(CheckForWinner(more_than_4, DiskType::kPlayer2));


  // Entire board is one player
  Board all_1;
  InitBoard(all_1);
  for (unsigned int i = 0; i < kBoardHeight; ++i) {
    for (unsigned int j = 0; j < kBoardWidth; ++j) {
      all_1.board[i][j] = DiskType::kPlayer1;
    }
  }
  REQUIRE(CheckForWinner(all_1, DiskType::kPlayer1));

  Board all_2;
  InitBoard(all_2);
  for (unsigned int i = 0; i < kBoardHeight; ++i) {
    for (unsigned int j = 0; j < kBoardWidth; ++j) {
      all_2.board[i][j] = DiskType::kPlayer2;
    }
  }
  REQUIRE(CheckForWinner(all_2, DiskType::kPlayer2));

  // Horizontal win middle
  // Horizontal win in the middle
  Board ho_mid_1;
  InitBoard(ho_mid_1);
  for (unsigned int i = 0; i < 4; ++i) {
    for (unsigned int j = 0; j < 4; ++j) {
      ho_mid_1.board[i + 2][j + 2] = DiskType::kPlayer1;
    }
  }
  REQUIRE(CheckForWinner(ho_mid_1, DiskType::kPlayer1));

  Board ho_mid_2;
  InitBoard(ho_mid_2);
  for (unsigned int i = 0; i < 4; ++i) {
    for (unsigned int j = 0; j < 4; ++j) {
      ho_mid_2.board[i + 1][j + 1] = DiskType::kPlayer2;
    }
  }
  REQUIRE(CheckForWinner(ho_mid_2, DiskType::kPlayer2));

}

/////////////////////////////////////////////////////////////////////////////////////////////