#ifndef JBLOCK_H
#define JBLOCK_H

#include "block.h"


using namespace std;

class JBlock : public Block {
    public: 
        // constructor
        JBlock(int l);

        // destructor
        ~JBlock() override;

        // getter
        char getType() const override;

        // rotate the block clockwise
        void clockwise () override;

        // rotate the block counterclockwise
        void counterclockwise () override;

};

#endif