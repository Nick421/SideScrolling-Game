#pragma once

#include <vector>
#include <cmath>
#include "player.h"
#include "stickman.h"
#include "config.h"
#include "physicsbody.h"
#include "obstacle.h"
#include "gamestate.h"

/*********************************************
 *  Design Pattern: Mediator                 *
 *  Concrete Colleague                       *
 *********************************************/

class StickmanPlayer : public Player {

  public:
    StickmanPlayer(Coordinate* position, std::string name);
    ~StickmanPlayer() override;

    virtual void jump() override;
    void checkGroundCollision();
    void landed();
    Obstacle* checkCollisions(std::vector<Obstacle*> obstacles);

    virtual RectCollider* getCollider() override {
        return &collider;
    }

    virtual void onCollision(Entity* other) override;
    virtual void update(bool paused, double time_since_last_frame) override;
    virtual void render(QPainter& painter) override;

    // stage 3
    // getter and setters for gravity, lives and current level
    void setGravity(double gravity) override;
    int getLives() override;
    void setLives(int lives) override;
    void loseLife() override;
    int getCurrentLevel() override;
    void setCurrentLevel(int level) override;
    double getGravity() override;

  private:
    // Coordinate for managing jumping and other movement independently to config positions.
    Coordinate* offset_position;
    PhysicsBody physics_body;
    RectCollider collider;

    double jump_height;
    double gravity;
    int jump_count;
    const int max_jump_count = 2;

    int frame_number;
    int counter;

    // stage 3
    int m_lives;
    int m_current_level;
};

