#ifndef OBLOCK_H
#define OBLOCK_H

#include "block.h"


using namespace std;

class OBlock : public Block {
    public: 
        // constructor
        OBlock(int l);

        // getter
        char getType() const override;

};

#endif

