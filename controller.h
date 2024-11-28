#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <vector>
#include <string>
#include <map>
#include <queue>
#include "view.h"
#include "board.h"
//#include <iostream>
//#include <memory>
//#include <utility>
//#include <functional>
using namespace std;

class Controller{
  enum class Command{
    LEFT, RIGHT, DOWN, CLOCKWISE, COUNTER_CLOCKWISE, DROP, // block movement
    LEVEL_UP, LEVEL_DOWN, NO_RANDOM, RANDOM, SEQUENCE, // specify block generation
    I, J, L, O, S, Z, T, // specify next block
    RESTART, INVALID, // other
    BLIND, HEAVY, FORCE // special actions
  };

	const int seed;
	const int startingLevel;
	const string scriptFile1;
	const string scriptFile2;
	const int numberOfPlayers = 2;
	int currentPlayer = 0;
	vector<Board*> boards;
	vector<View*> observers;
	vector<queue<Command>> commandsToExecute;

  map<string, Command> commands{
    {"left", Command::LEFT}, {"right", Command::RIGHT}, {"down", Command::DOWN}, {"clockwise", Command::CLOCKWISE},
    {"counter_clockwise", Command::COUNTER_CLOCKWISE}, {"drop", Command::DROP}, {"random", Command::RANDOM},
    {"sequence", Command::SEQUENCE}, {"I", Command::I}, {"J", Command::J}, {"L", Command::L}, {"O", Command::O},
    {"S", Command::S}, {"Z", Command::Z}, {"T", Command::T}, {"restart", Command::RESTART},
    {"levelup", Command::LEVEL_UP}, {"leveldown", Command::LEVEL_DOWN},
    {"blind", Command::BLIND}, {"heavy", Command::HEAVY}, {"force", Command::FORCE}
  };

  // For the game
  void nextPlayer();

  // I/O-related
  void performCommand(const Command);
  pair<int, Controller::Command> interpretInput(const string) const;
  void endTurn();

  public:
    // Big 5
    Controller(int, int, string, string);
    ~Controller();

    // Accessors
    const vector<Board*>& getBoards() const;
    Board* getBoard() const;
    int getCurrentPlayer() const;

    // Display-related
    void notifyObservers() const;
    void attachView(View*);
    void detachView(View*);

    // For the game
    void sequence(string);
    void noRandom(string); // TODO
    void random(); // TODO
    void resetGame();

    // I/O-related
    void runGame();
};

#endif //CONTROLLER_H
