#include "level3.h"
#include "iblock.h"
#include "jblock.h"
#include "lblock.h"
#include "oblock.h"
#include "sblock.h"
#include "zblock.h"
#include "tblock.h"
#include <cstdlib>

Block *Level3::generateBlock() {
    string BlockTypes[] = {"I", "J", "L", "O", "S", "S", "Z", "Z", "T"};
    const int weightTotal = 9;
    int random = rand() % weightTotal;

    string blockGenerated = blockTypes[random];

    if (blockGenerated == "I") {
        return new IBlock(1);
    } else if (blockGenerated == "J") {
        return new JBlock(1);
    } else if (blockGenerated == "L") {
        return new LBlock(1);
    } else if (blockGenerated == "O") {
        return new OBlock(1);
    } else if (blockGenerated == "S") {
        return new SBlock(1);
    } else if (blockGenerated == "Z") {
        return new ZBlock(1);
    } else if (blockGenerated == "T") {
        return new TBlock(1);
    }


}
