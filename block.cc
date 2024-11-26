#include "block.h"

extern const int maxRotations;
extern int startRotations;
extern int startCleared;
extern int startX;
extern int startY;
extern int startHeavy;

using namespace std;

void Block::clockwise(){numRotations = (numRotations + 1) % maxRotations;}

void Block::counterclockwise(){numRotations = (numRotations - 1) % maxRotations;}

vector <pair <int, int>> Block::getRotation(int i) {return rotations[i];}

int Block::getX() {return x;}

int Block::getY() {return y;}

bool Block::isHeavy() {return heavy;}

void Block::setX(int newX) {x = newX;}

void Block::setY(int newY) {y = newY;}

void Block::makeHeavy() {heavy = true;}