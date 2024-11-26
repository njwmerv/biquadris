#ifndef LEVEL_H
#define LEVEL_H

#include "BLOCK_H"

class Level {
    public:
        int currentLevel = 0;
        virtual Block *generateBlock() = 0;
        virtual ~Level() {};
};

#endif