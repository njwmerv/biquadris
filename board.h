#ifndef BOARD_H
#define BOARD_H
#include "block.h"
#include "level.h"
#include <vector>
#include <memory>
using namespace std;

class Board{
  public: 
    enum class GameState{GAME_OVER, PLAYER_TURN, FINISHED_TURN};
  private:
    vector<vector<shared_ptr<Block>>> board;
    unique_ptr<Level> level;
    int score;
    int highScore;
    shared_ptr<Block> current;
    shared_ptr<Block> next;
    string level0File;
    int currentLevel;
    bool blind;
    int linesJustCleared;
    int blocksPlaced;
    GameState gameState;

    // methods for managing board
    void clearBoard();
    void clearRows();
    void addCurrentToBoard();
    void levelFour();

  public:
    // Big 5
    Board(int, string, GameState);

    ~Board();

    // Accessors
    int getScore() const;
    int getLevel() const;
    int getHighScore() const;
    int getLinesJustCleared() const;
    bool isBlind() const;
    Block* getNextBlock() const;
    Block* getCurrentBlock() const;
    vector<vector<shared_ptr<Block>>> getTheBoard() const;
    GameState getGameState() const;

    // Mutators
    void setBlind(bool);
    void startTurn();

    // Game state
    void levelup();
    void leveldown();
    void restart(int);
    void forceBlock(const string);
    void forceLevel(const int);
    void noRandom(string&);
    void random();

    // movement
    void left();
    void right();
    void down();
    void drop();
    void clockwise();
    void counterclockwise();
};

#endif
