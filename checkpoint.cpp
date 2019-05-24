#include "checkpoint.h"

CheckPoint::CheckPoint(Coordinate* position, double width, double height, std::string name, QImage image, std::string type):
    CompositeEntity (position, name),
    m_collider(RectCollider(new Coordinate(position->getXCoordinate() - width / 2.0, position->getYCoordinate() - height / 2.0, position->getFrameHeight(), position->getFrameWidth()),
                            new Coordinate(position->getXCoordinate() + width / 2.0, position->getYCoordinate() + height / 2.0, position->getFrameHeight(), position->getFrameWidth()))),
    m_is_moving(true),
    m_type(type),
    m_image(image),
    m_width(width),
    m_height(height) {

}

void CheckPoint::update(bool paused, double time_since_last_frame) {
    if (!paused) {
        m_is_moving = true;

        // Keep collider in sync with position
        this->getPosition()->changeInXCoordinate(-Config::config()->getStickman()->getVelocity());
        m_collider.getV1()->setXCoordinateToZero(getPosition()->getXCoordinate() - m_width / 2.0);
        m_collider.getV1()->setYCoordinateToZero(getPosition()->getYCoordinate() - m_height / 2.0);
        m_collider.getV2()->setXCoordinateToZero(getPosition()->getXCoordinate() + m_width / 2.0);
        m_collider.getV2()->setYCoordinateToZero(getPosition()->getYCoordinate() + m_height / 2.0);

        updateChildren(paused, time_since_last_frame);

    } else {
        m_is_moving = false;
    }
}

void CheckPoint::render(QPainter& painter) {

    if (getPosition() != nullptr) {
        double x = this->getPosition()->getQtRenderingXCoordinate();
        double y = this->getPosition()->getQtRenderingYCoordinate();
        painter.drawImage(x - m_width / 2.0, y - m_height / 2.0, m_image);
    }

    renderChildren(painter);
}
