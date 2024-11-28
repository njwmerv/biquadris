#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <memory>
#include "view.h"
#include "board.h"
using namespace std;

class Controller{
  enum class Command{
    LEFT, RIGHT, DOWN, CLOCKWISE, COUNTER_CLOCKWISE, DROP, // block movement
    LEVEL_UP, LEVEL_DOWN, NO_RANDOM, RANDOM, SEQUENCE, // specify block generation
    I, J, L, O, S, Z, T, // specify next block
    RESTART, INVALID, // other
    BLIND, HEAVY, FORCE, // special actions
    FORCE_LEVEL, ADD, REMOVE, QUIT, RESTART_ALL // bonus
  };

  const int startingLevel;
  const string scriptFile1;
  const string scriptFile2;
  const int numberOfPlayers = 2;
  int currentPlayer = 0;
  vector<unique_ptr<Board>> boards;
  vector<View*> observers;
  vector<queue<Command>> commandsToExecute; // queue that stores commands to run for each player, even if turn ends
  const map<string, Command> defaultCommands{ // these are the commands a user can run at the start
    {"left", Command::LEFT}, {"right", Command::RIGHT}, {"down", Command::DOWN}, {"clockwise", Command::CLOCKWISE},
    {"counter_clockwise", Command::COUNTER_CLOCKWISE}, {"drop", Command::DROP}, {"random", Command::RANDOM},
    {"norandom", Command::NO_RANDOM}, {"sequence", Command::SEQUENCE}, {"I", Command::I}, {"J", Command::J},
    {"L", Command::L}, {"O", Command::O}, {"S", Command::S}, {"Z", Command::Z}, {"T", Command::T},
    {"restart", Command::RESTART}, {"levelup", Command::LEVEL_UP}, {"leveldown", Command::LEVEL_DOWN},
    {"blind", Command::BLIND}, {"heavy", Command::HEAVY}, {"force", Command::FORCE},
    {"forcelevel", Command::FORCE_LEVEL}, {"add", Command::ADD}, {"remove", Command::REMOVE}, {"quit", Command::QUIT}, {"restartall", Command::RESTART_ALL},
  };
  map<string, Command> commands = defaultCommands;

  // For the game
  void nextPlayer();
  void sequence(string);
  void resetGame();

  // I/O-related
  void performCommand(const Command);
  pair<int, Controller::Command> interpretInput(const string) const;
  void endTurn();
  void addCommandAlias(Command, string&);
  void removeCommandAlias(string&);
  void notifyObservers() const;

  public:
    // Big 5
    Controller(int, string, string);
    ~Controller();

    // Accessors
    const vector<unique_ptr<Board>>& getBoards() const;
    unique_ptr<Board>& getBoard();
    int getCurrentPlayer() const;

    // Display-related
    void attachView(View*);
    void detachView(View*);

    // I/O-related
    void runGame();
};

#endif //CONTROLLER_H
