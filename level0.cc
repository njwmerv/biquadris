#include "level0.h"
#include "iblock.h"
#include "jblock.h"
#include "lblock.h"
#include "oblock.h"
#include "sblock.h"
#include "zblock.h"
#include "tblock.h"

using namespace std;

Level0::Level0(const string& filename) : file(filename), filename(filename) {}


Block *Level0::generateBlock() {
    if (!(file >> currentBlock)) {
        file.close();
        file.open(filename);
        if (!(file >> currentBlock)) {
            return nullptr;
        }

    }
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

