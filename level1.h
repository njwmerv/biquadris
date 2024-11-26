#ifndef LEVEL1_H
#define LEVEL1_H

#include "level.h"
#include <string>

class Level1 : public Level {
    public:
        Block *generateBlock() override;
};

#endif
