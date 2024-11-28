#include "graphic.h"
#include <memory>
#include "board.h"
#include "controller.h"
#include "window.h"
using namespace std;

// Constants
const int BOARD_GAP = 9;
const int BOARD_WIDTH = 11;
const int BOARD_HEIGHT = 15;
const int BOARD_BUFFER = 6;
const int BORDER_WIDTH = 1;
const int SCALE_FACTOR = 10;
const int NUMBER_OF_PLAYERS = 2;
const int HALF_LINE = 5;
const int BOARD_BOT_POS = HALF_LINE * 12 + BOARD_HEIGHT * SCALE_FACTOR;

// Helper for converting block type (char) to the colour
int getColour(const char c){
  if(c == ' ') return Xwindow::White;
  else if(c == 'I') return Xwindow::Cyan;
  else if(c == 'J') return Xwindow::Blue;
  else if(c == 'L') return Xwindow::Orange;
  else if(c == 'O') return Xwindow::Yellow;
  else if(c == 'S') return Xwindow::Green;
  else if(c == 'T') return Xwindow::Purple;
  else if(c == 'Z') return Xwindow::Red;
  else if(c == '*') return Xwindow::Brown;
  return Xwindow::Black;
}

Graphic::Graphic(Controller* controller) :
  controller{controller},
  window{(SCALE_FACTOR * NUMBER_OF_PLAYERS * (BOARD_GAP + BOARD_WIDTH)), (SCALE_FACTOR * (BOARD_HEIGHT + BOARD_BUFFER + SCALE_FACTOR))}{
  // Draw the basic shape of the boards, fill them in with notify() later
  // draw static stuff here
	controller->attachView(this);
  window.drawString(HALF_LINE, HALF_LINE * 3, "Biquadris");
  window.fillRectangle(0, HALF_LINE * 4, window.getWidth(), 1, 1);

  int offset = 6;
  for(const unique_ptr<Board>& board : controller->getBoards()){
    // Draw Header (score + level)
    window.drawString(offset - BORDER_WIDTH, HALF_LINE * 7, "  Level: ");
    window.drawString(offset + 50, HALF_LINE * 7, to_string(board->getLevel()));
    window.drawString(offset - BORDER_WIDTH, HALF_LINE * 9, "  Score: ");
    window.drawString(offset + 50, HALF_LINE * 9, to_string(board->getScore()));
    window.drawString(offset - BORDER_WIDTH, HALF_LINE * 11, "HiScore: ");
    window.drawString(offset + 50, HALF_LINE * 11, to_string(board->getHighScore()));

    // Draw board outline
    window.fillRectangle(offset - BORDER_WIDTH, HALF_LINE * 12, BOARD_WIDTH * SCALE_FACTOR + BORDER_WIDTH, BORDER_WIDTH, Xwindow::Black);
    window.fillRectangle(offset - BORDER_WIDTH, HALF_LINE * 12, BORDER_WIDTH, BOARD_HEIGHT * SCALE_FACTOR + BORDER_WIDTH, Xwindow::Black);
    window.fillRectangle(offset - BORDER_WIDTH, BOARD_BOT_POS + BORDER_WIDTH, BOARD_WIDTH * SCALE_FACTOR + BORDER_WIDTH, BORDER_WIDTH, Xwindow::Black);
    window.fillRectangle(offset + (BOARD_WIDTH * SCALE_FACTOR), HALF_LINE * 12, BORDER_WIDTH, BOARD_HEIGHT * SCALE_FACTOR + 2 * BORDER_WIDTH, Xwindow::Black);

    // draw starting block
    const vector<vector<shared_ptr<Block>>> theBoard = board->getTheBoard();
    for(int j = 0; j < BOARD_WIDTH; j++){
      int cellColour = Xwindow::White;
      if(theBoard[BOARD_HEIGHT - 1][j] != nullptr) cellColour = getColour(theBoard[BOARD_HEIGHT - 1][j]->getType());
      window.fillRectangle(offset + j * SCALE_FACTOR, HALF_LINE * 12 + BORDER_WIDTH, SCALE_FACTOR, SCALE_FACTOR, cellColour);
    }

    // Draw footer (next block area)
    window.drawString(offset - BORDER_WIDTH, BOARD_BOT_POS + HALF_LINE * 3, "Next Block:");
    // Printing the next block itself
    window.fillRectangle(offset + HALF_LINE, BOARD_BOT_POS + HALF_LINE * 4, 4 * SCALE_FACTOR, 2 * SCALE_FACTOR, 0);
    const char nextType = board->getNextBlock()->getType();
    if(nextType == 'I'){
      window.fillRectangle(offset + HALF_LINE, BOARD_BOT_POS + HALF_LINE * 4, 4 * SCALE_FACTOR, SCALE_FACTOR, getColour(nextType));
    }
    else if(nextType == 'J'){
      window.fillRectangle(offset + HALF_LINE, BOARD_BOT_POS + HALF_LINE * 4, SCALE_FACTOR, SCALE_FACTOR, getColour(nextType));
      window.fillRectangle(offset + HALF_LINE, BOARD_BOT_POS + HALF_LINE * 6, 3 * SCALE_FACTOR, SCALE_FACTOR, getColour(nextType));
    }
    else if(nextType == 'L'){
      window.fillRectangle(offset + HALF_LINE, BOARD_BOT_POS + HALF_LINE * 4, 3 * SCALE_FACTOR, SCALE_FACTOR, getColour(nextType));
      window.fillRectangle(offset + HALF_LINE, BOARD_BOT_POS + HALF_LINE * 6, SCALE_FACTOR, SCALE_FACTOR, getColour(nextType));
    }
    else if(nextType == 'O'){
      window.fillRectangle(offset + HALF_LINE, BOARD_BOT_POS + HALF_LINE * 4, 2 * SCALE_FACTOR, 2 * SCALE_FACTOR, getColour(nextType));
    }
    else if(nextType == 'S'){
      window.fillRectangle(offset + HALF_LINE + SCALE_FACTOR, BOARD_BOT_POS + HALF_LINE * 4, 2 * SCALE_FACTOR, SCALE_FACTOR, getColour(nextType));
      window.fillRectangle(offset + HALF_LINE, BOARD_BOT_POS + HALF_LINE * 6, 2 * SCALE_FACTOR, SCALE_FACTOR, getColour(nextType));
    }
    else if(nextType == 'T'){
      window.fillRectangle(offset + HALF_LINE, BOARD_BOT_POS + HALF_LINE * 4, 3 * SCALE_FACTOR, SCALE_FACTOR, getColour(nextType));
      window.fillRectangle(offset + HALF_LINE + SCALE_FACTOR, BOARD_BOT_POS + HALF_LINE * 6, SCALE_FACTOR, SCALE_FACTOR, getColour(nextType));
    }
    else if(nextType == 'Z'){
      window.fillRectangle(offset + HALF_LINE, BOARD_BOT_POS + HALF_LINE * 4, 2 * SCALE_FACTOR, SCALE_FACTOR, getColour(nextType));
      window.fillRectangle(offset + HALF_LINE + SCALE_FACTOR, BOARD_BOT_POS + HALF_LINE * 6, 2 * SCALE_FACTOR, SCALE_FACTOR, getColour(nextType));
    }
    offset += SCALE_FACTOR * (BOARD_WIDTH + BOARD_GAP);
  }
}

Graphic::~Graphic() {controller->detachView(this);}

void Graphic::notify(){
  const unique_ptr<Board>& board = controller->getBoard(); // get Board of current player
  auto theBoard = board->getTheBoard(); // get the 2d array of that Board
  const int offset = controller->getCurrentPlayer() * SCALE_FACTOR * (BOARD_WIDTH + BOARD_GAP) + HALF_LINE + BORDER_WIDTH; // how far to right to print

  // Print level, score, high score
  window.fillRectangle(offset + 48, HALF_LINE * 5, 80, HALF_LINE * 2, 0);
  window.fillRectangle(offset + 48, HALF_LINE * 7, 80, HALF_LINE * 2, 0);
	window.fillRectangle(offset + 48, HALF_LINE * 9, 80, HALF_LINE * 2, 0);
  window.drawString(offset + 50, HALF_LINE * 7, to_string(board->getLevel()));
  window.drawString(offset + 50, HALF_LINE * 9, to_string(board->getScore()));
  window.drawString(offset + 50, HALF_LINE * 11, to_string(board->getHighScore()));

  // Print board itself but only of current player (that's the only one that will change)
  for(int i = 0; i < BOARD_HEIGHT; i++){
    for(int j = 0; j < BOARD_WIDTH; j++){
      int cellColour = Xwindow::White;
      if(board->isBlind() && i >= 5 && i < 15 && j >= 5 && j < 12) cellColour = Xwindow::Black; // blind
      else if(theBoard[i][j] != nullptr) cellColour = getColour(theBoard[i][j]->getType());
			window.fillRectangle(offset + j * SCALE_FACTOR, HALF_LINE * 12 + BORDER_WIDTH + (BOARD_HEIGHT - i - 1) * SCALE_FACTOR, SCALE_FACTOR, SCALE_FACTOR, cellColour);
    }
  }

  // Printing the block itself
  window.fillRectangle(offset + HALF_LINE, BOARD_BOT_POS + HALF_LINE * 4, 4 * SCALE_FACTOR, 2 * SCALE_FACTOR, 0);
  const char nextType = board->getNextBlock()->getType();
  if(nextType == 'I'){
    window.fillRectangle(offset + HALF_LINE, BOARD_BOT_POS + HALF_LINE * 4, 4 * SCALE_FACTOR, SCALE_FACTOR, getColour(nextType));
  }
  else if(nextType == 'J'){
    window.fillRectangle(offset + HALF_LINE, BOARD_BOT_POS + HALF_LINE * 4, SCALE_FACTOR, SCALE_FACTOR, getColour(nextType));
    window.fillRectangle(offset + HALF_LINE, BOARD_BOT_POS + HALF_LINE * 6, 3 * SCALE_FACTOR, SCALE_FACTOR, getColour(nextType));
  }
  else if(nextType == 'L'){
    window.fillRectangle(offset + HALF_LINE, BOARD_BOT_POS + HALF_LINE * 4, 3 * SCALE_FACTOR, SCALE_FACTOR, getColour(nextType));
    window.fillRectangle(offset + HALF_LINE, BOARD_BOT_POS + HALF_LINE * 6, SCALE_FACTOR, SCALE_FACTOR, getColour(nextType));
  }
  else if(nextType == 'O'){
    window.fillRectangle(offset + HALF_LINE, BOARD_BOT_POS + HALF_LINE * 4, 2 * SCALE_FACTOR, 2 * SCALE_FACTOR, getColour(nextType));
  }
  else if(nextType == 'S'){
    window.fillRectangle(offset + HALF_LINE + SCALE_FACTOR, BOARD_BOT_POS + HALF_LINE * 4, 2 * SCALE_FACTOR, SCALE_FACTOR, getColour(nextType));
    window.fillRectangle(offset + HALF_LINE, BOARD_BOT_POS + HALF_LINE * 6, 2 * SCALE_FACTOR, SCALE_FACTOR, getColour(nextType));
  }
  else if(nextType == 'T'){
    window.fillRectangle(offset + HALF_LINE, BOARD_BOT_POS + HALF_LINE * 4, 3 * SCALE_FACTOR, SCALE_FACTOR, getColour(nextType));
    window.fillRectangle(offset + HALF_LINE + SCALE_FACTOR, BOARD_BOT_POS + HALF_LINE * 6, SCALE_FACTOR, SCALE_FACTOR, getColour(nextType));
  }
  else if(nextType == 'Z'){
    window.fillRectangle(offset + HALF_LINE, BOARD_BOT_POS + HALF_LINE * 4, 2 * SCALE_FACTOR, SCALE_FACTOR, getColour(nextType));
    window.fillRectangle(offset + HALF_LINE + SCALE_FACTOR, BOARD_BOT_POS + HALF_LINE * 6, 2 * SCALE_FACTOR, SCALE_FACTOR, getColour(nextType));
  }
}
