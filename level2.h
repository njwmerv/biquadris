#ifndef LEVEL2_H
#define LEVEL2_H
#include "level.h"

class Level2 : public Level{
    public:
        // Constructor
        Level2(const string& path = "");
        // Destructor
        ~Level2(){}
        Block *generateBlock() override;
};

#endif

