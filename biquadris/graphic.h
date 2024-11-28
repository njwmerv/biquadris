#ifndef GRAPHIC_H
#define GRAPHIC_H
#include "view.h"
#include "controller.h"
#include "window.h"

class Graphic : public View{
  Controller* controller;
  Xwindow window;

  public:
    Graphic(Controller* controller);

    ~Graphic();

    void notify() override;
};

#endif //GRAPHIC_H
