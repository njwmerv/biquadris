#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include "controller.h"
#include "text.h"
#include "display.h"

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
      std::istringstream seedInput{argv[i + 1]};
      seedInput >> seed;
    }
    else if(arg == "-startlevel" && i + 1 < argc){
      std::istringstream startLevelInput{argv[i + 1]};
      startLevelInput >> startingLevel;
    }
    else if(arg == "-scriptfile1" && i + 1 < argc){
      std::istringstream scriptFileInput{argv[i + 1]};
      scriptFileInput >> scriptFile1;
    }
    else if(arg == "-scriptfile2" && i + 1 < argc){
      std::istringstream scriptFileInput{argv[i + 1]};
      scriptFileInput >> scriptFile2;
    }
  }
  Controller controller{seed, startingLevel, scriptFile1, scriptFile2};

  // Create displays
  std::vector<View*> displays;
  displays.emplace_back(new Text(&controller));
  if(!textOnly) displays.emplace_back(new Graphic(&controller));
  for(auto view : displays) controller.attachView(view);

  // Game loop, start reading input
  std::string input;
  int repetitions = 1;
  bool turnDone = false;
  while(true){ // Game loop
    Board* board = controller.getBoard();

    // Read input and get it interpreted by controller
    std::cin >> input;
    std::istringstream iss{input}; // maybe move this to inside interpretInput(str)
    if(!(iss >> repetitions)){ // TODO MARI: test this
      repetitions = 1;
      iss.clear();
    }
    const Controller::Command command = controller.interpretInput(iss.str());

    for(int i = 0; i < repetitions; i++){
      if(command == Controller::Command::LEFT) board->left()
      else if(command == Controller::Command::RIGHT) board->right()
      // TODO MARI: add the other commands
    }

    if(turnDone) controller.nextPlayer(); // TODO MARI: when is turnDone?
  }
  for(auto view : displays) delete view;
}