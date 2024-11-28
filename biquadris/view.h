#ifndef VIEW_H
#define VIEW_H

class View{
  public:
    virtual void notify() = 0;
    virtual ~View();
};

#endif //VIEW_H
