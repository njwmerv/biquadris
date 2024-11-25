#include "level1.h"
#include "iblock.h"
#include "jblock.h"
#include "lblock.h"
#include "oblock.h"
#include "sblock.h"
#include "zblock.h"
#include "tblock.h"


Block *Level1::generateBlock() {
    string blockTypes[] = {"I", "I", "J", "J", "L", "L", "O", "O", "S", "Z", "T", "T"};

    const int weightTotal = 12;

    int random = rand() % weightTotal;

    string blockGenerated = blockTypes[random];

    if (currentBlock == "I") {
        return new IBlock();
    } else if (currentBlock == "J") {
        return new JBlock();
    } else if (currentBlock == "L") {
        return new LBlock();
    } else if (currentBlock == "O") {
        return new OBlock();
    } else if (currentBlock == "S") {
        return new SBlock();
    } else if (currentBlck == "Z") {
        return new ZBlock();
    } else if (currentBlock == "T") {
        return new TBlock();
    }


}

