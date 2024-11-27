#include "level4.h"
#include "level3.h"
using namespace std;


Block* Level4::generateBlock() {
    // the external constructive force is implemented in board
    Level3 temp;
    return temp.generateBlock();

}

