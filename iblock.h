#ifndef IBLOCK_H
#define IBLOCK_H

#include "block.h"


using namespace std;

class IBlock : public Block {
    public: 
        // creator
        IBlock();

        // destructor
        ~IBlock() override;

        // getter
        char getType() const override;

        // rotate the block clockwise
        void clockwise () override;

        // rotate the block counterclockwise
        void counterclockwise () override;

}

#endif