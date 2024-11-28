#ifndef LEVEL3_H
#define LEVEL3_H
#include "level.h"
#include <fstream>
#include <string>

class Level3 : public Level {
  ifstream file;
  string filename;
  bool isRandom = false;

  public:
    Level3();
    Level3(const string& file);

    Block *generateBlock() override;

    void setRandomness(bool);
};

#endif
