#include "lblock.h"
#include <vector>

using namespace std;

LBlock :: LBlock(int l) {
    rotations[0] = {{0, 0}, {1, 0}, {2, 0}, {2, 1}};
    rotations[1] = {{0, 0}, {0, 1}, {0, 2}, {1, 0}};
    rotations[2] = {{0, 0}, {0, 1}, {1, 1}, {2, 1}};
    rotations[3] = {{0, 2}, {1, 2}, {1, 1}, {1, 0}};
    level = l;
}

char LBlock :: getType() const {
    return 'L';
}