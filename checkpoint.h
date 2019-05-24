#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include "compositeentity.h"
#include "rectcollider.h"
#include "coordinate.h"
#include "config.h"

class CheckPoint: public CompositeEntity {

  public:
    CheckPoint(Coordinate* position, double width, double height,
               std::string name, QImage image, std::string type);
    ~CheckPoint() override = default;

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
    QImage m_image;
    RectCollider m_collider;
    double m_width;
    double m_height;
    bool m_is_moving;
    std::string m_type;
};

#endif // CHECKPOINT_H
