#ifndef LEVEL_H
#define LEVEL_H
#include <fstream>
#include <string>
#include "block.h"
using namespace std;

class Level {
    protected:
      ifstream file;
      string filename = "";
      bool isRandom = false;

    public:
        Level(const string& path = "");
        virtual ~Level(){}

        virtual Block *generateBlock() = 0;

        // Mutators
        void setRandomness(bool);
        void setFileName(const string&);
};

#endif
