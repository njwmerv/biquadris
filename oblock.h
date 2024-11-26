#ifndef TBLOCK_H
#definetBLOCK_H

#include "block.h"


using namespace std;

class OBlock : public Block {
    public: 
        // constructor
        OBlock(int l);

        // getter
        char getType() const override;

        // rotate the block clockwise
        void clockwise () override;

        // rotate the block counterclockwise
        void counterclockwise () override;

};

#endif