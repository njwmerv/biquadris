#include "level4.h"
#include "iblock.h"
#include "jblock.h"
#include "lblock.h"
#include "oblock.h"
#include "sblock.h"
#include "zblock.h"
#include "tblock.h"
#include <cstdlib>
#include <fstream>

Level4::Level4(const string& path) : Level{path} {}

Block* Level4::generateBlock(){
    Block* block = nullptr;
    const int maxWeight = 9;
    const string blockTypes[maxWeight] = {"I", "J", "L", "O", "S", "S", "Z", "Z", "T"};
    string blockGenerated;
    if(isRandom){
        blockGenerated = blockTypes[rand() % maxWeight];
    }
    else if(filename != ""){
        if(!(file >> blockGenerated)){
            file.close();
            file.open(filename);
        }
        if(!(file >> blockGenerated)){
            isRandom = true; // file given is just empty
            return generateBlock();
        }
    }
    if(blockGenerated == "I") block = new IBlock(4);
    else if(blockGenerated == "J") block = new JBlock(4);
    else if(blockGenerated == "L") block = new LBlock(4);
    else if(blockGenerated == "O") block = new OBlock(4);
    else if(blockGenerated == "S") block = new SBlock(4);
    else if(blockGenerated == "Z") block = new ZBlock(4);
    else block = new TBlock(4);
    block->changeWeight(1);
    return block;
}
