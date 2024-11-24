#include "text.h"
#include <iostream>
#include <iomanip>
#include "board.h"

// Constants
const int BOARD_GAP = 9;
const int BOARD_WIDTH = 11;
const int BOARD_HEIGHT = 15;

Text::Text(Controller* controller) : View{controller} {}

Text::~Text(){
  controller->detachView(this);
}

void printBoardBorder(Controller* controller, std::ostream& out){
  for(Board* board : controller->getBoards()){
    for(int i = 0; i < BOARD_WIDTH; i++) out << '=';
    for(int i = 0; i < BOARD_GAP; i++) out << ' ';
  }
  out << std::endl;
}

void Text::notify(){
  // Print score
  for(Board* board : controller->getBoards()){
    out << "Score: " << std::setw(BOARD_WIDTH + BOARD_GAP - 7) << std::left << std::setfill(' ')
        <<  board->getScore();
    out << resetiosflags(std::ios::showbase);
  }
  out << std::endl;

  // Print top border
  printBoardBorder(controller, out);

  // Print board itself
  for(int i = 0; i < BOARD_HEIGHT; i++){
    for(Board* board : controller->getBoards()){
      const Board* board = board->getBoard();
      for(int j = 0; j < BOARD_WIDTH; j++) out << board[i][j]->getChar();
      for(int j = 0; j < BOARD_GAP; j++) out << ' ';
    }
  }

  // Print bottom border
  printBoardBorder(controller, out);

  // Print next block for each board
  for(Board* board : controller->getBoards()){
    out << std::setw(BOARD_WIDTH + BOARD_GAP) << std::left << std::setfill(' ')
        << "Next Block:";
    out << resetiosflags(std::ios::showbase);
  }
  out << std::endl;
  // Printing the block itself
  for(int i = 0; i < 4; i++){
    for(Board* board : controller->getBoards()){
      // TODO
    }
    out << std::endl;
  }
}
