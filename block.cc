#include "block.h"

using namespace std;

void Block::clockwise(){numRotations = (numRotations + 1) % 4;}

void Block::counterclockwise(){numRotations = (numRotations - 1) % 4;}

vector <pair <int, int>> Block::getRotation(int i) {return rotations[i];}

int Block::getNumRotations() const {return numRotations;}

int Block::getX() const {return x;}

int Block::getY() const {return y;}

bool Block::isHeavy() const {return heavy;}

int Block::getLevel() const {return level;}

void Block::setX(int newX) {x = newX;}

void Block::setY(int newY) {y = newY;}

void Block::makeHeavy() {heavy = true;}