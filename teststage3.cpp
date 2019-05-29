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
            num_cases_passed++;
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
        num_cases_passed++;
    } else {
        qDebug() << "Fail!";
    }
}

void TestStage3::testGainLife() {
    qDebug() << "6) testGainLife";
    dynamic_cast<Mediator*>(state)->heart();
    qDebug() << "Expected: 3 Actual: " << state->getPlayer()->get_lives();
    if (state->getPlayer()->get_lives() == 3) {
        qDebug() << "Pass!";
        num_cases_passed++;
    } else {
        qDebug() << "Fail!";
    }
}

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

void TestStage3::testReset() {
    qDebug() << "8) testReset";
    dynamic_cast<Mediator*>(state)->normalPowerup();
    state->setPlayerColliding(true);
    dynamic_cast<Mediator*>(state)->checkCollisions();
    qDebug() << "Expected: false Actual: " << state->getPlayerColliding();
    if (state->getPlayerColliding() == false) {
        qDebug() << "Pass!";
        num_cases_passed++;
    } else {
        qDebug() << "Fail!";
    }
}

void TestStage3::testGameover() {
    qDebug() << "9) testGameover";
    dynamic_cast<Mediator*>(state)->normalPowerup();
    state->getPlayer()->set_lives(1);
    state->setPlayerColliding(true);
    dynamic_cast<Mediator*>(state)->checkCollisions();
    qDebug() << "Expected: finished == true and lives == 0 Actual: " << dynamic_cast<Mediator*>(state)->isFinished()
             << " " << state->getPlayer()->get_lives();
    if (state->getPlayer()->get_lives() == 0 && dynamic_cast<Mediator*>(state)->isFinished() &&
            dynamic_cast<Mediator*>(state)->didWon() == false) {
        qDebug() << "Pass!";
        num_cases_passed++;
    } else {
        qDebug() << "Fail!";
    }
}

void TestStage3::testCheckpointNextLevel() {
    qDebug() << "10) testCheckpointNextLevel";
    dynamic_cast<Mediator*>(state)->checkpoint();
    qDebug() << "Expected: " << "2" << "Actual: " << state->getPlayer()->getCurrentLevel();
    if (state->getPlayer()->getCurrentLevel() == 2) {
        qDebug() << "Pass!";
        num_cases_passed++;
    } else {
        qDebug() << "Fail!";
    }
}

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
