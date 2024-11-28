#include "level3.h"
#include "iblock.h"
#include "jblock.h"
#include "lblock.h"
#include "oblock.h"
#include "sblock.h"
#include "zblock.h"
#include "tblock.h"
#include <cstdlib>
#include <fstream>

Level3::Level3(const string& path) : Level{path} {}

Block* Level3::generateBlock(){
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
