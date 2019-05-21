#pragma once

#include "collider.h"

class Coordinate;

class RectCollider : public Collider {
public:
    RectCollider(Coordinate* v1, Coordinate* v2);
    ~RectCollider();
    bool checkCollision(const RectCollider& other);
    Coordinate* getV1() {return v1;}
    Coordinate* getV2() {return v2;}
    double getMinXBound() const;
    double getMaxXBound() const;
    double getMinYBound() const;
    double getMaxYBound() const;

protected:
    Coordinate* v1;
    Coordinate* v2;
};
