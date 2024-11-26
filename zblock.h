#ifndef ZBLOCK_H
#define ZBLOCK_H

#include "block.h"


using namespace std;

class ZBlock : public Block {
public:
  // constructor
  ZBlock(int l);

  // destructor
  ~ZBlock() override;

  // getter
  char getType() const override;

};

#endif