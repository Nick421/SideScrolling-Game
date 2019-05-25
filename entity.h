#pragma once

#include <vector>
#include <QPainter>

class Coordinate;
class RectCollider;

class Entity {

  public:
    Entity();
    Entity(Coordinate* position, std::string name);
    virtual ~Entity();

    Coordinate* getPosition();
    void setPosition(Coordinate* position);

    std::string getName() {
        return name;
    }
    std::vector<Entity*>& getChildren() {
        return children;
    }

    // Override this if your entity has a collider.
    virtual RectCollider* getCollider() {
        return nullptr;
    }
    virtual void onCollision(Entity* /*other */) {}

    virtual void update(bool paused, double time_since_last_frame) = 0;
    virtual void render(QPainter& painter) = 0;

    // stage 3
    virtual void resetLevel() = 0;

  protected:
    std::vector<Entity*> children;

  private:
    Coordinate* position;
    std::string name;
};

