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
Board::Board(int startingLevel, string level0File) : score{0}, level0File{level0File}, currentLevel{startingLevel} {
  for(int i = 0; i < boardHeight; i++){
    vector<shared_ptr<Block>> row;
    for(int j = 0; j < boardWidth; j++) row.emplace_back(nullptr);
    board.emplace_back(row);
  }
  if(startingLevel == 0) level = new Level0{level0File};
  else if(startingLevel == 1) level = new Level1;
  else if(startingLevel == 2) level = new Level2;
  else if(startingLevel == 3) level = new Level3;
  else if(startingLevel == 4) level = new Level4;
  current = level->generateBlock();
  next = level->generateBlock();
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
Block* Board::getCurrentBlock() const {return current;}

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

Block* Board::forceBlock(const string type){
  if(type == "I") return new IBlock(1);
  else if(type == "J") return new JBlock(1);
  else if(type == "L") return new LBlock(1);
  else if(type == "O") return new OBlock(1);
  else if(type == "S") return new SBlock(1);
  else if(type == "Z") return new ZBlock(1);
  else return new TBlock(1);
}

Level* Board::forceLevel(const int newLevel){
  if(newLevel == 0) return new Level0(level0File);
  else if(newLevel == 1) return new Level1;
  else if(newLevel == 2) return new Level2;
  else if(newLevel == 3) return new Level3;
  else return new Level4;
}

void Board :: down () {
  int curX = current->getX();
  int curY = current->getY();
  int curNumRot = current->getNumRotations();
  for(pair<int, int> cell : current->getRotation(curNumRot)) {
    if(cell.second + curY - 1 <= 0) continue;
    if(board[cell.first + curX][cell.second + curY-1] != nullptr) {
      return;
    }
  }
  current->setY(curY-1);
}

void Board :: right() {
  int curX = current->getX();
  int curY = current->getY();
  int curNumRot = current->getNumRotations();
  for(pair<int, int> cell : current->getRotation(curNumRot)) {
    if(cell.first + curX + 1 >= boardWidth) continue;
    if(board[cell.first + curX + 1][cell.second + curY] != nullptr) {
      return;
    }
    if(!current->isHeavy()) continue;
    if(board[cell.first + curX + 1][cell.second + curY - 1] != nullptr || board[cell.first + curX + 1][cell.second + curY - 2] != nullptr) {
      return;
    }
  }
  current->setX(curX+1);
}

void Board :: left() {
  int curX = current->getX();
  int curY = current->getY();
  int curNumRot = current->getNumRotations();
  for(pair<int, int> cell : current->getRotation(curNumRot)) {
    if(cell.first + curX - 1 <= 0) continue;
    if(board[cell.first + curX - 1][cell.second + curY] != nullptr) {
      return;
    }
    if(!current->isHeavy()) continue;
    if(board[cell.first + curX - 1][cell.second + curY - 1] != nullptr || board[cell.first + curX - 1][cell.second + curY - 2] != nullptr) {
      return;
    }
  }
  current->setX(curX-1);
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
  current->setY(curY-smallestDistance);
  /* things that need to be implemented

  - has a line been cleared? -> score, 
  - set next as current, and create a new next using level (or file!)
  - if level 4 -> add to placed blocks counter, if counter % 5 = 0, then place singular block in middle
  - if blind -> remove blindness
  */
}
