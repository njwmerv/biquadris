#ifndef SBLOCK_H
#define SBLOCK_H

#include "block.h"


using namespace std;

class SBlock : public Block {
    public: 
        // constructor
        SBlock(int l);


        // getter
        char getType() const override;

};

#endif

