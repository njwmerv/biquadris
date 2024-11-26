#ifndef IBLOCK_H
#define IBLOCK_H

#include "BLOCK_H"


using namespace std;

class IBlock : public Block {
    public: 
        // constructor
        IBlock(int l);

        // destructor
        ~IBlock() override;

        // getter
        char getType() const override;

};

#endif