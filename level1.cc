#include "level1.h"
#include "iblock.h"
#include "jblock.h"
#include "lblock.h"
#include "oblock.h"
#include "sblock.h"
#include "zblock.h"
#include "tblock.h"
using namespace std;

Block* Level1::generateBlock(){
  const int maxWeight = 12;
  const string blockTypes[maxWeight] = {"I", "I", "J", "J", "L", "L", "O", "O", "S", "Z", "T", "T"};
  const string blockGenerated = blockTypes[rand() % maxWeight];

  if(blockGenerated == "I") return new IBlock(1);
  else if(blockGenerated == "J") return new JBlock(1);
  else if(blockGenerated == "L") return new LBlock(1);
  else if(blockGenerated == "O") return new OBlock(1);
  else if(blockGenerated == "S") return new SBlock(1);
  else if(blockGenerated == "Z") return new ZBlock(1);
  else if(blockGenerated == "T") return new TBlock(1);
  return new IBlock(1);
}

