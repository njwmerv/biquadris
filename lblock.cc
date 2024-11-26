#include "sblock.h"
#include <vector>

using namespace std;

LBlock :: LBlock(int l) {
    rotations[0] = {{0, 1}, {1, 1}, {2, 0}, {2, 1}};
    rotations[1] = {{1, 2}, {1, 1}, {1, 0}, {2, 0}};
    rotations[2] = {{0, 0}, {0, 1}, {1, 1}, {2, 1}};
    rotations[3] = {{0, 2}, {1, 2}, {1, 1}, {2, 0}};

    level = l;
}

char LBlock :: getType() const {
    return 'L';
}

void LBlock :: clockwise() {
    numRotations = (numRotations+1)%4;
}

void LBlock :: counterclockwise() {
    numRotations = (numRotations-1)%4;
}