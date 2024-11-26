#ifndef TBLOCK_H
#define TBLOCK_H

#include "BLOCK_H"


using namespace std;

class TBlock : public Block {
    public: 
        // constructor
        TBlock(int l);

        // getter
        char getType() const override;

};

#endif