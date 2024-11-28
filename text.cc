#include "text.h"
#include <iostream>
#include <iomanip>
#include "board.h"
#include "controller.h"
using namespace std;

// Constants
const int NUMBER_PLAYERS = 2;
const int BOARD_GAP = 9;
const int BOARD_WIDTH = 11;
const int BOARD_HEIGHT = 15;

Text::Text(Controller* controller) : controller{controller} {controller->attachView(this);}

Text::~Text(){
  controller->detachView(this);
}

void printBoardBorder(Controller* controller, ostream& out){
  for(Board* board : controller->getBoards()){
    for(int i = 0; i < BOARD_WIDTH + 2; i++) out << '=';
    for(int i = 0; i < BOARD_GAP - 2; i++) out << ' ';
  }
  out << endl;
}

void Text::notify(){
	if(controller->getBoard()->getGameState() == Board::GameState::FINISHED_TURN) return;

	// Print frame border
	for(int i = 0; i < NUMBER_PLAYERS * (BOARD_WIDTH + BOARD_GAP); i++) out << "-";
	out << endl;
  // Print level
  for(Board* board : controller->getBoards()){
    out << "Level: " << setw(BOARD_WIDTH + BOARD_GAP - 7) << left << setfill(' ')
        << board->getLevel();
    out << resetiosflags(ios::showbase);
  }
  out << endl;

  // Print score
  for(Board* board : controller->getBoards()){
    out << "Score: " << setw(BOARD_WIDTH + BOARD_GAP - 7) << left << setfill(' ')
        <<  board->getScore();
    out << resetiosflags(ios::showbase);
  }
  out << endl;

	// Print high score
	for(Board* board : controller->getBoards()){
		out << "HiScore: " << setw(BOARD_WIDTH + BOARD_GAP - 9) << left << setfill(' ')
				<< board->getHighScore();
		out << resetiosflags(ios::showbase);
	}
	out << endl;

  // Print top border
  printBoardBorder(controller, out);

  // Print board itself
  for(int i = BOARD_HEIGHT - 1; i >= 0; i--){
    for(Board* board : controller->getBoards()){
      auto theBoard = board->getTheBoard();
      out << "|";
      for(int j = 0; j < BOARD_WIDTH; j++){
				if(board->isBlind() && i >= 2 && i < 12 && j >= 2 && j < 9) out << '?';
        else if(theBoard[i][j] != nullptr) out << theBoard[i][j]->getType();
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
    out << setw(BOARD_WIDTH + BOARD_GAP) << left << setfill(' ')
        << "Next Block:";
    out << resetiosflags(ios::showbase);
  }
  out << std::endl;
  // Printing the block itself
  for(Board* board : controller->getBoards()){
    out << setw(BOARD_WIDTH + BOARD_GAP) << left << setfill(' ')
        << board->getNextBlock()->getType();
    out << resetiosflags(ios::showbase);
  }
  out << endl;
}
