#include "teststage3.h"


TestStage3::TestStage3(std::unique_ptr<GameStateFactory>& factory):
    state(factory->createGameState()),
    num_cases_passed(0) {

}

void TestStage3::run() {
    testLargePowerup();
    testTinyPowerup();
    testNormalPowerup();
    testGiantPowerup();
    testLoseLife();
    testGainLife();
    testSpeedPowerup();
    testReset();
    testGameover();
    testCheckpointNextLevel();
    testCheckpointWin();
    qDebug() << "Number of test cases passed:" << num_cases_passed << "/11";
}

/*
 * This check if mediator correctly change Stickman size
 * Expected the gravity to change as Large powerup makes you jump higher
*/
void TestStage3::testLargePowerup() {
    qDebug() << "1) testLargePowerup";
    dynamic_cast<Mediator*>(state)->largePowerup();
    qDebug() << "Expected: " << -3920 << "Actual: " << state->getPlayer()->getGravity();
    if (int(state->getPlayer()->getGravity()) == -int(9.8 * 400)) {
        qDebug() << "Pass!";
        num_cases_passed++;
    } else {
        qDebug() << "Fail!";
    }
}

/*
 * This check if mediator correctly change Stickman size
 * Expected the size to change to tiny
*/
void TestStage3::testTinyPowerup() {
    qDebug() << "2) testTinyPowerup";
    dynamic_cast<Mediator*>(state)->tinyPowerup();
    std::string actual = Config::config()->getStickman()->getSize();
    qDebug() << "Expected: " << "tiny" << "Actual: " << actual.c_str();
    if (actual == "tiny") {
        qDebug() << "Pass!";
        num_cases_passed++;
    } else {
        qDebug() << "Fail!";
    }
}

/*
 * This check if mediator correctly change Stickman size
 * Expected the size to change to normal
*/
void TestStage3::testNormalPowerup() {
    qDebug() << "3) testNormalPowerup";
    dynamic_cast<Mediator*>(state)->normalPowerup();
    std::string actual = Config::config()->getStickman()->getSize();
    qDebug() << "Expected: " << "normal" << "Actual: " << actual.c_str();
    if (actual == "normal") {
        qDebug() << "Pass!";
        num_cases_passed++;
    } else {
        qDebug() << "Fail!";
    }
}

/*
 * This check if mediator correctly change Stickman size
 * Expected the size to change to giant and check if colliding with obstacle
 * makes you inmmune (lose no life)
*/
void TestStage3::testGiantPowerup() {
    qDebug() << "4) testGiantPowerup";
    dynamic_cast<Mediator*>(state)->giantPowerup();
    std::string actual = Config::config()->getStickman()->getSize();
    qDebug() << "Expected: " << "giant" << "Actual: " << actual.c_str();
    if (actual == "giant") {
        int live = state->getPlayer()->getLives();
        state->setPlayerColliding(true);
        dynamic_cast<Mediator*>(state)->checkCollisions();
        qDebug() << "Expected: " << live << "Actual: " << state->getPlayer()->getLives();
        if (live == state->getPlayer()->getLives()) {
            qDebug() << "Pass!";
            num_cases_passed++;
        } else {
            qDebug() << "Fail!";
        }

    } else {
        qDebug() << "Fail!";
    }
}

/*
 * This check if mediator correctly change Stickman lives
 * Expected life to decrease by 1
*/
void TestStage3::testLoseLife() {
    qDebug() << "5) testLoseLife";
    dynamic_cast<Mediator*>(state)->normalPowerup();
    state->setPlayerColliding(true);
    dynamic_cast<Mediator*>(state)->checkCollisions();
    qDebug() << "Expected: 2 Actual: " << state->getPlayer()->getLives();
    if (state->getPlayer()->getLives() == 2) {
        qDebug() << "Pass!";
        num_cases_passed++;
    } else {
        qDebug() << "Fail!";
    }
}

/*
 * This check if mediator correctly change Stickman lives
 * Expected life to increase by 1
*/
void TestStage3::testGainLife() {
    qDebug() << "6) testGainLife";
    dynamic_cast<Mediator*>(state)->heart();
    qDebug() << "Expected: 3 Actual: " << state->getPlayer()->getLives();
    if (state->getPlayer()->getLives() == 3) {
        qDebug() << "Pass!";
        num_cases_passed++;
    } else {
        qDebug() << "Fail!";
    }
}

/*
 * This check if mediator correctly change Stickman speed
 * Expected the speed of stickman to increase
*/
void TestStage3::testSpeedPowerup() {
    qDebug() << "7) testSpeedPowerup";
    int speed = Config::config()->getInitialVelocity();
    dynamic_cast<Mediator*>(state)->speedup();
    qDebug() << "Expected: " << speed * 2 << " Actual: " << Config::config()->getVelocity();
    if (Config::config()->getVelocity() == speed * 2) {
        qDebug() << "Pass!";
        num_cases_passed++;
    } else {
        qDebug() << "Fail!";
    }
}

/*
 * This check if mediator correctly reset when Stickman hits obstacle
 * Expected collision to be false as when it reset the Stickman no longer colliding
*/
void TestStage3::testReset() {
    qDebug() << "8) testReset";
    dynamic_cast<Mediator*>(state)->normalPowerup();
    state->setPlayerColliding(true);
    dynamic_cast<Mediator*>(state)->checkCollisions();
    qDebug() << "Expected: false Actual: " << state->getPlayerColliding();
    if (!state->getPlayerColliding()) {
        qDebug() << "Pass!";
        num_cases_passed++;
    } else {
        qDebug() << "Fail!";
    }
}

/*
 * This check if mediator correctly go to Gameover
 * Simulate player colliding to obstacle with 1 life left
 * Expected life to decrease to 0 and then game finished is true but not won
*/
void TestStage3::testGameover() {
    qDebug() << "9) testGameover";
    dynamic_cast<Mediator*>(state)->normalPowerup();
    state->getPlayer()->setLives(1);
    state->setPlayerColliding(true);
    dynamic_cast<Mediator*>(state)->checkCollisions();
    qDebug() << "Expected: finished == true and lives == 0 Actual: " << dynamic_cast<Mediator*>(state)->isFinished()
             << " " << state->getPlayer()->getLives();
    if (state->getPlayer()->getLives() == 0 && dynamic_cast<Mediator*>(state)->isFinished() &&
            !dynamic_cast<Mediator*>(state)->didWon()) {
        qDebug() << "Pass!";
        num_cases_passed++;
    } else {
        qDebug() << "Fail!";
    }
}

/*
 * This check if mediator correctly go to next level
 * Expected current level for stickman to + 1
*/
void TestStage3::testCheckpointNextLevel() {
    qDebug() << "10) testCheckpointNextLevel";
    int level = state->getPlayer()->getCurrentLevel();
    dynamic_cast<Mediator*>(state)->checkpoint();
    qDebug() << "Expected: " << level + 1 << "Actual: " << state->getPlayer()->getCurrentLevel();
    if (state->getPlayer()->getCurrentLevel() == level + 1) {
        qDebug() << "Pass!";
        num_cases_passed++;
    } else {
        qDebug() << "Fail!";
    }
}

/*
 * This check if mediator correctly go to Winning state
 * Simulate player going to checkpoint at final level
 * Expected game finished is true and also won
*/
void TestStage3::testCheckpointWin() {
    qDebug() << "11) testCheckpointWin";
    state->getPlayer()->setCurrentLevel(2);
    dynamic_cast<Mediator*>(state)->setNumLevels(2);
    dynamic_cast<Mediator*>(state)->checkpoint();
    qDebug() << "Expected: " << "True" << "Actual: " << dynamic_cast<Mediator*>(state)->didWon();
    if (dynamic_cast<Mediator*>(state)->didWon() && dynamic_cast<Mediator*>(state)->isFinished()) {
        qDebug() << "Pass!";
        num_cases_passed++;
    } else {
        qDebug() << "Fail!";
    }

}
