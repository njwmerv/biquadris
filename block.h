#ifndef BLOCK_H
#define BLOCK_H

#include <vector>

using namespace std;

const int maxRotations = 3;

class Block {
    protected:
        vector <pair <int, int>> rotations [maxRotations];
        int level;
        int numRotations;
        int x;
        int y;
    public:

        // destructor
        virtual ~Block() {} 

        // get the type of the block
        virtual char getType() const = 0;

        // rotate the block clockwise
        virtual void clockwise () = 0;

        // rotate the block counterclockwise
        virtual void counterclockwise () = 0;

};

#endif