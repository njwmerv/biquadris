#include "block.h"

using namespace std;

void Block::clockwise(){numRotations = (numRotations + 1) % maxRotations;}

void Block::counterclockwise(){numRotations = (numRotations - 1) % maxRotations;}

vector <pair <int, int>> Block::getRotations() {return rotations;}



int Block::getX() {return x;}

int Block::getY() {return y;}

void Block::setX(int newX) {x = newX;}

void Block::setY(int newY) {y = newY;}
