#ifndef LBLOCK_H
#define LBLOCK_H

#include "BLOCK_H"


using namespace std;

class LBlock : public Block {
    public: 
        // constructor
        LBlock(int l);

        // getter
        char getType() const override;
};

#endif