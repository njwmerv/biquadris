#ifndef IBLOCK_H
#define IBLOCK_H

#include "block.h"


using namespace std;

class IBlock : public Block {
    public: 
        // constructor
        IBlock(int l);

        // getter
        char getType() const override;

};

#endif

