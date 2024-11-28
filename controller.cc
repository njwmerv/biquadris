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
Controller::Controller(int startingLevel, string scriptFile1, string scriptFile2) :
  startingLevel{startingLevel}, scriptFile1{scriptFile1}, scriptFile2{scriptFile2} {
  boards.emplace_back(make_unique<Board>(startingLevel, scriptFile1, Board::GameState::PLAYER_TURN));
  boards.emplace_back(make_unique<Board>(startingLevel, scriptFile2, Board::GameState::FINISHED_TURN));
  for(int i = 0; i < numberOfPlayers; i++) commandsToExecute.emplace_back(queue<Command>());
}

Controller::~Controller(){}

// Accessors
const vector<unique_ptr<Board>>& Controller::getBoards() const {return boards;}
unique_ptr<Board>& Controller::getBoard() {return boards.at(currentPlayer);}
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
    if(*it == viewer) it = observers.erase(it); // in case there are multiple occurrences
    else it++;                                  // of an observer in the vector
  }
}

// For the game
void Controller::nextPlayer(){currentPlayer = (currentPlayer + 1) % numberOfPlayers;}

void Controller::sequence(string file){
  ifstream ifs{file};
  string line;
  while(ifs >> line){ // read command from file
    pair<int, Command> interpretation = interpretInput(line);
    for(int i = 0; i < interpretation.first; i++) commandsToExecute.at(currentPlayer).push(interpretation.second);
    // add command to queue
  }
}

void Controller::resetGame(){ // clear board and reset current + next blocks for each player
  for(unique_ptr<Board>& board : boards){
    board->restart(startingLevel);
  }
  currentPlayer = 0; // go back to first player
}

// I/O-related
pair<int, Controller::Command> Controller::interpretInput(const string input) const {
  int repetitions = 1;
  Command command = Command::INVALID;

  istringstream iss{input}; // try to read an int at the start of the input
  if(!(iss >> repetitions)){ // if no int, just assume repetitions is 1
    repetitions = 1;
    iss.clear();
  }
  string remainingInput; // get the actual input
  iss >> remainingInput;
  transform(remainingInput.begin(), remainingInput.end(), remainingInput.begin(), [](unsigned char c) {return tolower(c);});

  // Check if this is a known command
  for(pair<string, Command> stringCommand : commands){
    if(stringCommand.first == remainingInput) command = stringCommand.second;
  }

  // Check if enough of a string was given to distinguish it from other commands
	if(command == Command::INVALID){ // if didn't find command yet
  	  for(pair<string, Command> stringCommand : commands){ // search hashmap for autocomplete candidates
    	if(!(stringCommand.first.starts_with(remainingInput))) continue; // input isn't a prefix of command, so can't be that
    	else if(command == Command::INVALID) command = stringCommand.second; // found it as a prefix for a known command
    	else return {0, Command::INVALID};
  	  }
	}

  // don't add these to the queue
  if(command == Command::INVALID ||
     command == Command::BLIND ||
     command == Command::HEAVY ||
     command == Command::FORCE) repetitions = 0;
  // these can't be repeated
  else if(command == Command::RESTART ||
          command == Command::NO_RANDOM ||
          command == Command::RANDOM ||
          command == Command::ADD ||
          command == Command::REMOVE ||
          command == Command::RESTART_ALL ||
          command == Command::QUIT) repetitions = 1;
	
  return {repetitions, command};
}

void Controller::endTurn(){
  unique_ptr<Board>& board = getBoard(); // get board whose turn just ended
  notifyObservers(); // update display for it (only Graphic displays should run here)
  const int linesJustCleared = board->getLinesJustCleared(); // get how many lines cleared
  nextPlayer(); // switch to next player's board
  unique_ptr<Board>& newBoard = getBoard();
  newBoard->startTurn(); // reset this player's state to as if they just started their turn
  if(linesJustCleared <= 1) return; // if prev player cleared 2+ lines, they do special action
  cout << "You just cleared " << linesJustCleared << " lines! Enter your special action below:" << endl;
  string specialAction; // prompt user for what they want to do for special action
  Command attackCommand = Command::INVALID;
  while(attackCommand == Command::INVALID){ // while input is wrong, keep asking
    cin >> specialAction;
    attackCommand = interpretInput(specialAction).second; // only care about the command, no repetitions
    if(attackCommand == Command::BLIND) newBoard->setBlind(true); // make them blind
    else if(attackCommand == Command::HEAVY) newBoard->getCurrentBlock()->changeWeight(2); // make current block heavier
    else if(attackCommand == Command::FORCE){
      string type; // ask for what type of block
	  while(cin >> type){ // while type is wrong, keep asking
      	if(type != "I" && type != "J" && type != "L" && type != "O" && type != "S" && type != "Z" && type != "T") cerr << "Invalid block type" << endl;
		else {newBoard->forceBlock(type); break;}
	  }
    }
    else{ // tell user their input was wrong
	  attackCommand = Command::INVALID;
	  cerr << "Invalid special action" << endl;
	}
  }
}

void Controller::performCommand(const Command command){
  unique_ptr<Board>& board = getBoard(); // get board to run commands on
  // movement related
  if(command == Command::LEFT) board->left();
  else if(command == Command::RIGHT) board->right();
  else if(command == Command::DOWN) board->down();
  else if(command == Command::CLOCKWISE) board->clockwise();
  else if(command == Command::COUNTER_CLOCKWISE) board->counterclockwise();
  else if(command == Command::DROP) board->drop();
  // levels related
  else if(command == Command::LEVEL_UP) board->levelup();
  else if(command == Command::LEVEL_DOWN) board->leveldown();
  else if(command == Command::FORCE_LEVEL){
    int newLevel = -1;
    while(newLevel == -1){
      cin >> newLevel;
      if(newLevel != 0 && newLevel != 1 && newLevel != 2 && newLevel != 3 && newLevel != 4) newLevel = -1;
      else board->forceLevel(newLevel);
    }
  }
  // block generation related
  else if(command == Command::NO_RANDOM && board->getLevel() >= 3){
    string filePath;
    cin >> filePath;
    ifstream file{filePath};
    board->noRandom(filePath);
  }
  else if(command == Command::RANDOM && board->getLevel() >= 3) board->random();
  else if(command == Command::SEQUENCE){
    string filePath;
    cin >> filePath;
    sequence(filePath);
  }
  // force a block
  else if(command == Command::I) board->forceBlock("I");
  else if(command == Command::J) board->forceBlock("J");
  else if(command == Command::L) board->forceBlock("L");
  else if(command == Command::O) board->forceBlock("O");
  else if(command == Command::S) board->forceBlock("S");
  else if(command == Command::Z) board->forceBlock("Z");
  else if(command == Command::T) board->forceBlock("T");
  // other commands
  else if(command == Command::RESTART){
    cout << "Restarting game for Player " << currentPlayer << "..." << endl;
    board->restart(startingLevel);
  }
  else if(command == Command::ADD){
    string command;
    string alias;
    Controller::Command interpretedCommand = Command::INVALID;
    while(interpretedCommand == Command::INVALID){
      cin >> command;
      interpretedCommand = interpretInput(command).second;
    }
    cin >> alias;
    addCommandAlias(interpretedCommand, alias);
  }
  else if(command == Command::REMOVE){
    string alias;
    cin >> alias;
    removeCommandAlias(alias);
  }
  else if(command == Command::RESTART_ALL) resetGame();
  else{
    cerr << "Invalid command" << endl; // tell user their input is received and wrong
  }
}

void Controller::runGame(){
  string input;
  while(true){ // Game loop
    queue<Command>& commandQueue = commandsToExecute.at(currentPlayer);
    cout << "Current Player: " << currentPlayer << endl;
    notifyObservers(); // update graphics
    cout << "Command: " << endl; // prompt user for input
	while(commandQueue.empty()){ // only ask for input if queue of commands is empty and nothing to do
  	  cin >> input;
	  pair<int, Command> interpretation = interpretInput(input);
      if(interpretation.first == 0) cerr << "Invalid input" << endl;
      for(int i = 0; i < interpretation.first; i++) commandQueue.push(interpretation.second); // add command to queue
	}
    if(commandQueue.front() == Command::QUIT) break; // if user wants to quit, end game loop
    performCommand(commandQueue.front()); // get command and run it
    commandQueue.pop(); // get rid of command
    const Board::GameState boardState = getBoard()->getGameState(); // get game state
    if(boardState == Board::GameState::GAME_OVER){ // if player lost
      cout << "Game over for Player " << (currentPlayer + 1) << endl; // tell them
      cout << "Would you like to restart? [y/n]" << endl; // ask if they want to keep playing
      string answer;
      while(answer != "y" && answer != "n" && answer != "Y" && answer != "N") cin >> answer;
      if(answer == "y" || answer == "Y"){ // want to keep playing
        performCommand(Command::RESTART);
        endTurn();
      }
      else break; // end game
    }
    else if(boardState == Board::GameState::FINISHED_TURN) endTurn(); // if player ended their turn, switch
  }
}

void Controller::addCommandAlias(Command command, string& alias){
  if(command == Command::INVALID) return; // not a valid command to make an alias for
  transform(alias.begin(), alias.end(), alias.begin(), [](unsigned char c) {return tolower(c);}); // case-insensitive
  if(commands.count(alias) == 1) return; // already in the map of commands
  commands[alias] = command; // add it
}

void Controller::removeCommandAlias(string& alias){
  transform(alias.begin(), alias.end(), alias.begin(), [](unsigned char c) {return tolower(c);}); // case-insensitive
  if(commands.count(alias) == 0) return; // check that this is even removable
  int counter = 0; // check that it's not the last instance of this command
  for(auto it = commands.begin(); it != commands.end(); it++){
    if(it->second == commands.at(alias)) counter++;
  }
  if(counter > 1) commands.erase(alias); // remove it
}
