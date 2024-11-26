#include "sblock.h"
#include <vector>

using namespace std;

SBlock::SBlock(int l){
    rotations[0] = {{0, 1}, {1, 1}, {1, 2}, {2, 2}};
    rotations[1] = {{1, 2}, {1, 1}, {2, 1}, {2, 0}};
    rotations[2] = rotations[0];
    rotations[3] = rotations[1];
    level = l;
}

char SBlock::getType() const {
    return 'S';
}
