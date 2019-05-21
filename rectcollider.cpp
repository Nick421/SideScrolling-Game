#include "rectcollider.h"
#include "coordinate.h"

RectCollider::RectCollider(Coordinate* v1, Coordinate* v2)
    : v1(v1),
      v2(v2) {}

RectCollider::~RectCollider() {
    delete v1;
    delete v2;
}

bool RectCollider::checkCollision(const RectCollider& other) {
    bool x_overlap = !(this->getMinXBound() > other.getMaxXBound() || this->getMaxXBound() < other.getMinXBound());
    bool y_overlap = !(this->getMinYBound() > other.getMaxYBound() || this->getMaxYBound() < other.getMinYBound());
    return x_overlap && y_overlap;
}

double RectCollider::getMinXBound() const {
    if (v1->getXCoordinate() < v2->getXCoordinate()) {
        return v1->getXCoordinate();
    } else {
        return v2->getXCoordinate();
    }
}

double RectCollider::getMaxXBound() const {
    if (v1->getXCoordinate() > v2->getXCoordinate()) {
        return v1->getXCoordinate();
    } else {
        return v2->getXCoordinate();
    }
}

double RectCollider::getMinYBound() const {
    if (v1->getYCoordinate() < v2->getYCoordinate()) {
        return v1->getYCoordinate();
    } else {
        return v2->getYCoordinate();
    }
}

double RectCollider::getMaxYBound() const {
    if (v1->getYCoordinate() > v2->getYCoordinate()) {
        return v1->getYCoordinate();
    } else {
        return v2->getYCoordinate();
    }
}

