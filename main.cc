#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include "controller.h"
#include "text.h"
#include "graphic.h"
#include "block.h"

int main(int argc, char* argv[]){
  // Game setup
  // Read CLI args
  std::string arg;
  bool textOnly = false;
  int seed = std::rand();
  int startingLevel = 0;
  std::string scriptFile1 = "sequence1.txt";
  std::string scriptFile2 = "sequence2.txt";
  for(int i = 1; i < argc; i++){
    std::istringstream iss{argv[i]};
    iss >> arg;

    if(arg == "-text") textOnly = true;
    else if(arg == "-seed" && i + 1 < argc){
      std::string str = argv[i + 1];
      std::istringstream seedInput{str};
      seedInput >> seed;
      i++;
    }
    else if(arg == "-startlevel" && i + 1 < argc){
      std::string str = argv[i + 1];
      std::istringstream startLevelInput{str};
      startLevelInput >> startingLevel;
      i++;
    }
    else if(arg == "-scriptfile1" && i + 1 < argc){
      std::string str = argv[i + 1];
      std::istringstream scriptFileInput{str};
      scriptFileInput >> scriptFile1;
      i++;
    }
    else if(arg == "-scriptfile2" && i + 1 < argc){
      std::string str = argv[i + 1];
      std::istringstream scriptFileInput{str};
      scriptFileInput >> scriptFile2;
      i++;
    }
    else{std::cerr << arg << " is not a valid command line argument" << std::endl;}
  }
  Controller controller{seed, startingLevel, scriptFile1, scriptFile2};

  // Create displays
  std::vector<View*> displays;
  displays.emplace_back(new Text(&controller));
  if(!textOnly) displays.emplace_back(new Graphic(&controller));

  // Game loop
  controller.runGame();
  for(auto view : displays) delete view;
}