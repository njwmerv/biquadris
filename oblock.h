#ifndef OBLOCK_H
#define OBLOCK_H

#include "BLOCK_H"


using namespace std;

class OBlock : public Block {
    public: 
        // constructor
        OBlock(int l);

        // getter
        char getType() const override;

};

#endif