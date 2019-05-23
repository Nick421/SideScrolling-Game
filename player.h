#pragma once

#include "compositeentity.h"

class Coordinate;

class Player : public CompositeEntity {

  public:
    Player(Coordinate* position, std::string name);
    virtual void jump() = 0;

    // stage 3
    virtual void set_gravity(double gravity) = 0;
};

