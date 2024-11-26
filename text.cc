#include "text.h"
#include <iostream>
#include <iomanip>
#include "board.h"
#include "controller.h"

// Constants
const int BOARD_GAP = 9;
const int BOARD_WIDTH = 11;
const int BOARD_HEIGHT = 15;

Text::Text(Controller* controller) : controller{controller} {controller->attachView(this);}

Text::~Text(){
  controller->detachView(this);
}

void printBoardBorder(Controller* controller, std::ostream& out){
  for(Board* board : controller->getBoards()){
    for(int i = 0; i < BOARD_WIDTH + 2; i++) out << '=';
    for(int i = 0; i < BOARD_GAP - 2; i++) out << ' ';
  }
  out << std::endl;
}

void Text::notify(){
  // Print level
  for(Board* board : controller->getBoards()){
    out << "Level: " << std::setw(BOARD_WIDTH + BOARD_GAP - 7) << std::left << std::setfill(' ')
        <<  board->getLevel();
    out << resetiosflags(std::ios::showbase);
  }
  out << std::endl;

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
      auto theBoard = board->getTheBoard();
      out << "|";
      for(int j = 0; j < BOARD_WIDTH; j++){
        if(theBoard[i][j] != nullptr) out << theBoard[i][j]->getType();
        else out << ' ';
      }
      out << "|";
      for(int j = 0; j < BOARD_GAP - 2; j++) out << ' ';
    }
    out << endl;
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
  for(Board* board : controller->getBoards()){
    out << std::setw(BOARD_WIDTH + BOARD_GAP) << std::left << std::setfill(' ')
        << board->getNextBlock()->getType();
    out << resetiosflags(std::ios::showbase);
  }
  out << std::endl;
}
