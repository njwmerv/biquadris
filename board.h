#ifndef BOARD_H
#define BOARD_H
#include "block.h"
#include "level.h"
#include <vector>
#include <memory>
using namespace std;

class Board{
  vector<vector<shared_ptr<Block>>> board;
  Level* level;
  int score;
  int highScore;
  shared_ptr<Block> current;
  Block* next;
  string level0File;
  int currentLevel;
  bool blind;

  void clearRows();

  void addCurrentToBoard();

  public:
    // Big 5
    Board(int, string);

    ~Board();

    // Accessors
    int getScore() const;

    int getLevel() const;

    vector<vector<shared_ptr<Block>>> getTheBoard() const;

    Block* getNextBlock() const;

    Block* getCurrentBlock() const;

    bool isBlind() const;

    // Mutators
    void setScore(int);

    // Game state
    void levelup();
    void leveldown();
    void clearBoard();
    void forceBlock(const string);
    void forceLevel(const int);

    void left();
    void right();
    void down();
    void drop();
    void clockwise();
    void counterclockwise();
};

#endif
