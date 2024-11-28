#ifndef LEVEL0_H
#define LEVEL0_H
#include "level.h"
#include <string>
using namespace std;


class Level0 : public Level {
    string currentBlock;
    public:
        Block* generateBlock() override;
    
};

#endif
