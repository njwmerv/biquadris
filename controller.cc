#include "controller.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>
#include <utility>
#include <algorithm>
#include <queue>
#include "board.h"
using namespace std;

// Big 5
Controller::Controller(int seed, int startingLevel, string scriptFile1, string scriptFile2) :
  seed{seed}, startingLevel{startingLevel}, scriptFile1{scriptFile1}, scriptFile2{scriptFile2} {
  boards.emplace_back(new Board(startingLevel, scriptFile1));
  boards.emplace_back(new Board(startingLevel, scriptFile2));
  for(int i = 0; i < numberOfPlayers; i++) commandsToExecute.emplace_back(queue<Command>());
}

Controller::~Controller(){
  for(Board* board : boards) delete board;
}

// Accessors
const vector<Board*>& Controller::getBoards() const {return boards;}
Board* Controller::getBoard() const {return boards.at(currentPlayer);}
int Controller::getCurrentPlayer() const {return currentPlayer;}

// Display-related
void Controller::notifyObservers() const {
  for(auto view : observers) view->notify();
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

// For the game
void Controller::nextPlayer(){currentPlayer = (currentPlayer + 1) % numberOfPlayers;}

void Controller::sequence(string file){
  ifstream ifs{file};
  string line;
  while(ifs >> line){
    pair<int, Command> interpretation = interpretInput(line);
    for(int i = 0; i < interpretation.first; i++) commandsToExecute.at(currentPlayer).push(interpretation.second);
  }
}
// TODO
void Controller::noRandom(string){

}
// TODO
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
  Command command = Command::INVALID;

  istringstream iss{input};
  if(!(iss >> repetitions)){
    repetitions = 1;
    iss.clear();
  }
  string remainingInput;
  iss >> remainingInput;
  //transform(remainingInput.begin(), remainingInput.end(), remainingInput.begin(), [](unsigned char c) {return tolower(c);});

  // Check if this is a known command
  for(pair<string, Command> stringCommand : commands){
    if(stringCommand.first == remainingInput) command = stringCommand.second;
  }

  // Check if enough of a string was given to distinguish it from other commands
	if(command == Command::INVALID){
  	for(pair<string, Command> stringCommand : commands){
    	if(!(stringCommand.first.starts_with(remainingInput))) continue; // input isn't a prefix of command, so can't be that
    	else if(command == Command::INVALID) command = stringCommand.second; // found it as a prefix for a known command
    	else return {0, Command::INVALID};
  	}
	}

  // don't add these to the queue
  if(command == Command::INVALID || command == Command::BLIND || command == Command::HEAVY || command == Command::FORCE) repetitions = 0;
  // these can't be repeated
  else if(command == Command::RESTART || command == Command::NO_RANDOM || command == Command::RANDOM) repetitions = 1;
	
  return {repetitions, command};
}

void Controller::performCommand(const Command command){
  Board* board = getBoard();
  if(command == Command::LEFT) board->left();
  else if(command == Command::RIGHT) board->right();
  else if(command == Command::DOWN) board->down();
  else if(command == Command::CLOCKWISE) board->clockwise();
  else if(command == Command::COUNTER_CLOCKWISE) board->counterclockwise();
  else if(command == Command::DROP){
    board->drop();
    notifyObservers();
    const int linesJustCleared = board->getLinesJustCleared();
    board->setLinesJustCleared(0);
    nextPlayer();
    board = getBoard();
    if(linesJustCleared <= 1) return;
      // if drop is in sequence or repeated a bunch of times, check that it still goes to next player and doesnt force their input
      // try using try-catch if sequence is a problem
    cout << "You just cleared 2 or more lines! Enter your special action below:" << endl;
    string specialAction;
    Command attackCommand = Command::INVALID;
    while(attackCommand == Command::INVALID){
      cin >> specialAction;
      attackCommand = interpretInput(specialAction).second;
      if(attackCommand == Command::BLIND) getBoard()->setBlind(true);
      else if(attackCommand == Command::HEAVY) getBoard(); // idk what to do here
      else if(attackCommand == Command::FORCE){
        string type;
				while(cin >> type){
					if(type != "I" && type != "J" && type != "L" && type != "O" && type != "S" && type != "Z" && type != "T") cerr << "Invalid block type" << endl;
					else {getBoard()->forceBlock(type); break;}
				}
      }
      else{
				attackCommand = Command::INVALID;
				cerr << "Invalid special action" << endl;
			}
    }
  }
  else if(command == Command::LEVEL_UP) board->levelup();
  else if(command == Command::LEVEL_DOWN) board->leveldown();
  else if(command == Command::NO_RANDOM){
    string filePath;
    cin >> filePath;
    ifstream file{filePath};
  }
  //else if(command == Command::RANDOM) board->random();
  else if(command == Command::SEQUENCE){
    string filePath;
    cin >> filePath;
    sequence(filePath);
  }
  else if(command == Command::I) board->forceBlock("I");
  else if(command == Command::J) board->forceBlock("J");
  else if(command == Command::L) board->forceBlock("L");
  else if(command == Command::O) board->forceBlock("O");
  else if(command == Command::S) board->forceBlock("S");
  else if(command == Command::Z) board->forceBlock("Z");
  else if(command == Command::T) board->forceBlock("T");
  else if(command == Command::RESTART){
    board->clearBoard();
    board->forceLevel(startingLevel);
    board->setScore(0);
  }
  else{
    cerr << "Invalid command" << endl;
  }
}

void Controller::runGame(){
  string input;
  while(true){ // Game loop
    queue<Command>& commandQueue = commandsToExecute.at(currentPlayer);
    cout << "Current Player: " << currentPlayer << endl;
    notifyObservers(); // update graphics
		cout << "Command: " << endl;
		while(commandQueue.empty()){
  	  cin >> input;
			pair<int, Command> interpretation = interpretInput(input);
            if(interpretation.first == 0) cerr << "Invalid input" << endl;
      for(int i = 0; i < interpretation.first; i++) commandQueue.push(interpretation.second);
		}
    performCommand(commandQueue.front());
    commandQueue.pop();
  }
}
