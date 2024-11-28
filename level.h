#ifndef LEVEL_H
#define LEVEL_H

#include "block.h"

class Level {
    public:
        int currentLevel = 0;
        virtual Block *generateBlock() = 0;
        virtual void setRandomness(bool);
        virutal void setFileName(const string&);
};

#endif