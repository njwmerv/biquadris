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
  Block* current;
  Block* next;
  string level0File;
  int currentLevel;

  public:
    // Big 5
    Board(int, string);

    ~Board();

    // Accessors
    int getScore() const;

    int getLevel() const;

    // Mutators
    void setScore(int);

    // Game state
    void levelup();
    void leveldown();
    void clearBoard();
    Block* forceBlock(const char);
    Level* forceLevel(const int);

    void down();
    void right();
    void left();
};

#endif
