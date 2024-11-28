#include "fourblock.h"
#include <vector>

using namespace std;

// 1x1 block for level 4

fourBlock :: fourBlock(int l) {
    rotations[0] = {{0,0}};
    rotations[1] = rotations[0];
    rotations[2] = rotations[0];
    rotations[3] = rotations[0];

    level = l;
}

char fourBlock :: getType() const {
    return '*';
}