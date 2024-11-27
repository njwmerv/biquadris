#include "graphic.h"
#include "board.h"
#include "controller.h"
#include "window.h"
using namespace std;

// Constants
const int BOARD_GAP = 9;
const int BOARD_WIDTH = 11;
const int BOARD_HEIGHT = 15;
const int BOARD_BUFFER = 3;
const int BORDER_WIDTH = 1;
const int SCALE_FACTOR = 10;
const int NUMBER_OF_PLAYERS = 2;

int getColour(const char c){
  if(c == ' ') return Xwindow::White;
  else if(c == 'I') return Xwindow::Cyan;
  else if(c == 'J') return Xwindow::Blue;
  else if(c == 'L') return Xwindow::Orange;
  else if(c == 'O') return Xwindow::Yellow;
  else if(c == 'S') return Xwindow::Green;
  else if(c == 'T') return Xwindow::Purple;
  else if(c == 'Z') return Xwindow::Red;
  return Xwindow::Black;
}

Graphic::Graphic(Controller* controller) :
  controller{controller},
  window{(SCALE_FACTOR * NUMBER_OF_PLAYERS * (BOARD_GAP + BOARD_WIDTH)), (SCALE_FACTOR * (BOARD_HEIGHT + BOARD_BUFFER + 10))}{
  // Draw the basic shape of the boards, fill them in with notify() later
  // draw static stuff here
	controller->attachView(this);
  window.drawString(5, 15, "Biquadris");
  window.fillRectangle(0, 20, window.getWidth(), 1, 1); // TODO draw current when initializing, by including in theBoard

  int offset = 0;
  for(Board* board : controller->getBoards()){
    // Draw Header (score + level)
    window.drawString(offset + 5, 35, "Level: ");
    window.drawString(offset + 5, 45, "Score: ");
    window.drawString(offset + 5 + 38 + 6, 35, to_string(board->getLevel()));
    window.drawString(offset + 5 + 38 + 6, 45, to_string(board->getScore()));

    // Drawing the board and it's starting block
    const vector<vector<shared_ptr<Block>>> theBoard = board->getTheBoard();
    for(int j = 0; j < BOARD_WIDTH; j++){
        int cellColour = Xwindow::White;
        if(theBoard[BOARD_HEIGHT - 1][j] != nullptr) cellColour = getColour(theBoard[BOARD_HEIGHT - 1][j]->getType());
	    window.fillRectangle(offset + j * SCALE_FACTOR, 51 + SCALE_FACTOR, SCALE_FACTOR, SCALE_FACTOR, cellColour);
      }

    // Draw board outline
    window.fillRectangle(offset + 5, 50, BOARD_WIDTH * SCALE_FACTOR + 1, 1, 1);
    window.fillRectangle(offset + 5, 50, 1, BOARD_HEIGHT * SCALE_FACTOR + 1, 1);
    window.fillRectangle(offset + 5, 50 + (BOARD_HEIGHT * SCALE_FACTOR) + 1, BOARD_WIDTH * SCALE_FACTOR + 1, BORDER_WIDTH, 1);
    window.fillRectangle(offset + 5 + (BOARD_WIDTH * SCALE_FACTOR) + 1, 50, BORDER_WIDTH, BOARD_HEIGHT * SCALE_FACTOR + 2, 1);

    // Draw footer (next block area)
    window.drawString(offset + 5, 65 + (BOARD_HEIGHT * SCALE_FACTOR), "Next Block:");
    offset += SCALE_FACTOR * (BOARD_WIDTH + BOARD_GAP);
  }
}

Graphic::~Graphic(){
  controller->detachView(this);
}

void Graphic::notify(){
  const Board* board = controller->getBoard();
  auto theBoard = board->getTheBoard();
  const int offset = controller->getCurrentPlayer() * SCALE_FACTOR * (BOARD_WIDTH + BOARD_GAP) + 6;

  // Print score
  window.fillRectangle(offset + 5 + 36, 25, 80, 10, 0);
  window.fillRectangle(offset + 5 + 36, 35, 80, 10, 0);
  window.drawString(offset + 5 + 38, 35, to_string(board->getLevel()));
  window.drawString(offset + 5 + 38, 45, to_string(board->getScore()));

  // Print board itself but only of current player (that's the only one that will change)
  for(int i = 0; i < BOARD_HEIGHT; i++){
    for(int j = 0; j < BOARD_WIDTH; j++){
      int cellColour = Xwindow::White;
      if(board->isBlind() && i >= 5 && i < 15 && j >= 5 && j < 12) cellColour = Xwindow::Black; // blind
      else if(theBoard[i][j] != nullptr) cellColour = getColour(theBoard[i][j]->getType());
			window.fillRectangle(offset + j * SCALE_FACTOR, 51 + (BOARD_HEIGHT - i - 1) * SCALE_FACTOR, SCALE_FACTOR, SCALE_FACTOR, cellColour);
    }
  }

  // Printing the block itself
  window.fillRectangle(offset + 5, 70 + (BOARD_HEIGHT * SCALE_FACTOR), 4 & SCALE_FACTOR, 2 * SCALE_FACTOR, 0);
  const char nextType = board->getNextBlock()->getType();
  if(nextType == 'I'){
    window.fillRectangle(offset + 5, 70 + (BOARD_HEIGHT * SCALE_FACTOR), 4 * SCALE_FACTOR, SCALE_FACTOR, getColour(nextType));
  }
  else if(nextType == 'J'){
    window.fillRectangle(offset + 5, 70 + (BOARD_HEIGHT * SCALE_FACTOR), SCALE_FACTOR, SCALE_FACTOR, getColour(nextType));
    window.fillRectangle(offset + 5, 80 + (BOARD_HEIGHT * SCALE_FACTOR), 3 * SCALE_FACTOR, SCALE_FACTOR, getColour(nextType));
  }
  else if(nextType == 'L'){
    window.fillRectangle(offset + 5, 70 + (BOARD_HEIGHT * SCALE_FACTOR), 3 * SCALE_FACTOR, SCALE_FACTOR, getColour(nextType));
    window.fillRectangle(offset + 5, 80 + (BOARD_HEIGHT * SCALE_FACTOR), SCALE_FACTOR, SCALE_FACTOR, getColour(nextType));
  }
  else if(nextType == 'O'){
    window.fillRectangle(offset + 5, 70 + (BOARD_HEIGHT * SCALE_FACTOR), 2 * SCALE_FACTOR, 2 * SCALE_FACTOR, getColour(nextType));
  }
  else if(nextType == 'S'){
    window.fillRectangle(offset + 5 + SCALE_FACTOR, 70 + (BOARD_HEIGHT * SCALE_FACTOR), 2 * SCALE_FACTOR, SCALE_FACTOR, getColour(nextType));
    window.fillRectangle(offset + 5, 80 + (BOARD_HEIGHT * SCALE_FACTOR), 2 * SCALE_FACTOR, SCALE_FACTOR, getColour(nextType));
  }
  else if(nextType == 'T'){
    window.fillRectangle(offset + 5 + SCALE_FACTOR, 70 + (BOARD_HEIGHT * SCALE_FACTOR), 3 * SCALE_FACTOR, SCALE_FACTOR, getColour(nextType));
    window.fillRectangle(offset + 5, 80 + (BOARD_HEIGHT * SCALE_FACTOR), 3 * SCALE_FACTOR, SCALE_FACTOR, getColour(nextType));
  }
  else if(nextType == 'Z'){
    window.fillRectangle(offset + 5, 70 + (BOARD_HEIGHT * SCALE_FACTOR), 2 * SCALE_FACTOR, SCALE_FACTOR, getColour(nextType));
    window.fillRectangle(offset + 5 + SCALE_FACTOR, 80 + (BOARD_HEIGHT * SCALE_FACTOR), 2 * SCALE_FACTOR, SCALE_FACTOR, getColour(nextType));
  }
}
