#include "checkpoint.h"

CheckPoint::CheckPoint(Coordinate* position, double width, double height, double velocity, double loop_after, std::string name, QImage image):
    CompositeEntity (position, name),
    m_collider(RectCollider(new Coordinate(position->getXCoordinate() - width / 2.0, position->getYCoordinate() - height / 2.0, position->getFrameHeight(), position->getFrameWidth()),
                            new Coordinate(position->getXCoordinate() + width / 2.0, position->getYCoordinate() + height / 2.0, position->getFrameHeight(), position->getFrameWidth()))) {

}

void CheckPoint::update(bool paused, double time_since_last_frame) {
    if (!paused) {
        m_is_moving = true;

        // Keep collider in sync with position
        this->getPosition()->changeInXCoordinate(m_velocity);
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

void CheckPoint::render(QPainter& painter) {
    QBrush brush(Qt::gray);
    painter.setBrush(brush);

    if (getPosition() != nullptr) {
        double x = this->getPosition()->getQtRenderingXCoordinate();
        double y = this->getPosition()->getQtRenderingYCoordinate();
        painter.drawRect(x - m_width / 2.0, y - m_height / 2.0, m_width, m_height);
    }

    renderChildren(painter);
}
