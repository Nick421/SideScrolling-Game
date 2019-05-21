#include "entity.h"

#include "coordinate.h"

Entity::Entity()
    : children(std::vector<Entity*>()),
      position(nullptr) {}

Entity::Entity(Coordinate* position, std::string name)
    : children(std::vector<Entity*>()),
      position(position),
      name(name) {}

Entity::~Entity() {
    delete position;
}

Coordinate* Entity::getPosition() {
    return position;
}

void Entity::setPosition(Coordinate* position) {
    this->position = position;
}
