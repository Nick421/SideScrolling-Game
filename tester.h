#pragma once

#include "gamestatefactory.h"
#include "obstacle.h"

#include <ctime>
#include <memory>

class Tester {
public:
    Tester(std::unique_ptr<GameStateFactory>& factory);
    virtual ~Tester();
    void run(int num_frames);

protected:
    void simulateUpdate();
    void simulateJump();
    void simulateTogglePause();

    bool assertCollisionBehaviour();

protected:
    GameState* state;
    bool paused;
};
