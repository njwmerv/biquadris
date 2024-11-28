#include "text.h"
#include <iostream>
#include <iomanip>
#include <string>
#include "board.h"
#include "controller.h"
using namespace std;

// Constants
const int NUMBER_PLAYERS = 2;
const int BOARD_GAP = 9;
const int BOARD_WIDTH = 11;
const int BOARD_HEIGHT = 15;
const int BORDER_WIDTH = 1;
const char DIVIDER = '-';
const char HORIZONTAL_BORDER = '=';
const char VERTICAL_BORDER = '|';
const char BLIND_CHAR = '?';
const string LEVEL_TEXT = "Level: ";
const string SCORE_TEXT = "Score: ";
const string HIGHSCORE_TEXT = "HiScore: ";
const string NEXT_BLOCK_TEXT = "Next Block:";

Text::Text(Controller* controller) : controller{controller} {controller->attachView(this);}

Text::~Text(){
  controller->detachView(this);
}

void printBoardBorder(Controller* controller, ostream& out){
  for(Board* board : controller->getBoards()){
    for(int i = 0; i < BOARD_WIDTH + 2 * BORDER_WIDTH; i++) out << HORIZONTAL_BORDER;
    for(int i = 0; i < BOARD_GAP - 2 * BORDER_WIDTH; i++) out << ' ';
  }
  out << endl;
}

void Text::notify(){
	if(controller->getBoard()->getGameState() == Board::GameState::FINISHED_TURN) return;

	// Print frame border
	for(int i = 0; i < NUMBER_PLAYERS * (BOARD_WIDTH + BOARD_GAP); i++) out << DIVIDER;
	out << endl;
  // Print level
  for(Board* board : controller->getBoards()){
    out << LEVEL_TEXT << setw(BOARD_WIDTH + BOARD_GAP - LEVEL_TEXT.length()) << left << setfill(' ')
        << board->getLevel();
    out << resetiosflags(ios::showbase);
  }
  out << endl;

  // Print score
  for(Board* board : controller->getBoards()){
    out << SCORE_TEXT << setw(BOARD_WIDTH + BOARD_GAP - SCORE_TEXT.length()) << left << setfill(' ')
        <<  board->getScore();
    out << resetiosflags(ios::showbase);
  }
  out << endl;

	// Print high score
	for(Board* board : controller->getBoards()){
		out << HIGHSCORE_TEXT << setw(BOARD_WIDTH + BOARD_GAP - HIGHSCORE_TEXT.length()) << left << setfill(' ')
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
      out << VERTICAL_BORDER;
      for(int j = 0; j < BOARD_WIDTH; j++){
				if(board->isBlind() && i >= 2 && i < 12 && j >= 2 && j < 9) out << BLIND_CHAR; // if blind
        else if(theBoard[i][j] != nullptr) out << theBoard[i][j]->getType(); // otherwise use block type
        else out << ' '; // if no block there, empty
      }
      out << VERTICAL_BORDER;
      for(int j = 0; j < BOARD_GAP - 2; j++) out << ' ';
    }
    out << endl;
  }

  // Print bottom border
  printBoardBorder(controller, out);

  // Print next block for each board
  for(Board* board : controller->getBoards()){
    out << setw(BOARD_WIDTH + BOARD_GAP) << left << setfill(' ')
        << NEXT_BLOCK_TEXT;
    out << resetiosflags(ios::showbase);
  }
  out << std::endl;
  // Printing the block itself
  for(Board* board : controller->getBoards()){ // print top half
    Block* currentBlock = board->getCurrentBlock();
    const char type = currentBlock->getType();
    if(type == 'I'){
      out << setw(BOARD_WIDTH + BOARD_GAP) << left << setfill(' ')
          << "IIII";
    }
    else if(type == 'J'){
      out << setw(BOARD_WIDTH + BOARD_GAP) << left << setfill(' ')
          << "JJJ";
    }
    else if(type == 'L'){
      out << setw(BOARD_WIDTH + BOARD_GAP) << left << setfill(' ')
          << "LLL";
    }
    else if(type == 'S'){
      out << setw(BOARD_WIDTH + BOARD_GAP) << left << setfill(' ')
          << " SS";
    }
    else if(type == 'Z'){
      out << setw(BOARD_WIDTH + BOARD_GAP) << left << setfill(' ')
          << "ZZ";
    }
    else if(type == 'O'){
      out << setw(BOARD_WIDTH + BOARD_GAP) << left << setfill(' ')
          << "OO";
    }
    else if(type == 'T'){
      out << setw(BOARD_WIDTH + BOARD_GAP) << left << setfill(' ')
          << "TTT";
    }
    out << resetiosflags(ios::showbase);
  }
  out << endl;
  for(Board* board : controller->getBoards()){ // print bottom half
    Block* currentBlock = board->getCurrentBlock();
    const char type = currentBlock->getType();
    if(type == 'I'){
      out << setw(BOARD_WIDTH + BOARD_GAP) << left << setfill(' ')
          << "";
    }
    else if(type == 'J'){
      out << setw(BOARD_WIDTH + BOARD_GAP) << left << setfill(' ')
          << "  J";
    }
    else if(type == 'L'){
      out << setw(BOARD_WIDTH + BOARD_GAP) << left << setfill(' ')
          << "L";
    }
    else if(type == 'S'){
      out << setw(BOARD_WIDTH + BOARD_GAP) << left << setfill(' ')
          << "SS";
    }
    else if(type == 'Z'){
      out << setw(BOARD_WIDTH + BOARD_GAP) << left << setfill(' ')
          << " ZZ";
    }
    else if(type == 'O'){
      out << setw(BOARD_WIDTH + BOARD_GAP) << left << setfill(' ')
          << "OO";
    }
    else if(type == 'T'){
      out << setw(BOARD_WIDTH + BOARD_GAP) << left << setfill(' ')
          << " T ";
    }
    out << resetiosflags(ios::showbase);
  }
  out << endl;
}
