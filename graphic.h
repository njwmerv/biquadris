#ifndef TEXT_H
#define TEXT_H
#include "view.h"
#include "controller.h"
#include <iostream>
#include "window.h"

class Graphic : public View{
  Controller* controller;
  Xwindow window;

  public:
    Graphic(Controller* controller);

    ~Graphic();

    void notify() override;
};

#endif //TEXT_H
