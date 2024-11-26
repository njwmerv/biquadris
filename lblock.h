#ifndef LBLOCK_H
#define LBLOCK_H

#include "block.h"


using namespace std;

class LBlock : public Block {
    public: 
        // constructor
        LBlock(int l);

        // getter
        char getType() const override;

        // rotate the block clockwise
        void clockwise () override;

        // rotate the block counterclockwise
        void counterclockwise () override;

};

#endif