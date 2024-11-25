#ifndef IBLOCK_H
#define IBLOCK_H

#include "block.h"


using namespace std;

class IBlock : public Block {
    public: 
        // constructor
        IBlock(int l);

        // destructor
        ~IBlock() override;

        // getter
        char getType() const override;

        // rotate the block clockwise
        vector<pair<int, int>> clockwise () override;

        // rotate the block counterclockwise
        vector<pair<int, int>> counterclockwise () override;

};

#endif