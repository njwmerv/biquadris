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

};

#endif