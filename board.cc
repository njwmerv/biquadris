#include "board.h"
#include <string>
#include <memory>
#include "level.h"
#include "level0.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"
using namespace std;

// Big 5
Board::Board(int startingLevel, std::string level0File) :
  score{0}, level0File{level0File}, currentLevel{startingLevel} {
  for(int i = 0; i < 15; i++){
    board.emplace_back(vector<shared_ptr<Block>> {nullptr});
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
      if(cell != nullptr) delete cell;
      cell = nullptr;
    }
  }
}

void Board :: down () {
    int curX = current->getX();
    int curY = current->getY();
    int curNumRot  = current->getNumRotations();
    for(pair<int, int> cell : current->getRotation(curNumRot)) {
        if(board[cell.first + curX][cell.second + curY-1] != nullptr) {
            // call something that runs when a block has been placed
            return;
        }
    }
    current->setY(curY-1);
}


void Board :: right() {
    int curX = current->getX();
    int curY = current->getY();
    int curNumRot  = current->getNumRotations();
    for(pair<int, int> cell : current->getRotation(curNumRot)) {
        if(board[cell.first + curX + 1][cell.second + curY] != nullptr) {
            // call something that runs when a block has been placed
            return;
        }
    }
    current->setX(curX+1);
}

void Board :: left() {
    int curX = current->getX();
    int curY = current->getY();
    int curNumRot  = current->getNumRotations();
    for(pair<int, int> cell : current->getRotation(curNumRot)) {
        if(board[cell.first + curX - 1][cell.second + curY] != nullptr) {
            // call something that runs when a block has been placed
            return;
        }
    }
    current->setX(curX-1);
}