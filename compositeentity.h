#pragma once

#include "entity.h"

#include <string>

/*********************************************
 *  Design Pattern: Mediator                 *
 *  Concrete Colleague                       *
 *********************************************/
class CompositeEntity : public Entity {
  public:
    CompositeEntity(Coordinate* position, std::string name);
    ~CompositeEntity() = default;

    void addChild(Entity* e);
    void removeChild(Entity* e);
    Entity* getChild(Entity* e);

    void renderChildren(QPainter& painter);
    void updateChildren(bool paused, double deltaTimeMilliseconds);

    //stage 3
    // this method is for resetting all obstacle on player collision
    void resetLevel();
};
