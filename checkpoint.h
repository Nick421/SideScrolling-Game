#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include "compositeentity.h"
#include "rectcollider.h"
#include "coordinate.h"

class CheckPoint: public CompositeEntity {

  public:
    CheckPoint(Coordinate* position, double width, double height,
               double velocity, double loop_after, std::string name, QImage image);
    ~CheckPoint() override = default;

    virtual RectCollider* getCollider() override {
        return &m_collider;
    }

    virtual void update(bool paused, double time_since_last_frame) override;
    virtual void render(QPainter& painter) override;

  private:
    QColor m_colour;
    RectCollider m_collider;
    double m_width;
    double m_height;
    double m_velocity;
    double m_dist_travelled;
    bool m_is_moving;
};

#endif // CHECKPOINT_H
