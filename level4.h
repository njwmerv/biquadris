#ifndef LEVEL4_H
#define LEVEL4_H
#include "level.h"
#include <fstream>

class Level4 : public Level {
  public:
    Block *generateBlock() override;
};

#endif
