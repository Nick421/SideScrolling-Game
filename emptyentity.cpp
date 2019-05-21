#include "emptyentity.h"

EmptyEntity::EmptyEntity(Coordinate* position, std::string name)
    : CompositeEntity(position, name){}


void EmptyEntity::update(bool paused, double time_since_last_frame) {
    this->updateChildren(paused, time_since_last_frame);
}

void EmptyEntity::render(QPainter &painter) {
    this->renderChildren(painter);
}

