#pragma once

#include <QPainter>
#include <QColor>
#include "compositeentity.h"
#include "rectcollider.h"

class Obstacle : public CompositeEntity {

  public:
    Obstacle(Coordinate* position, double width, double height, double velocity, double loop_after, QColor colour, std::string name);
    ~Obstacle() override = default;

    virtual RectCollider* getCollider() override {
        return &collider;
    }

    virtual void update(bool paused, double time_since_last_frame) override;
    virtual void render(QPainter& painter) override;

    bool isMoving() {
        return is_moving;
    }

  private:
    QColor colour;
    RectCollider collider;
    double width;
    double height;
    double velocity;
    double dist_travelled;
    double loop_after;
    bool is_moving;
};

