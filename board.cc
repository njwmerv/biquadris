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
#include "fourblock.h"
using namespace std;

const int boardWidth = 11; // note that the actual board is in the range [0,10]
const int boardBuffer = 3;
const int boardHeight = 15;

// Big 5
Board::Board(int startingLevel, string level0File, Board::GameState gameState) :
  score{0}, highScore{0}, level0File{level0File}, currentLevel{startingLevel}, blind{false}, linesJustCleared{0},
  gameState{gameState} {
  for(int i = 0; i < boardHeight + boardBuffer; i++) board.emplace_back(vector<shared_ptr<Block>>(boardWidth, nullptr));
  if(startingLevel == 0) level = new Level0{level0File};
  else if(startingLevel == 1) level = new Level1;
  else if(startingLevel == 2) level = new Level2;
  else if(startingLevel == 3) level = new Level3;
  else if(startingLevel == 4) level = new Level4;
  current = shared_ptr<Block>(level->generateBlock());
  next = shared_ptr<Block>(level->generateBlock());
  addCurrentToBoard();
  blocksPlaced = 0;
}

Board::~Board(){
  clearBoard();
  current.reset();
  next.reset();
  delete level;
}

// Accessors
int Board::getScore() const {return score;}
int Board::getLevel() const {return currentLevel;}
int Board::getHighScore() const {return highScore;}
int Board::getLinesJustCleared() const {return linesJustCleared;}
bool Board::isBlind() const {return blind;}
Block* Board::getNextBlock() const {return next.get();}
Block* Board::getCurrentBlock() const {return current.get();}
vector<vector<shared_ptr<Block>>> Board::getTheBoard() const {return board;}
Board::GameState Board::getGameState() const {return gameState;}

// Mutators
void Board::setScore(int newScore) {score = newScore;}
void Board::setLinesJustCleared(int newCount) {linesJustCleared = newCount;}
void Board::setBlind(bool blindness) {blind = blindness;}
void Board::startTurn() {gameState = GameState::PLAYER_TURN;}

void Board::levelup(){
  if(currentLevel == 4) return;
  currentLevel++;
  forceLevel(currentLevel);
}

void Board::leveldown(){
  if(currentLevel == 0) return;
  currentLevel--;
  forceLevel(currentLevel);
}

void Board::clearBoard(){
  for(vector<shared_ptr<Block>>& row : board){
    for(shared_ptr<Block>& cell : row) cell.reset();
  }
}

void Board::forceLevel(const int newLevel){
  if(newLevel == currentLevel) return; // if same level, don't switch
  delete level; // discard old level
  // get new level
  if(newLevel == 0) level = new Level0(level0File);
  else if(newLevel == 1) level = new Level1;
  else if(newLevel == 2) level = new Level2;
  else if(newLevel == 3) level = new Level3;
  else level = new Level4;
  // generate new blocks
  // completely erase the previous current block
  vector<pair<int, int>> cellsOfBlock = current->getRotation(current->getNumRotations());
  const int curX = current->getX();
  const int curY = current->getY();
  for(auto cell : cellsOfBlock){
    board[cell.second + curY][cell.first + curX].reset();
  }
  current.reset(level->generateBlock()); // generate new current block
  addCurrentToBoard();
  next.reset(level->generateBlock()); // generate new next block
  currentLevel = newLevel;
}

void Board::forceBlock(const string type){
  vector<pair<int, int>> cellsOfBlock = current->getRotation(current->getNumRotations());
  const int weight = current->getHeaviness();
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
  current->changeWeight(weight);
  addCurrentToBoard();
}

void Board :: down () {
  // accessing the properties of the current block
  int curX = current->getX();
  int curY = current->getY();
  int curNumRot = current->getNumRotations();

  bool willDrop = false; // only used if the block is heavy
  const int weight = current->getHeaviness();

  // determining if we are able to move the block down
  for(pair<int, int> cell : current->getRotation(curNumRot)) {
    if(cell.second + curY - 1 < 0) return;
    if(board[cell.second + curY - 1][cell.first + curX] != nullptr && 
       board[cell.second + curY - 1][cell.first + curX] != current) {
      return;
    }
    if(cell.second + curY - weight < 0) {
      willDrop = true;
      continue;
    }
    for(int i = 1; i <= weight; i++){
      if(board[cell.second + curY - i][cell.first + curX] != nullptr &&
         board[cell.second + curY - i][cell.first + curX] != current){
        willDrop = true;
        continue;
      }
    }
  }
  // erasing the block in the board
  for(pair<int, int> cell : current->getRotation(curNumRot)) {
    board[cell.second + curY][cell.first + curX].reset();
  }
  // updating the block's y coordinate
  current->setY(curY - 1);
  curY = curY - 1;
  if(!willDrop && weight > 0) {
    current->setY(curY - weight);
    curY = curY - weight;
  }
  
  // adding it to the board
  addCurrentToBoard();
  if(willDrop) drop();
}

void Board :: right() {
  // accessing the properties of the current block
  int curX = current->getX();
  int curY = current->getY();
  int curNumRot = current->getNumRotations();

  bool willDrop = false; // only used if the block is heavy
  const int weight = current->getHeaviness();

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
    // checking if the cell breaks the border
    if(cell.second + curY - weight < 0) {
      willDrop = true;
      continue;
    }
    for(int i = 1; i <= weight; i++){
      if(board[cell.second + curY - i][cell.first + curX + 1] != nullptr &&
         board[cell.second + curY - i][cell.first + curX + 1] != current){
        willDrop = true;
        continue;
      }
    }
  }
  // erasing the block in the board
  for(pair<int, int> cell : current->getRotation(curNumRot)) {
    board[cell.second + curY][cell.first + curX].reset();
  }
  // updating the block's x coordinate
  current->setX(curX + 1);
  curX = curX + 1;
  // updating the block's y coordinate if it is heavy, and falls without impediment
  if(!willDrop && weight > 0) {
    current->setY(curY - weight);
    curY = curY - weight;
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
  const int weight = current->getHeaviness();

  // determining if we are able to move the block to the right
  for(pair<int, int> cell : current->getRotation(curNumRot)) {
    // checking if the cell surpasses the border
    if(cell.first + curX - 1 < 0) return;
    // checking if the space next to the cell is empty
    if(board[cell.second + curY][cell.first + curX - 1] != nullptr &&
       board[cell.second + curY][cell.first + curX - 1] != current) {
      return;
    }
    // checking if the cell breaks the border
    if(cell.second + curY - weight < 0) {
      willDrop = true;
      continue;
    }
    for(int i = 1; i <= weight; i++){
      if(board[cell.second + curY - i][cell.first + curX - 1] != nullptr &&
         board[cell.second + curY - i][cell.first + curX - 1] != current){
        willDrop = true;
        continue;
      }
    }
  }
  // erasing the block in the board
  for(pair<int, int> cell : current->getRotation(curNumRot)) {
    board[cell.second + curY][cell.first + curX].reset();
  }
  // updating the block's x coordinate
  current->setX(curX - 1);
  curX = curX - 1;
  // updating the block's y coordinate if it is heavy, and falls without impediment
  if(!willDrop && weight > 0) {
    current->setY(curY - weight);
    curY = curY - weight;
  }
  // adding the block to its new position in the board
  addCurrentToBoard();
  // calling drop() if the block drops due to being heavy and impeded
  if(willDrop) drop();
}

void Board::drop() {
  // accessing the properties of the current block
  int curX = current->getX();
  int curY = current->getY();
  int curNumRot = current->getNumRotations();

  while(true) {
    bool canMove = true;
    // checking if block can move down
    for (pair<int, int> cell : current->getRotation(curNumRot)) {
      int newX = curX + cell.first;
      int newY = curY + cell.second - 1;

      if (newY < 0) {
        canMove = false;
        break;
      }

      if (board[newY][newX] != nullptr && board[newY][newX] != current) {
        canMove = false;
        break;
      }
    }
    if (!canMove) {
      break;
    }
    // removing the block in its previous position
    for (pair<int, int> cell : current->getRotation(curNumRot)) {
      board[curY + cell.second][curX + cell.first].reset();
    }
    curY--;
    current->setY(curY);
  }
  // adding the block in its new position on the board
  addCurrentToBoard();
  blocksPlaced++;
  clearRows();
  // checking if blocksPlaced % 5 == 0 (note that this number resets to 0 when a line is cleared)
  if(blocksPlaced%5 == 0 && currentLevel == 4) {
    levelFour();
  } 
  // adding the next block to the board
  current = next;
  addCurrentToBoard();
  if(gameState != GameState::GAME_OVER) gameState = GameState::FINISHED_TURN;
  // generating the next block
  next = shared_ptr<Block>(level->generateBlock());
  if(blind) blind = false;
}

void Board::addCurrentToBoard(){
  const int curX = current->getX();
  const int curY = current->getY();
  vector<pair<int, int>> cellsOfBlock = current->getRotation(current->getNumRotations());
  for(pair<int, int> cell : cellsOfBlock){
    // checking if the game has ended 
    // (note that when this function is called on a dropped block, the space is already verified to be cleared)
    if(board[cell.second + curY][cell.first + curX] != nullptr &&
       board[cell.second + curY][cell.first + curX] != current) {
      gameState = GameState::GAME_OVER;
      return;
    }
    // otherwise, placing the block as intended
    board[cell.second + curY][cell.first + curX] = current;
  }

}

void Board::clearRows() {
  int cleared = 0;
  for(int row = 0; row < boardHeight;){
    bool fullRow = true;
    for(int col = 0; col < boardWidth; ++col){
      if(!board[row][col]){
        fullRow = false;
        break;
      }
    }
    if(fullRow){
      cleared++;
      blocksPlaced = 0; // for Level 4
      for(auto cell : board[row]){
        if(cell.use_count() == 1 && cell->getType() != '*') score += (cell->getLevel() + 1) * (cell->getLevel() + 1);
        cell.reset();
      }
      board.erase(board.begin() + row);
	  board.emplace_back(vector<shared_ptr<Block>>(11, nullptr));
    }
    else{
      row++;
    }
  }
  if(cleared > 0) score += (cleared + currentLevel) * (cleared + currentLevel);
  if(score > highScore) highScore = score;
  linesJustCleared = cleared;
}


void Board::clockwise() {
  int curX = current->getX();
  int curY = current->getY();
  int curNumRot = current->getNumRotations();
  
  int newNumRot = (curNumRot + 1) % 4;
  bool willDrop = false;
  const int weight = current->getHeaviness();

  for(pair<int, int> cell : current->getRotation(newNumRot)) {
    int newX = cell.first + curX;
    int newY = cell.second + curY;

    if (newX < 0 || newX >= boardWidth || newY < 0 || newY >= boardHeight + boardBuffer) {
      return;
    }
    if (board[newY][newX] != nullptr && board[newY][newX] != current) {
      return;
    }

    // checking if the cell breaks the border
    if(newY - weight < 0) {
      willDrop = true;
      continue;
    }
    for(int i = 1; i <= weight; i++){
      if(board[newY - i][newX] != nullptr &&
         board[newY - i][newX] != current){
        willDrop = true;
        continue;
      }
    }
  }

  for(pair<int, int> cell : current->getRotation(curNumRot)) {
    board[curY + cell.second][curX + cell.first].reset();
  }

  // updating the block's y coordinate if it is heavy, and falls without impediment
  if(!willDrop && weight > 0) {
    current->setY(curY - weight);
    curY = curY - weight;
  }

  current->clockwise();

  addCurrentToBoard();
  if(willDrop) drop();
}

void Board::counterclockwise() {
  int curX = current->getX();
  int curY = current->getY();
  int curNumRot = current->getNumRotations();

  int newNumRot = (curNumRot - 1 + 4) % 4;
  bool willDrop = false;
  const int weight = current->getHeaviness();

  for(pair<int, int> cell : current->getRotation(newNumRot)) {
    int newX = cell.first + curX;
    int newY = cell.second + curY;

    if (newX < 0 || newX >= boardWidth || newY < 0 || newY >= boardHeight + boardBuffer) {
      return;
    }
    if (board[newY][newX] != nullptr && board[newY][newX] != current) {
      return;
    }

    // checking if the cell breaks the border
    if(newY - weight < 0) {
      willDrop = true;
      continue;
    }
    for(int i = 1; i <= weight; i++){
      if(board[newY - i][newX] != nullptr &&
         board[newY - i][newX] != current){
        willDrop = true;
        continue;
      }
    }
  }

  for(pair<int, int> cell : current->getRotation(curNumRot)) {
    board[curY + cell.second][curX + cell.first].reset();
  }

  // updating the block's y coordinate if it is heavy, and falls without impediment
  if(!willDrop && weight > 0) {
    current->setY(curY - weight);
    curY = curY - weight;
  }

  current->counterclockwise();

  addCurrentToBoard();
  if(willDrop) drop();
}

void Board :: levelFour() {
  for(int i = 0; i < boardHeight; i++) {
    if(board[i][boardWidth/2] == nullptr) {
      board[i][boardWidth/2] = shared_ptr<Block>(new fourBlock(currentLevel));
      break;
    }
  }
  clearRows();
}

void Board::noRandom(string& file){
  if(currentLevel < 3) return;
  level->setRandomness(false);
  level->setFileName(file);
}

void Board::random(){
  if(currentLevel < 3) return;
  level->setRandomness(true);
}
