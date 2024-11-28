#include "jblock.h"
#include <vector>

using namespace std;

JBlock :: JBlock(int l) {
    rotations[0] = {{0, 1}, {0, 0}, {1, 0}, {2, 0}};
    rotations[1] = {{1, 2}, {0, 2}, {0, 1}, {0, 0}};
    rotations[2] = {{2, 0}, {2, 1}, {1, 1}, {0, 1}};
    rotations[3] = {{0, 0}, {1, 0}, {1, 1}, {1, 2}};

    level = l;
}


char JBlock :: getType() const {
    return 'J';
}
