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
    const string blockTypes[] = {"I", "J", "L", "O", "S", "S", "Z", "Z", "T"};
    const string blockGenerated = blockTypes[rand() % 9];
    Block* block = nullptr;
    if(blockGenerated == "I") block = new IBlock(3);
    else if(blockGenerated == "J") block = new JBlock(3);
    else if(blockGenerated == "L") block = new LBlock(3);
    else if(blockGenerated == "O") block = new OBlock(3);
    else if(blockGenerated == "S") block = new SBlock(3);
    else if(blockGenerated == "Z") block = new ZBlock(3);
    else block = new TBlock(3);
    block->changeWeight(1);
    return block;
}
