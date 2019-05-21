#include "tester.h"

#include "gamestate.h"
#include "player.h"

#include <iostream>

Tester::Tester(std::unique_ptr<GameStateFactory>& factory)
    : state(factory->createGameState()),
      paused(false) {}

Tester::~Tester()
{
    delete state;
}

void Tester::run(int num_frames) {
    std::srand(std::time(nullptr));
    for (int i = 0; i < num_frames; ++i) {
        if (paused) {
            simulateTogglePause();
        } else {
            // Jump (1/100) or pause (1/250) randomly
            int roll = std::rand();
            if (roll < RAND_MAX / 100.0) {
                simulateJump();
            } else if (roll > RAND_MAX * 249.0 / 250.0) {
                simulateTogglePause();
            }
        }
        simulateUpdate();
        assertCollisionBehaviour();
        std::cout << std::endl;
    }
}

void Tester::simulateUpdate() {
    state->update(paused);
    std::cout << "Update simulated" << std::endl;

}

void Tester::simulateJump() {
    state->getPlayer()->jump();
    std::cout << "Jump simulated" << std::endl;
}

void Tester::simulateTogglePause() {
    paused = !paused;
    if (paused) {
        std::cout << "Paused" << std::endl;
    } else {
        std::cout << "Unpaused" << std::endl;
    }
}

bool Tester::assertCollisionBehaviour() {
    // Ensure that collisions stop movement of background and obstacles
    if (state->getPlayerColliding()) {
        std::vector<Entity*> obstacles = state->findEntitiesByNameContains("obstacle");
        for (auto* obstacle : obstacles) {
            Obstacle* o = dynamic_cast<Obstacle*>(obstacle);
            if (o->isMoving()) {
                std::cerr << "Invalid obstacle collision behaviour" << std::endl;
                return false;
            }
        }
    }

    std::cout << "Passed obstacle collision behaviour test." << std::endl;

    return true;
}
