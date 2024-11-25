#include "controller.h"
#include <sstream>
#include "board.h"

// Big 5
Controller::Controller(int seed, int startingLevel, std::string scriptFile1, std::string scriptFile2) :
  seed{seed}, startingLevel{startingLevel}, scriptFile1{scriptFile1}, scriptFile2{scriptFile2} {
  for(int i = 0; i < numberOfPlayers; i++){
    // TODO MARI: Create boards
  }
}

// Accessors
const std::vector<Board*>& Controller::getBoards() const {return boards;}

const Board* Controller::getBoard() const {return boards.at(currentPlayer);}

int Controller::getCurrentPlayer() const {return currentPlayer;}

// Mutators
void Controller::nextPlayer(){currentPlayer = (currentPlayer + 1) % numberOfPlayers;}

// Display-related
void Controller::notifyObservers() const {
  for(View* view : observers){
     view->notify();
  }
}

void Controller::attachView(View* viewer){
  for(View* view : observers){ // make sure you do not add an already attached observer
    if(view == viewer) return;
  }
  observers.emplace_back(viewer);
}

void Controller::detachView(View* viewer){
  for(auto it = observers.begin(); it != observers.end();){
    if(*it == viewer) it = observers.erase(it);
    else it++;
  }
}

// For the game TODO: MARI
void Controller::sequence(std::string){

}

void Controller::noRandom(std::string){

}

void Controller::random(){

}

void Controller::resetGame(){
  for(Board* board : boards){
    board->clearBoard();
    board->forceLevel(startingLevel);
    board->setScore(0);
  }
  currentPlayer = 0;
}

// I/O-related
Controller::Command Controller::interpretInput(const std::string input) const {
  // Check if this is a known command
  for(auto stringCommand : commands){
    if(stringCommand.first == input) return stringCommand.second;
  }

  // Check if enough of a string was given to distinguish it from other commands
  Command match = Command::INVALID;
  for(auto stringCommand : commands){
    if(!(stringCommand.first.startsWith(input))) continue; // input isn't a prefix of command, so can't be that
    else if(match == Command::INVALID) match = stringCommand.second; // found it as a prefix for a known command
    else return Command::INVALID; // found it as a prefix for another command, so input is ambiguous
  }

  return match;
}
