#include "graphic.h"
#include "board.h"

// Constants
const int BOARD_GAP = 9;
const int BOARD_WIDTH = 11;
const int BOARD_HEIGHT = 15;
const int BORDER_WIDTH = 1;
const int SCALE_FACTOR = 5;
const int NUMBER_OF_PLAYERS = 2;

Graphic::Graphic(Controller* controller) :
  View{controller},
  window{(SCALE_FACTOR * NUMBER_OF_PLAYERS * (BOARD_GAP + BOARD_WIDTH)), (SCALE_FACTOR * (BOARD_HEIGHT + 5))}{
  // Draw the basic shape of the boards, fill them in with notify() later
  // draw static stuff here
  int offset = 0;
  for(Board* board : controller->getBoards()){
    // Draw Header (score)

    // Draw board outline

    // Draw footer (next block area)

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
}

void Graphic::notify(){
  const Board* board = controller->getBoard(); // calculate offset by getting current player
  // modulo by number of players, but maybe just make that built into nextPlayer() but that's next time
  const int offset = controller->getCurrentPlayer();

  // Print score
  window.drawString(0, 0, "Score: " + board->getScore()));

  // Print board itself but only of current player (that's the only one that will change)
  for(int i = 0; i < BOARD_HEIGHT; i++){
    for(int j = 0; j < BOARD_WIDTH; j++){
      const int cellColour = board[i][j]->getType();
      window.fillRectangle(i * SCALE_FACTOR, j * SCALE_FACTOR, SCALE_FACTOR, SCALE_FACTOR, cellColour);
    }
  }

  // Printing the block itself
  // TODO
}
