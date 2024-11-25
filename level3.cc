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
