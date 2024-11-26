#include "zblock.h"
#include <vector>
using namespace std;

ZBlock::ZBlock(int l){
  rotations[0] = {{0, 1}, {1, 1}, {1, 0}, {2, 0}};
  rotations[1] = {{0, 0}, {0, 1}, {1, 1}, {1, 2}};
  rotations[2] = rotations[0];
  rotations[3] = rotations[1];
  level = l;
}

char ZBlock::getType() const {
  return 'Z';
}

void ZBlock::clockwise() {
  numRotations = (numRotations + 1) % 4;
}

void ZBlock::counterclockwise() {
  numRotations = (numRotations - 1) % 4;
}