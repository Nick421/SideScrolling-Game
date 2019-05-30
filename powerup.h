#ifndef POWERUP_H
#define POWERUP_H

#include "compositeentity.h"
#include "rectcollider.h"
#include "coordinate.h"

/*********************************************
 *  Design Pattern: Mediator                 *
 *  Concrete Colleague                       *
 *********************************************/

/*
 * Powerup class
 * The class is nearly identical to obstacle class
 * only new method is getter for type
 * The type defined what type of powerup it is
*/
class PowerUp : public CompositeEntity {

  public:
    PowerUp(Coordinate* position, double width, double height,
            double velocity, double loop_after,
            std::string name, std::string type, QImage image);
    ~PowerUp() override = default;

    virtual RectCollider* getCollider() override {
        return &m_collider;
    }

    virtual void update(bool paused, double time_since_last_frame) override;
    virtual void render(QPainter& painter) override;

    bool isMoving() {
        return m_is_moving;
    }

    // getter for m_type
    std::string getType() {
        return m_type;
    }
    // reset method
    void resetLevel() override;

  private:
    QImage m_image;
    RectCollider m_collider;
    double m_width;
    double m_height;
    double m_velocity;
    double m_dist_travelled;
    double m_loop_after;
    bool m_is_moving;
    std::string m_type;
    int m_initial_x;
};

#endif // POWERUP_H
