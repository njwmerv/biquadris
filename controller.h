#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <utility>
#include <functional>
#include "board.h"

class View; // forward declaration

class Controller{
  const int seed;
  const int startingLevel;
  const std::string scriptFile1;
  const std::string scriptFile2;
  const int numberOfPlayers = 2;
  std::reference_wrapper<std::istream> in = std::cin;
  std::vector<Board*> boards;
  std::vector<View*> observers;
  int currentPlayer = 0;

  std::map<std::string, Command> commands{
    {"left", Command::LEFT}, {"right", Command::RIGHT}, {"down", Command::DOWN}, {"clockwise", Command::CLOCKWISE},
    {"counter_clockwise", Command::COUNTER_CLOCKWISE}, {"drop", Command::DROP}, {"random", Command::RANDOM},
    {"sequence", Command::SEQUENCE}, {"I", Command::I}, {"J", Command::J}, {"L", Command::L}, {"O", Command::O},
    {"S", Command::S}, {"Z", Command::Z}, {"T", Command::T}, {"restart", Command::RESTART},
    {"blind", Command::BLIND}, {"heavy", Command::HEAVY}, {"force", Command::FORCE}
  };

  public:
    // Big 5
    Controller(int, int, std::string, std::string);

    // Accessors
    const std::vector<Board*>& getBoards() const;

    const Board* getBoard() const;

    int getCurrentPlayer() const;

    // Mutators
    void nextPlayer();

    // Display-related
    void notifyObservers() const;

    void attachView(View*);

    void detachView(View*);

    // For the game
    void sequence(std::string);

    void noRandom(std::string);

    void random();

    void resetGame();

    void nextPlayer();

    // I/O-related
    enum class Command{
      LEFT, RIGHT, DOWN, CLOCKWISE, COUNTER_CLOCKWISE, DROP, // block movement
      LEVEL_UP, LEVEL_DOWN, NO_RANDOM, RANDOM, SEQUENCE, // specify block generation
      I, J, L, O, S, Z, T, // specify next block
      RESTART, INVALID, // other
      BLIND, HEAVY, FORCE // special actions
    };

    std::pair<int, Controller::Command> interpretInput(const std::string) const;

    void performCommand(const int, const Command);

    void runGame();
};

#endif //CONTROLLER_H
