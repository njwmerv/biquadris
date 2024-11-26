#include "iblock.h"
#include <vector>

using namespace std;

IBlock :: IBlock(int l) {
    rotations[0] = {{0, 0}, {1, 0}, {2, 0}, {3, 0}};
    rotations[1] = {{0, 1}, {0, 2}, {0, 3}, {0, 4}};
    rotations[2] = rotations[0];
    rotations[3] = rotations[1];

    level = l;
}

IBlock :: ~IBlock() {

}

char IBlock :: getType() const {
    return 'I';
}