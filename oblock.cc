#include "sblock.h"
#include <vector>

using namespace std;

OBlock::OBlock(int l) : level{l} {
    rotations[0] = {{1, 1}, {1, 2}, {2, 1}, {2, 2}};
    rotations[1] = rotations[0]
    rotations[2] = rotations[0]
    rotations[3] = rotations[0]
}

char OBlock::getType() const {
    return 'O';
}

void OBlock::clockwise() {
    numRotations = (numRotations + 1) % 4;
}

void OBlock::counterclockwise() {
    numRotations = (numRotations - 1) % 4;
}