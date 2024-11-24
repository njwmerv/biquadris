#ifndef TEXT_H
#define TEXT_H
#include "view.h"
#include <iostream>
#include "window.h"

class Graphic : public View{
  Xwindow window;

  public:
    Graphic(Controller* controller);

    ~Graphic() override;

    void notify() override;
};

#endif //TEXT_H
