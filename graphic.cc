#include "graphic.h"
#include "board.h"

// Constants
const int BOARD_GAP = 9;
const int BOARD_WIDTH = 11;
const int BOARD_HEIGHT = 15;
const int BORDER_WIDTH = 1;
const int SCALE_FACTOR = 10;
const int NUMBER_OF_PLAYERS = 2;

Graphic::Graphic(Controller* controller) :
  View{controller},
  window{(SCALE_FACTOR * NUMBER_OF_PLAYERS * (BOARD_GAP + BOARD_WIDTH)), (SCALE_FACTOR * (BOARD_HEIGHT + 10))}{
  // Draw the basic shape of the boards, fill them in with notify() later
  // draw static stuff here
  window.drawString(5, 15, "Biquadris");
  window.fillRectangle(0, 20, window.getWidth(), 1, 1);

  int offset = 0;
  for(Board* board : controller->getBoards()){
    // Draw Header (score + level)
    window.drawString(offset + 5, 35, "Level: ");
    window.drawString(offset + 5, 45, "Score: ");

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

int getColour(const char c){
  if(c == ' ') return 0;
  else if(c == 'I') return 2;
  else if(c == 'J') return 3;
  else if(c == 'L') return 4;
  else if(c == 'O') return 5;
  else if(c == 'S') return 6;
  else if(c == 'T') return 7;
  else if(c == 'Z') return 8;
  return 1;
}

void Graphic::notify(){
  const Board* board = controller->getBoard();
  const int offset = controller->getCurrentPlayer() * SCALE_FACTOR * (BOARD_WIDTH + BOARD_GAP);

  // Print score
  window.fillRectangle(offset + 5 + 36, 25, 80, 10, 0);
  window.fillRectangle(offset + 5 + 36, 35, 80, 10, 0);
  window.drawString(offset + 5 + 38, 35, board->getLevel());
  window.drawString(offset + 5 + 38, 45, board->getScore());

  // Print board itself but only of current player (that's the only one that will change)
  for(int i = 0; i < BOARD_HEIGHT; i++){
    for(int j = 0; j < BOARD_WIDTH; j++){
      const int cellColour = getColour(board[i][j]->getType());
      window.fillRectangle(offset + i * SCALE_FACTOR, j * SCALE_FACTOR, SCALE_FACTOR, SCALE_FACTOR, cellColour);
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