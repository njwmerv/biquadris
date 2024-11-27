#include "board.h"
#include <string>
#include <memory>
#include "level.h"
#include "level0.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"
#include "iblock.h"
#include "jblock.h"
#include "lblock.h"
#include "oblock.h"
#include "sblock.h"
#include "zblock.h"
#include "tblock.h"
using namespace std;

const int boardWidth = 11; // max, not reached (start at index 0)
const int boardHeight = 18;

// Big 5
Board::Board(int startingLevel, string level0File):
  score{0}, highScore{0}, level0File{level0File}, currentLevel{startingLevel}, blind{false} {
  for(int i = 0; i < boardHeight; i++) board.emplace_back(vector<shared_ptr<Block>>(boardWidth, nullptr));
  if(startingLevel == 0) level = new Level0{level0File};
  else if(startingLevel == 1) level = new Level1;
  else if(startingLevel == 2) level = new Level2;
  else if(startingLevel == 3) level = new Level3;
  else if(startingLevel == 4) level = new Level4;
  current = shared_ptr<Block>(level->generateBlock());
  next = level->generateBlock();
  addCurrentToBoard();
}

Board::~Board(){
  clearBoard();
  delete level;
}

// Accessors
int Board::getScore() const {return score;}
int Board::getLevel() const {return currentLevel;}
vector<vector<shared_ptr<Block>>> Board::getTheBoard() const {return board;}
Block* Board::getNextBlock() const {return next;}
Block* Board::getCurrentBlock() const {return current.get();}
bool Board::isBlind() const {return blind;}
// Mutators
void Board::setScore(int newScore){score = newScore;}

void Board::levelup(){
  if(currentLevel == 4) return;
  delete level;
  currentLevel++;
  if(currentLevel == 1) level = new Level1;
  else if(currentLevel == 2) level = new Level2;
  else if(currentLevel == 3) level = new Level3;
  else if(currentLevel == 4) level = new Level4;
}

void Board::leveldown(){
  if(currentLevel == 0) return;
  delete level;
  currentLevel--;
  if(currentLevel == 0) level = new Level0(level0File);
  else if(currentLevel == 1) level = new Level1;
  else if(currentLevel == 2) level = new Level2;
  else if(currentLevel == 3) level = new Level3;
}

void Board::clearBoard(){
  for(auto row : board){
    for(auto cell : row){
      cell.reset();
    }
  }
}

void Board::forceBlock(const string type){
  auto cellsOfBlock = current->getRotation(current->getNumRotations());
  const int curX = current->getX();
  const int curY = current->getY();
  for(auto cell : cellsOfBlock){ // this should delete the current block completely
    board[cell.second + curY][cell.first + curX].reset();
  }
  current.reset();
  if(type == "I") current = shared_ptr<Block>(new IBlock(currentLevel));
  else if(type == "J") current = shared_ptr<Block>(new JBlock(currentLevel));
  else if(type == "L") current = shared_ptr<Block>(new LBlock(currentLevel));
  else if(type == "O") current = shared_ptr<Block>(new OBlock(currentLevel));
  else if(type == "S") current = shared_ptr<Block>(new SBlock(currentLevel));
  else if(type == "Z") current = shared_ptr<Block>(new ZBlock(currentLevel));
  else current = shared_ptr<Block>(new TBlock(currentLevel));
  addCurrentToBoard();
}

void Board::forceLevel(const int newLevel){
  if(newLevel == currentLevel) return;
  delete level;
  if(newLevel == 0) level = new Level0(level0File);
  else if(newLevel == 1) level = new Level1;
  else if(newLevel == 2) level = new Level2;
  else if(newLevel == 3) level = new Level3;
  else level = new Level4;
}

void Board :: down () {
  int curX = current->getX();
  int curY = current->getY();
  int curNumRot = current->getNumRotations();
  for(pair<int, int> cell : current->getRotation(curNumRot)) {
    if(cell.second + curY - 1 < 0) continue;
    if(board[cell.first + curX][cell.second + curY - 1] != nullptr && 
       board[cell.first + curX][cell.second + curY - 1] != current) {
      return;
    }
  }
  for(pair<int, int> cell : current->getRotation(curNumRot)) {
    board[cell.first + curX][cell.second + curY] = nullptr;
  }
  current->setY(curY-1);
  for(pair<int, int> cell : current->getRotation(curNumRot)) {
    board[cell.first + curX][cell.second + curY] = current;
  }
}

void Board :: right() {
  // accessing the properties of the current block
  int curX = current->getX();
  int curY = current->getY();
  int curNumRot = current->getNumRotations();

  bool willDrop = false; // only used if the block is heavy

  // determining if we are able to move the block to the right
  for(pair<int, int> cell : current->getRotation(curNumRot)) {
    // checking if the cell surpasses the border
    if(cell.first + curX + 1 >= boardWidth) return; 
    // checking if the space next to the cell is empty
    if(board[cell.second + curY][cell.first + curX + 1] != nullptr && 
       board[cell.second + curY][cell.first + curX + 1] != current) {
      return;
    }
    // operations only ran if the cell is heavy
    if(!current->isHeavy()) continue;
    // checking if the cell breaks the border
    if(cell.second + curY - 2 < 0) {
      willDrop = true;
      continue;
    }
    if(board[cell.second + curY - 1][cell.first + curX + 1] != nullptr &&
       board[cell.second + curY - 1][cell.first + curX + 1] != current &&
       board[cell.second + curY - 2][cell.first + curX + 1] != nullptr &&
       board[cell.second + curY - 2][cell.first + curX + 1] != current) {
      willDrop = true;
      continue;
    }
  }
  // erasing the block in the board
  for(pair<int, int> cell : current->getRotation(curNumRot)) {
    board[cell.second + curY][cell.first + curX] = nullptr;
  }
  // updating the block's x coordinate
  current->setX(curX + 1);
  curX = curX + 1;
  // updating the block's y coordinate if it is heavy, and falls without impediment
  if(!willDrop && current->isHeavy()) {
    current->setY(curY - 2);
    curY = curY - 2;
  }
  // adding the block to its new position in the board
  addCurrentToBoard();
  // calling drop() if the block drops due to being heavy and impeded
  if(willDrop) drop();
}

void Board :: left() {
  // accessing the properties of the current block
  int curX = current->getX();
  int curY = current->getY();
  int curNumRot = current->getNumRotations();

  bool willDrop = false; // only used if the block is heavy

  // determining if we are able to move the block to the right
  for(pair<int, int> cell : current->getRotation(curNumRot)) {
    // checking if the cell surpasses the border
    if(cell.first + curX - 1 < 0) return;
    // checking if the space next to the cell is empty
    if(board[cell.second + curY][cell.first + curX - 1] != nullptr &&
       board[cell.second + curY][cell.first + curX - 1] != current) {
      return;
       }
    // operations only ran if the cell is heavy
    if(!current->isHeavy()) continue;
    // checking if the cell breaks the border
    if(cell.second + curY - 2 < 0) {
      willDrop = true;
      continue;
    }
    if(board[cell.second + curY - 1][cell.first + curX - 1] != nullptr &&
       board[cell.second + curY - 1][cell.first + curX - 1] != current &&
       board[cell.second + curY - 2][cell.first + curX - 1] != nullptr &&
       board[cell.second + curY - 2][cell.first + curX - 1] != current) {
      willDrop = true;
      continue;
       }
  }
  // erasing the block in the board
  for(pair<int, int> cell : current->getRotation(curNumRot)) {
    board[cell.second + curY][cell.first + curX] = nullptr;
  }
  // updating the block's x coordinate
  current->setX(curX - 1);
  curX = curX - 1;
  // updating the block's y coordinate if it is heavy, and falls without impediment
  if(!willDrop && current->isHeavy()) {
    current->setY(curY - 2);
    curY = curY - 2;
  }
  // adding the block to its new position in the board
  addCurrentToBoard();
  // calling drop() if the block drops due to being heavy and impeded
  if(willDrop) drop();
}

void Board :: drop() {
  int curX = current->getX();
  int curY = current->getY();
  int curNumRot = current->getNumRotations();
  int smallestDistance = INT_MAX;
  for(pair<int, int> cell : current->getRotation(curNumRot)) {
    int curLoopX = cell.first + curX;
    int count = 0;
    for(int i = cell.second+curY - 1; i >= 0; i--) {
      if(board[curLoopX][i] != nullptr) {
        break;
      }
      count++;
    }
    if(count < smallestDistance) {
      smallestDistance = count;
    }
  }
  for(pair<int, int> cell : current->getRotation(curNumRot)) {
    board[cell.first + curX][cell.second + curY] = nullptr;
  }
  current->setY(curY-smallestDistance);
  for(pair<int, int> cell : current->getRotation(curNumRot)) {
    board[cell.first + curX][cell.second + curY] = current;
  }
  clearRows(); // clears full rows and then increments score accordingly
  current.reset(next); // if you want to specify next, do it when it's generated or just above this line
  addCurrentToBoard();
  /* things that need to be implemented
  - if level 4 -> add to placed blocks counter, if counter % 5 = 0, then place singular block in middle
  */
  if(blind) blind = false;
}

void Board::addCurrentToBoard(){
  const int curX = current->getX();
  const int curY = current->getY();
  vector<pair<int, int>> cellsOfBlock = current->getRotation(current->getNumRotations());
  for(pair<int, int> cell : cellsOfBlock){
    board[cell.second + curY][cell.first + curX] = current;
  }
}

void Board::clearRows() {
  int cleared = 0;
  for (int row = 0; row < 18; row++) {
    bool fullRow = true;

    for (int col = 0; col < 11; ++col) {
      if (!board[row][col]) {
        fullRow = false;
        break;
      }
    }

    if (fullRow) {
      cleared++;
      board.erase(board.begin() + row);
      for(auto cell : board[row]){
        if(cell.use_count() == 1) score += (cell->getLevel() + 1) * (cell->getLevel() + 1);
        cell.reset();
      }
      board.insert(board.begin(), vector<shared_ptr<Block>>(11, nullptr));
      row--;
    }
  }
  score += (cleared + currentLevel) * (cleared + currentLevel);
  if(score > highScore) highScore = score;
}


void Board::clockwise() {
  int curX = current->getX();
  int curY = current->getY();
  int curNumRot = current->getNumRotations();
  
  int newNumRot = (curNumRot + 1) % 4;

  for(pair<int, int> cell : current->getRotation(newNumRot)) {
    int newX = cell.first + oldX;
    int newY = cell.second + oldY;

    if (newX < 0 || newX >= boardWidth || newY < 0 || newY >= boardHeight) {
      return;
    }
    if (board[newY][newX] != nullptr && board[newY][newX] != current) {
      return;
    }
  }

  for(pair<int, int> cell : current->getRotation(curNumRot)) {
    board[curY + cell.second][curX + cell.first] = nullptr;
  } 

  current->clockwise();

  addCurrentToBoard();
}
