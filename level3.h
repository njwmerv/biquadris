#ifndef LEVEL3_H
#define LEVEL3_H
#include "level.h"
#include <fstream>
#include <string>

class Level3 : public Level {
  public:
    Level3(const string& path = "");
    ~Level3(){}
    Block *generateBlock() override;
};

#endif
