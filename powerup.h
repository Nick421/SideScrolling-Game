#ifndef POWERUP_H
#define POWERUP_H

#include "compositeentity.h"
#include "rectcollider.h"
#include "coordinate.h"

class PowerUp : public CompositeEntity {

  public:
    PowerUp(Coordinate* position, double width, double height,
            double velocity, double loop_after, QColor colour,
            std::string name, QImage image, std::string type);
    ~PowerUp() override = default;

    virtual RectCollider* getCollider() override {
        return &m_collider;
    }

    virtual void update(bool paused, double time_since_last_frame) override;
    virtual void render(QPainter& painter) override;

    bool isMoving() {
        return m_is_moving;
    }

    std::string get_type() {
        return m_type;
    }

  private:
    QColor m_colour;
    RectCollider m_collider;
    double m_width;
    double m_height;
    double m_velocity;
    double m_dist_travelled;
    double m_loop_after;
    bool m_is_moving;
    std::string m_type;
};

#endif // POWERUP_H
