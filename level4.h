#ifndef LEVEL4_H
#define LEVEL4_H
#include "level.h"
#include <fstream>
#include <string>

class Level4 : public Level {
  ifstream file;
  string filename;
  bool isRandom = false;

public:
  Level4();
  Level4(const string& file);

  Block *generateBlock() override;

  void setRandomness(bool);
};

#endif
