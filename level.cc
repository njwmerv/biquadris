#include "level.h"
#include <fstream>

Level::Level(const string& path) : filename{path} {
  if(filename != "") file.open(filename);
}

// Mutators
void Level::setRandomness(bool nowRandom) {isRandom = nowRandom;}
void Level::setFileName(const string& path){
  filename = path;
  file.close();
  file.open(filename);
}