#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <map>
#include <utility>
#include <functional>
#include "view.h"
#include "board.h"
using namespace std;

class Controller{
  const int seed;
  const int startingLevel;
  const string scriptFile1;
  const string scriptFile2;
  const int numberOfPlayers = 2;
  istream& in = cin;
  vector<Board*> boards;
  vector<View*> observers;
  int currentPlayer = 0;

  enum class Command{
    LEFT, RIGHT, DOWN, CLOCKWISE, COUNTER_CLOCKWISE, DROP, // block movement
    LEVEL_UP, LEVEL_DOWN, NO_RANDOM, RANDOM, SEQUENCE, // specify block generation
    I, J, L, O, S, Z, T, // specify next block
    RESTART, INVALID, // other
    BLIND, HEAVY, FORCE // special actions
  };

  map<string, Command> commands{
    {"left", Command::LEFT}, {"right", Command::RIGHT}, {"down", Command::DOWN}, {"clockwise", Command::CLOCKWISE},
    {"counter_clockwise", Command::COUNTER_CLOCKWISE}, {"drop", Command::DROP}, {"random", Command::RANDOM},
    {"sequence", Command::SEQUENCE}, {"I", Command::I}, {"J", Command::J}, {"L", Command::L}, {"O", Command::O},
    {"S", Command::S}, {"Z", Command::Z}, {"T", Command::T}, {"restart", Command::RESTART},
    {"levelup", Command::LEVEL_UP}, {"leveldown", Command::LEVEL_DOWN},
    {"blind", Command::BLIND}, {"heavy", Command::HEAVY}, {"force", Command::FORCE}
  };

  public:
    // Big 5
    Controller(int, int, string, string);

    ~Controller();

    // Accessors
    const vector<Board*>& getBoards() const;

    Board* getBoard() const;

    int getCurrentPlayer() const;

    // Mutators
    void nextPlayer();

    // Display-related
    void notifyObservers() const;

    void attachView(View*);

    void detachView(View*);

    // For the game TODO
    void sequence(string);

    void noRandom(string);

    void random();

    void resetGame();

    // I/O-related

    pair<int, Controller::Command> interpretInput(const string) const;

    void performCommand(const int, const Command);

    void runGame();
};

#endif //CONTROLLER_H
