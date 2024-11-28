#ifndef BLOCK_H
#define BLOCK_H

#include <vector>

using namespace std;

class Block {
    protected:
        vector <pair <int, int>> rotations [4];
        int level; // level of the board when the block was placed
        int numRotations = 0; // number of times the block has been rotated % 4
        int numCleared = 0; // number of cells that have been cleared
        int x = 0; // far left, as specified
        int y = 14; // 1 below the 3 extra rows of space, as specified
        int heaviness = 0;
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
        int getNumRotations() const;
        int getX() const;
        int getY() const;
        int getHeaviness() const;
        int getLevel() const;

        // mutators
        void setX(int newX);
        void setY(int newY);
        void changeWeight(int);

};

#endif