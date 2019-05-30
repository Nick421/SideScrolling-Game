#ifndef TESTSTAGE3_H
#define TESTSTAGE3_H

#include "stage3game.h"
#include "stickmanplayer.h"
#include "gamestatefactory.h"
#include "mediator.h"

#include <QDebug>

// Test class for stage 3
// Simulate unit testing and mostly test the mediator
class TestStage3 {
  public:
    TestStage3(std::unique_ptr<GameStateFactory>& factory);
    // run all the test cases
    void run();
  protected:
    void testLargePowerup();
    void testTinyPowerup();
    void testNormalPowerup();
    void testGiantPowerup();
    void testCheckpointWin();
    void testCheckpointNextLevel();
    void testLoseLife();
    void testGainLife();
    void testSpeedPowerup();
    void testGameover();
    void testReset();

  private:
    GameState* state;
    int num_cases_passed;
};

#endif // TESTSTAGE3_H
