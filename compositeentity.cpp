#include "compositeentity.h"

CompositeEntity::CompositeEntity(Coordinate* position, std::string name)
    : Entity(position, name) {}


void CompositeEntity::addChild(Entity* e) {
    std::vector<Entity*>::iterator it;
    for (it = children.begin(); it != children.end(); it++) {
        if (*it == e) {
            return;
        }
    }
    children.push_back(e);
}

void CompositeEntity::removeChild(Entity* e) {
    std::vector<Entity*>::iterator it;
    for (it = children.begin(); it != children.end(); it++) {
        if (*it == e) {
            children.erase(it);
        }
    }
}

Entity* CompositeEntity::getChild(Entity* e) {
    std::vector<Entity*>::iterator it;
    for (it = children.begin(); it != children.end(); it++) {
        if (*it == e) {
            return *it;
        }
    }
    return nullptr;
}

void CompositeEntity::renderChildren(QPainter& painter) {
    std::vector<Entity*>::iterator it;
    for (it = children.begin(); it != children.end(); it++) {
        (*it)->render(painter);
    }
}

void CompositeEntity::updateChildren(bool paused, double deltaTimeMilliseconds) {
    std::vector<Entity*>::iterator it;
    for (it = children.begin(); it != children.end(); it++) {
        (*it)->update(paused, deltaTimeMilliseconds);
    }
}

void CompositeEntity::resetLevel() {
    std::vector<Entity*>::iterator it;
    for (it = children.begin(); it != children.end(); it++) {
        (*it)->resetLevel();
    }
}

