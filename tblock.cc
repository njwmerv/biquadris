#include "tblock.h"
#include <vector>

using namespace std;

TBlock::TBlock(int l){
    rotations[0] = {{0, 0}, {1, 0}, {2, 0}, {1, 1}};
    rotations[1] = {{0, 0}, {0, 1}, {0, 2}, {1, 1}};
    rotations[2] = {{0, 2}, {1, 2}, {2, 2}, {1, 1}};
    rotations[3] = {{2, 0}, {2, 1}, {2, 2}, {1, 1}};
}

char TBlock::getType() const {
    return 'T';
}
