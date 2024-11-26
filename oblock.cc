#include "oblock.h"
#include <vector>

using namespace std;

OBlock::OBlock(int l){
    rotations[0] = {{0, 2}, {0, 1}, {1, 2}, {1, 1}};
    rotations[1] = rotations[0];
    rotations[2] = rotations[0];
    rotations[3] = rotations[0];
}

char OBlock::getType() const {
    return 'O';
}