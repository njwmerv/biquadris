#include "level2.h"
#include "iblock.h"
#include "jblock.h"
#include "lblock.h"
#include "oblock.h"
#include "sblock.h"
#include "zblock.h"
#include "tblock.h"
#include <cstdlib>
#include <string>
using namespace std;

Block *Level2::generateBlock(){
    const string blockTypes[] = {"I", "J", "I", "L", "O", "S", "Z", "T"};
    const string blockGenerated = blockTypes[rand() % 7];

    if(blockGenerated == "I") return new IBlock(1);
    else if(blockGenerated == "J") return new JBlock(1);
    else if(blockGenerated == "L") return new LBlock(1);
    else if(blockGenerated == "O") return new OBlock(1);
    else if(blockGenerated == "S") return new SBlock(1);
    else if(blockGenerated == "Z") return new ZBlock(1);
    else return new TBlock(1);
}

