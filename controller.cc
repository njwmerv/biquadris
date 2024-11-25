#include "controller.h"
#include <sstream>
#include <utility>
#include <fstream>
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
void Controller::nextPlayer(){currentPlayer = (currentPlayer + 1) % numberOfPlayers; in = std::cin;}

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
std::pair<int, Controller::Command> Controller::interpretInput(const std::string input) const {
  int repetitions = 1;

  std::istringstream iss{input};
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
  const Board* board = getBoard();
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
      std::string filePath;
      in.get() >> filePath;
      std::ifstream file{filePath};
    }
    else if(command == Command::RANDOM) board->random();
    else if(command == Command::SEQUENCE){
      std::string filePath;
      in.get() >> filePath;
      std::ifstream file{filePath};
      in = file; // may cause seg fault when this goes out of scope
    }
    else if(command == Command::I) board;
    else if(command == Command::J) board;
    else if(command == Command::L) board;
    else if(command == Command::O) board;
    else if(command == Command::S) board;
    else if(command == Command::Z) board;
    else if(command == Command::T) board;
    else if(command == Controller::Command::RESTART) board->restart();
  }
}

void Controller::runGame(){
  std::string input;
  bool turnDone = false;
  while(true){ // Game loop
    notifyObservers(); // update graphics

    // Read input and get it interpreted by controller
    if(in.get().eof() && &(in.get()) == &std::cin) break;
    else if(in.get().eof()) in = std::cin;

    in.get() >> input;
    auto interpretedInput = interpretInput(input);
    performCommand(interpretedInput.first, interpretedInput.second);

    if(turnDone) nextPlayer(); // TODO MARI: when is turnDone?
  }
}
