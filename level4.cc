#include "level4.h"
#include "level3.h"
using namespace std;


Block* Level4::generateBlock() {
    blockCount++;
    if (blockCount % 5 == 0) {
        // place1Block(); TODO Chloe
    }
    Level3 temp;
    return temp.generateBlock();

}

