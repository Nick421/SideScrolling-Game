#pragma once

#include "entity.h"

class Coordinate;

class LeafEntity : public Entity {

public:
    LeafEntity(Coordinate* position, std::string name);
};

