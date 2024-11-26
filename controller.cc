#include "controller.h"
#include <sstream>
#include <memory>
#include <utility>
#include <fstream>
#include "board.h"
using namespace std;

// Big 5
Controller::Controller(int seed, int startingLevel, string scriptFile1, string scriptFile2) :
  seed{seed}, startingLevel{startingLevel}, scriptFile1{scriptFile1}, scriptFile2{scriptFile2} {
  boards.emplace_back(new Board(startingLevel, scriptFile1));
  boards.emplace_back(new Board(startingLevel, scriptFile2));
}

Controller::~Controller(){
  for(auto board : boards) delete board;
}

// Accessors
const vector<Board*>& Controller::getBoards() const {return boards;}

Board* Controller::getBoard() const {return boards.at(currentPlayer);}

int Controller::getCurrentPlayer() const {return currentPlayer;}

// Mutators
void Controller::nextPlayer(){currentPlayer = (currentPlayer + 1) % numberOfPlayers; in = cin;}

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
void Controller::sequence(string file){
  ifstream ifs{file};
  string line;
  while(ifs >> line){
    auto interpreted = interpretInput(line);
    performCommand(interpreted.first, interpreted.second);
  }
}

void Controller::noRandom(string){

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
pair<int, Controller::Command> Controller::interpretInput(const string input) const {
  int repetitions = 1;

  istringstream iss{input};
  if(!(iss >> repetitions)){
    repetitions = 1;
    iss.clear();
  }
  string remainingInput;
  iss >> remainingInput;

  // Check if this is a known command
  for(auto stringCommand : commands){
    if(stringCommand.first == remainingInput) return {repetitions, stringCommand.second};
  }

  // Check if enough of a string was given to distinguish it from other commands
  Command match = Command::INVALID;
  for(auto stringCommand : commands){
    if(!(stringCommand.first.starts_with(remainingInput))) continue; // input isn't a prefix of command, so can't be that
    else if(match == Command::INVALID) match = stringCommand.second; // found it as a prefix for a known command
    else return {0, Command::INVALID}; // found it as a prefix for another command, so input is ambiguous
  }

  return {match == Command::INVALID ? 0 : repetitions, match};
}

void Controller::performCommand(const int repetitions, const Command command){
  Board* board = getBoard();
  for(int i = 0; i < repetitions; i++){
    if(command == Command::LEFT) board->left();
    else if(command == Command::RIGHT) board->right();
    else if(command == Command::DOWN) board->down();
    else if(command == Command::CLOCKWISE) board->clockwise();
    else if(command == Command::COUNTER_CLOCKWISE) board->counterclockwise();
    else if(command == Command::DROP) board->drop();
    else if(command == Command::LEVEL_UP) board->levelup();
    else if(command == Command::LEVEL_DOWN) board->leveldown();
    else if(command == Command::NO_RANDOM){
      string filePath;
      in >> filePath;
      ifstream file{filePath};
    }
    else if(command == Command::RANDOM) board->random();
    else if(command == Command::SEQUENCE){
      string filePath;
      in >> filePath;
      sequence(filePath);
    }
    else if(command == Command::I) board;
    else if(command == Command::J) board;
    else if(command == Command::L) board;
    else if(command == Command::O) board;
    else if(command == Command::S) board;
    else if(command == Command::Z) board;
    else if(command == Command::T) board;
    else if(command == Controller::Command::RESTART){
      board->clearBoard();
      board->forceLevel(startingLevel);
      board->setScore(0);
    }
  }
}

void Controller::runGame(){
  string input;
  bool turnDone = false;
  while(true){ // Game loop
    notifyObservers(); // update graphics

    // Read input and get it interpreted by controller
    in >> input;
    auto interpretedInput = interpretInput(input);
    performCommand(interpretedInput.first, interpretedInput.second);

    if(turnDone){notifyObservers(); nextPlayer();} // TODO MARI: when is turnDone?
  }
}
