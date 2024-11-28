#ifndef fourBLOCK_H
#define fourBLOCK_H

#include "block.h"

// 1x1 block for level 4

using namespace std;

class fourBlock : public Block {
    public: 
        // constructor
        fourBlock(int l);

        // getter
        char getType() const override;

};

#endif

