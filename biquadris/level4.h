#ifndef LEVEL4_H
#define LEVEL4_H
#include "level.h"
#include <fstream>

class Level4 : public Level {
  public:
    // Constructor
    Level4(const string& path = "");
    // Destructor
    ~Level4(){}
    Block *generateBlock() override;
};

#endif
