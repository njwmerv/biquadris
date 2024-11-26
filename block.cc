#include "block.h"

using namespace std;

void Block::clockwise(){numRotations = (numRotations + 1) % maxRotations;}

void Block::counterclockwise(){numRotations = (numRotations - 1) % maxRotations;}

void Block::setX(int newX) {x = newX;}

void Block::setY(int newY) {y = newY;}
