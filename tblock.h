#ifndef TBLOCK_H
#definetBLOCK_H

#include "block.h"


using namespace std;

class TBlock : public Block {
    public: 
        // constructor
        TBlock(int l);

        // destructor
        ~TBlock() override;

        // getter
        char getType() const override;

        // rotate the block clockwise
        void clockwise () override;

        // rotate the block counterclockwise
        void counterclockwise () override;

};

#endif