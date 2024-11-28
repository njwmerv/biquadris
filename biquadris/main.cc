#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include "controller.h"
#include "text.h"
#include "graphic.h"
#include "block.h"
using namespace std;

int main(int argc, char* argv[]){
  // Game setup
  // Read CLI args
  string arg;
  bool textOnly = false;
  int startingLevel = 0;
  string scriptFile1 = "sequence1.txt";
  string scriptFile2 = "sequence2.txt";
  for(int i = 1; i < argc; i++){
    istringstream iss{argv[i]};
    iss >> arg;

    if(arg == "-text") textOnly = true;
    else if(arg == "-seed" && i + 1 < argc){
      string str = argv[i + 1];
      if(str == "random"){
        srand(time(nullptr));
        i++;
        continue;
      }
      int seed;
      istringstream seedInput{str};
      if(seedInput >> seed) srand(seed);
      i++;
    }
    else if(arg == "-startlevel" && i + 1 < argc){
      string str = argv[i + 1];
      istringstream startLevelInput{str};
      startLevelInput >> startingLevel;
      i++;
    }
    else if(arg == "-scriptfile1" && i + 1 < argc){
      string str = argv[i + 1];
      istringstream scriptFileInput{str};
      scriptFileInput >> scriptFile1;
      i++;
    }
    else if(arg == "-scriptfile2" && i + 1 < argc){
      string str = argv[i + 1];
      istringstream scriptFileInput{str};
      scriptFileInput >> scriptFile2;
      i++;
    }
    else{cerr << arg << " is not a valid command line argument" << endl;}
  }
  Controller controller{startingLevel, scriptFile1, scriptFile2};

  // Create displays
  vector<View*> displays;
  displays.emplace_back(new Text(&controller));
  if(!textOnly) displays.emplace_back(new Graphic(&controller));

  // Game loop
  controller.runGame();
  for(auto view : displays) delete view;
}