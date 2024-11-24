#ifndef TEXT_H
#define TEXT_H
#include "view.h"
#include <iostream>

class Text : public View{
  std::ostream& out = std::cout;

  public:
    Text(Controller* controller);

    ~Text() override;

    void notify() override;
};

#endif //TEXT_H
