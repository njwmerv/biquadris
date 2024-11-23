#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <vector>

class View; // forward declaration

class Controller{
  // std::vector<Player*> players; TODO
  std::vector<View*> observers;

  public:
    void notifyObservers() const;

    void attachView(View*);

    void detachView(View*);

    const std::vector<Player*>& getPlayers() const;
};

#endif //CONTROLLER_H
