#include "text.h"
#include <iostream>
#include <iomanip>

// Constants
const int BOARD_GAP = 9;
const int BOARD_WIDTH = 11;
const int BOARD_HEIGHT = 15;

Text::~Text(){
  controller->detachView(this);
}

void printBoardBorder(Controller* controller, std::ostream& out){
  for(Player* player : controller->getPlayers()){
    for(int i = 0; i < BOARD_WIDTH; i++) out << '=';
    for(int i = 0; i < BOARD_GAP; i++) out << ' ';
  }
  out << std::endl;
}

void Text::notify(){
  // Print score
  for(Player* player : controller->getPlayers()){
    out << "Score: " << std::setw(BOARD_WIDTH + BOARD_GAP - 7) << std::left << std::setfill(' ')
        <<  player->getScore();
    out << resetiosflags(std::ios::showbase);
  }
  out << std::endl;

  // Print top border
  printBoardBorder(controller, out);

  // Print board itself
  for(int i = 0; i < BOARD_HEIGHT; i++){
    for(Player* player : controller->getPlayers()){
      const Board* board = player->getBoard();
      for(int j = 0; j < BOARD_WIDTH; j++) out << board[i][j]->getChar();
      for(int j = 0; j < BOARD_GAP; j++) out << ' ';
    }
  }

  // Print bottom border
  printBoardBorder(controller, out);

  // Print next block for each player
  for(Player* player : controller->getPlayers()){
    out << std::setw(BOARD_WIDTH + BOARD_GAP) << std::left << std::setfill(' ')
        << "Next Block:";
    out << resetiosflags(std::ios::showbase);
  }
  out << std::endl;
  // Printing the block itself
  for(int i = 0; i < 4; i++){
    for(Player* player : controller->getPlayers()){
      // TODO
    }
    out << std::endl;
  }
}
