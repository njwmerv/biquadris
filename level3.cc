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

    if(blockGenerated == "I") return new IBlock(3);
    else if(blockGenerated == "J") return new JBlock(3);
    else if(blockGenerated == "L") return new LBlock(3);
    else if(blockGenerated == "O") return new OBlock(3);
    else if(blockGenerated == "S") return new SBlock(3);
    else if(blockGenerated == "Z") return new ZBlock(3);
    else return new TBlock(3);
}
