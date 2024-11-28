#ifndef LEVEL3_H
#define LEVEL3_H
#include "level.h"
#include <fstream>
#include <string>

class Level3 : public Level {
  public:
    // Constructor
    Level3(const string& path = "");
    // Destructor
    ~Level3(){}
    Block *generateBlock() override;
};

#endif
