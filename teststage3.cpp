#include "teststage3.h"


TestStage3::TestStage3(std::unique_ptr<GameStateFactory>& factory):
    state(factory->createGameState()) {

}

void TestStage3::run() {
    testLargePowerup();
    testTinyPowerup();
    testNormalPowerup();
    testGiantPowerup();
    testLoseLife();
    testReset();
    testGameover();
    testCheckpointNextLevel();
    testCheckpointWin();
}

void TestStage3::testLargePowerup() {
    qDebug() << "1) testLargePowerup";
    dynamic_cast<Mediator*>(state)->largePowerup();
    qDebug() << "Expected: " << -3920 << "Actual: " << state->getPlayer()->getGravity();
    if (int(state->getPlayer()->getGravity()) == -int(9.8 * 400)) {
        qDebug() << "Pass!";
    } else {
        qDebug() << "Fail!";
    }
}

void TestStage3::testTinyPowerup() {
    qDebug() << "2) testTinyPowerup";
    dynamic_cast<Mediator*>(state)->tinyPowerup();
    std::string actual = Config::config()->getStickman()->getSize();
    qDebug() << "Expected: " << "tiny" << "Actual: " << actual.c_str();
    if (actual == "tiny") {
        qDebug() << "Pass!";
    } else {
        qDebug() << "Fail!";
    }
}

void TestStage3::testNormalPowerup() {
    qDebug() << "3) testNormalPowerup";
    dynamic_cast<Mediator*>(state)->normalPowerup();
    std::string actual = Config::config()->getStickman()->getSize();
    qDebug() << "Expected: " << "normal" << "Actual: " << actual.c_str();
    if (actual == "normal") {
        qDebug() << "Pass!";
    } else {
        qDebug() << "Fail!";
    }
}

void TestStage3::testGiantPowerup() {
    qDebug() << "4) testGiantPowerup";
    dynamic_cast<Mediator*>(state)->giantPowerup();
    std::string actual = Config::config()->getStickman()->getSize();
    qDebug() << "Expected: " << "giant" << "Actual: " << actual.c_str();
    if (actual == "giant") {
        int live = state->getPlayer()->get_lives();
        state->setPlayerColliding(true);
        dynamic_cast<Mediator*>(state)->checkCollisions();
        qDebug() << "Expected: " << live << "Actual: " << state->getPlayer()->get_lives();
        if (live == state->getPlayer()->get_lives()) {
            qDebug() << "Pass!";
        } else {
            qDebug() << "Fail!";
        }

    } else {
        qDebug() << "Fail!";
    }
}

void TestStage3::testLoseLife() {
    qDebug() << "5) testLoseLife";
    dynamic_cast<Mediator*>(state)->normalPowerup();
    state->setPlayerColliding(true);
    dynamic_cast<Mediator*>(state)->checkCollisions();
    qDebug() << "Expected: 2 Actual: " << state->getPlayer()->get_lives();
    if (state->getPlayer()->get_lives() == 2) {
        qDebug() << "Pass!";
    } else {
        qDebug() << "Fail!";
    }
}

void TestStage3::testReset() {
    qDebug() << "6) testReset";
    dynamic_cast<Mediator*>(state)->normalPowerup();
    state->setPlayerColliding(true);
    dynamic_cast<Mediator*>(state)->checkCollisions();
    qDebug() << "Expected: false Actual: " << state->getPlayerColliding();
    if (state->getPlayerColliding() == false) {
        qDebug() << "Pass!";
    } else {
        qDebug() << "Fail!";
    }
}

void TestStage3::testGameover() {
    qDebug() << "7) testGameover";
    dynamic_cast<Mediator*>(state)->normalPowerup();
    state->getPlayer()->set_lives(1);
    state->setPlayerColliding(true);
    dynamic_cast<Mediator*>(state)->checkCollisions();
    qDebug() << "Expected: finished == true and lives == 0 Actual: " << dynamic_cast<Mediator*>(state)->isFinished()
             << " " << state->getPlayer()->get_lives();
    if (state->getPlayer()->get_lives() == 0 && dynamic_cast<Mediator*>(state)->isFinished() &&
            dynamic_cast<Mediator*>(state)->didWon() == false) {
        qDebug() << "Pass!";
    } else {
        qDebug() << "Fail!";
    }
}

void TestStage3::testCheckpointNextLevel() {
    qDebug() << "8) testCheckpointNextLevel";
    dynamic_cast<Mediator*>(state)->checkpoint();
    qDebug() << "Expected: " << "2" << "Actual: " << state->getPlayer()->getCurrentLevel();
    if (state->getPlayer()->getCurrentLevel() == 2) {
        qDebug() << "Pass!";
    } else {
        qDebug() << "Fail!";
    }
}

void TestStage3::testCheckpointWin() {
    qDebug() << "9) testCheckpointWin";
    state->getPlayer()->setCurrentLevel(2);
    dynamic_cast<Mediator*>(state)->setNumLevels(2);
    dynamic_cast<Mediator*>(state)->checkpoint();
    qDebug() << "Expected: " << "True" << "Actual: " << dynamic_cast<Mediator*>(state)->didWon();
    if (dynamic_cast<Mediator*>(state)->didWon() && dynamic_cast<Mediator*>(state)->isFinished()) {
        qDebug() << "Pass!";
    } else {
        qDebug() << "Fail!";
    }

}
