#ifndef fourBLOCK_H
#define fourBLOCK_H

#include "block.h"


using namespace std;

class fourBlock : public Block {
    public: 
        // constructor
        fourBlock(int l);

        // getter
        char getType() const override;

};

#endif