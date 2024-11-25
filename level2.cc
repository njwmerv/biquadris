#include "level2.h"
#include "iblock.h"
#include "jblock.h"
#include "lblock.h"
#include "oblock.h"
#include "sblock.h"
#include "zblock.h"
#include "tblock.h"
#include <cstdlib>


Block *Level2::generateBlock() {
    string blockTypes[] = {"I", "J", "I", "L", "O", "S", "Z", "T"};
    int randomNum = rand() % 7;
    string blockGenerated = blockTypes[randomNum];

    if (blockGenerated == "I") {
        return new IBlock();
    } else if (blockGenerated == "J") {
        return new JBlock();
    } else if (blockGenerated == "L") {
        return new LBlock();
    } else if (blockGenerated == "O") {
        return new OBlock();
    } else if (blockGenerated == "S") {
        return new SBlock();
    } else if (blockGenerated == "Z") {
        return new ZBlock();
    } else if (blockGenerated == "T") {
        return new TBlock();
    }


}

