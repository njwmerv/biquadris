#include "level4.h"
#include "iblock.h"
#include "jblock.h"
#include "lblock.h"
#include "oblock.h"
#include "sblock.h"
#include "zblock.h"
#include "tblock.h"

using namespace std;


Block *Level4::generateBlock() {
    blockCount++;
    if (blockCount % 5 == 0) {
        place1Block();
    }
    return Level3::generateBlock();

}

