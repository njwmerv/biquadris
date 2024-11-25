#ifndef LEVEL2_H
#define LEVEL2_H
#include "level.h"

class Level2 : public Level{
    public:
        Block *generateBlock() override;
}

#endif

