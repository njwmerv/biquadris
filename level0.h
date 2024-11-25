#ifndef LEVEL0_H
#define LEVEL0_H
#include "level.h"
#include <fstream>
#include <string>
using namespace std;


class Level0 : public Level {
    ifstream file;
    string currentBlock;
    string filename;
    public:
        Level0(const string& filename);
        Block* generateBlock() override;
    
}

#endif
