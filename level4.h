#ifndef LEVEL4_H
#define LEVEL4_H

#include "level.h"
#include <string>

class Level4 : public Level {
    private:
        int blockCount;
    public:
        Block *generateBlock() override;
}




#endif
