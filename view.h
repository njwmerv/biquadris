#ifndef VIEW_H
#define VIEW_H
#include "controller.h"

class View{
  protected:
    Controller* controller;

  public:
    View(Controller* controller) : controller{controller} {
      controller->attachView(this);
    }

    virtual ~View() = 0;

    virtual void notify() = 0;
};

#endif //VIEW_H
