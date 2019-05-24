#pragma once

#include "compositeentity.h"

class Coordinate;

class Player : public CompositeEntity {

  public:
    Player(Coordinate* position, std::string name);
    virtual void jump() = 0;

    // stage 3
    virtual void set_gravity(double gravity) = 0;
    virtual int get_lives() = 0;
    virtual void set_lives(int lives) = 0;
    virtual void lose_life() = 0;
};

