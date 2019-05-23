#pragma once

#include "compositeentity.h"

#include <string>

class EmptyEntity : public CompositeEntity {
  public:
    EmptyEntity(Coordinate* position, std::string name);

    virtual void update(bool paused, double time_since_last_frame) override;
    virtual void render(QPainter& painter) override;
};

