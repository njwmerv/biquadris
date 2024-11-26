#ifndef BLOCK_H
#define BLOCK_H

#include <vector>

using namespace std;

const int maxRotations = 4;
int startRotations = 0;
int startCleared = 0;
int startX = 0;
int startY = 0;

class Block {
    protected:
        vector <pair <int, int>> rotations [maxRotations];
        int level; // level of the board when the block was placed
        int numRotations = startRotations; // number of times the block has been rotated % 4
        int numCleared = startCleared; // number of cells that have been cleared
        int x = startX; // only matters when dropping
        int y = startY;
    public:

        // destructor
        virtual ~Block() {} 

        // get the type of the block
        virtual char getType() const = 0;

        // rotate the block clockwise
        void clockwise();

        // rotate the block counterclockwise
        void counterclockwise();

        // accessors
        vector <pair <int, int>> getRotation(int i);
        int getNumRotations();
        int getX();
        int getY();

        // mutators
        void setX(int newX);
        void setY(int newY);

};

#endif