#include "obstacle.h"

#include "coordinate.h"

//stage 3
#include "config.h"


Obstacle::Obstacle(Coordinate* position, double width, double height, double velocity, double loop_after, QColor colour, std::string name)
    : CompositeEntity(position, name),
      colour(colour),
      collider(RectCollider(new Coordinate(position->getXCoordinate() - width / 2.0, position->getYCoordinate() - height / 2.0, position->getFrameHeight(), position->getFrameWidth()),
                            new Coordinate(position->getXCoordinate() + width / 2.0, position->getYCoordinate() + height / 2.0, position->getFrameHeight(), position->getFrameWidth()))),
      velocity(velocity),
      dist_travelled(0),
      loop_after(loop_after),
      is_moving(true),
      initial_x(position->getQtRenderingXCoordinate()) {

    if (width > 0) {
        this->width = width;
    } else {
        this->width = 1;
    }

    if (height > 0) {
        this->height = height;
    } else {
        this->height = 1;
    }

}

void Obstacle::update(bool paused, double time_since_last_frame) {

    if (!paused) {
        is_moving = true;

        if (dist_travelled >= loop_after) {
            this->getPosition()->changeInXCoordinate(loop_after);
            dist_travelled = 0;
        }

        // Keep collider in sync with position
        //this->getPosition()->changeInXCoordinate(velocity);
        this->getPosition()->changeInXCoordinate(-Config::config()->getStickman()->getVelocity());
        collider.getV1()->setXCoordinateToZero(getPosition()->getXCoordinate() - width / 2.0);
        collider.getV1()->setYCoordinateToZero(getPosition()->getYCoordinate() - height / 2.0);
        collider.getV2()->setXCoordinateToZero(getPosition()->getXCoordinate() + width / 2.0);
        collider.getV2()->setYCoordinateToZero(getPosition()->getYCoordinate() + height / 2.0);

        updateChildren(paused, time_since_last_frame);

        dist_travelled -= velocity;
    } else {
        is_moving = false;
    }
}

void Obstacle::render(QPainter& painter) {
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(2);
    painter.setPen(pen);

    QBrush brush(colour);
    painter.setBrush(brush);

    if (getPosition() != nullptr) {
        double x = this->getPosition()->getQtRenderingXCoordinate();
        double y = this->getPosition()->getQtRenderingYCoordinate();
        painter.drawRect(x - width / 2.0, y - height / 2.0, width, height);
    }

    renderChildren(painter);
}

// stage 3
// only reset the x position
void Obstacle::resetLevel() {
    this->setPosition(new Coordinate(initial_x, getPosition()->getYCoordinate(), getPosition()->getFrameHeight(), getPosition()->getFrameWidth()));
}
