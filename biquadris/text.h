#ifndef TEXT_H
#define TEXT_H
#include "view.h"
#include "controller.h"
#include <iostream>

class Text : public View{
  Controller* controller;
  std::ostream& out = std::cout;

  public:
    Text(Controller* controller);

    ~Text();

    void notify() override;
};

#endif //TEXT_H
