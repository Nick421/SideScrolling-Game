#include "powerup.h"

#include "config.h"

PowerUp::PowerUp(Coordinate* position, double width, double height, double velocity, double loop_after, std::string name, std::string type, QImage image)
    : CompositeEntity(position, name),
      m_collider(RectCollider(new Coordinate(position->getXCoordinate() - width / 2.0, position->getYCoordinate() - height / 2.0, position->getFrameHeight(), position->getFrameWidth()),
                              new Coordinate(position->getXCoordinate() + width / 2.0, position->getYCoordinate() + height / 2.0, position->getFrameHeight(), position->getFrameWidth()))),
      m_velocity(velocity),
      m_dist_travelled(0),
      m_loop_after(loop_after),
      m_is_moving(true),
      m_type(type),
      m_image(image),
      m_width(width),
      m_height(height),
      m_initial_x(position->getQtRenderingXCoordinate()) {

}

void PowerUp::update(bool paused, double time_since_last_frame) {

    if (!paused) {
        m_is_moving = true;

        if (m_dist_travelled >= m_loop_after) {
            this->getPosition()->changeInXCoordinate(m_loop_after);
            m_dist_travelled = 0;
        }

        // Keep collider in sync with position
        this->getPosition()->changeInXCoordinate(-Config::config()->getStickman()->getVelocity());
        m_collider.getV1()->setXCoordinateToZero(getPosition()->getXCoordinate() - m_width / 2.0);
        m_collider.getV1()->setYCoordinateToZero(getPosition()->getYCoordinate() - m_height / 2.0);
        m_collider.getV2()->setXCoordinateToZero(getPosition()->getXCoordinate() + m_width / 2.0);
        m_collider.getV2()->setYCoordinateToZero(getPosition()->getYCoordinate() + m_height / 2.0);

        updateChildren(paused, time_since_last_frame);

        m_dist_travelled -= m_velocity;
    } else {
        m_is_moving = false;
    }
}

void PowerUp::render(QPainter& painter) {

    if (getPosition() != nullptr) {
        double x = this->getPosition()->getQtRenderingXCoordinate();
        double y = this->getPosition()->getQtRenderingYCoordinate();
        painter.drawImage(x - m_width / 2.0, y - m_height / 2.0, m_image);
    }

    renderChildren(painter);
}

// reset back to initial x position
void PowerUp::resetLevel() {
    setPosition(new Coordinate(m_initial_x, getPosition()->getYCoordinate(), getPosition()->getFrameHeight(), getPosition()->getFrameWidth()));
}
