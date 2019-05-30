#pragma once

#include "compositeentity.h"

/*********************************************
 *  Design Pattern: Mediator                 *
 *  Colleague                                *
 *********************************************/

class Coordinate;

class Player : public CompositeEntity {

  public:
    Player(Coordinate* position, std::string name);
    virtual void jump() = 0;

    /* stage 3
     * all virtual function for getters and setters
     * for all new member variables in Player
    */
    virtual void setGravity(double gravity) = 0;
    virtual double getGravity() = 0;
    virtual int getLives() = 0;
    virtual void setLives(int lives) = 0;
    virtual void loseLife() = 0;
    virtual int getCurrentLevel() = 0;
    virtual void setCurrentLevel(int level) = 0;
};

