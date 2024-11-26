#include "tblock.h"
#include <vector>

using namespace std;

TBlock::TBlock(int l){
    rotations[0] = {{0, 0}, {1, 0}, {2, 0}, {1, 1}};
    rotations[1] = {{0, 2}, {0, 1}, {0, 0}, {1, 1}};
    rotations[2] = {{0, 1}, {1, 1}, {1, 2}, {1, 0}};
    rotations[3] = {{0, 1}, {1, 1}, {1, 0}, {1, 2}};
}

char TBlock::getType() const {
    return 'T';
}
