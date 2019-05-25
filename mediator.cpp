#include "mediator.h"

Mediator::Mediator():
    m_score(0),
    m_finished(false),
    m_won(false) {

}

Mediator::~Mediator() {

}

void Mediator::checkCollisions() {
    GameState::checkCollisions();

    unsigned int world_height = Config::config()->getWorldHeight();
    unsigned int world_width = Config::config()->getWorldWidth();

    if (getPlayerColliding() == true) {
        getPlayer()->lose_life();
        // gotta somehow find a way to reset back.
        getPlayer()->setPosition(new Coordinate(0,
                                                0 + Config::config()->getStickman()->getHeight(),
                                                world_height,
                                                world_width));
        if (getPlayer()->get_lives() == 0) {
            //m_finished = true;
        }
    }

    for (auto* entity : findEntitiesByNameContains("power")) {
        // Check collisions with player
        RectCollider* p_col = getPlayer()->getCollider();
        RectCollider* o_col = entity->getCollider();
        if (p_col != nullptr && o_col != nullptr) {
            if (p_col->checkCollision(*o_col)) {
                getPlayer()->onCollision(entity);
                entity->onCollision(getPlayer());
                std::string type = static_cast<PowerUp*>(entity)->get_type();
                if (type.compare("Normal") == 0) {
                    Config::config()->getStickman()->changeSize("normal");
                    getPlayer()->set_gravity(-9.8 * 200);
                } else if (type.compare("Tiny") == 0) {
                    Config::config()->getStickman()->changeSize("tiny");
                    getPlayer()->set_gravity(-9.8 * 200);
                } else if (type.compare("Large") == 0) {
                    Config::config()->getStickman()->changeSize("large");
                    getPlayer()->set_gravity(-9.8 * 400);
                } else if (type.compare("Giant") == 0) {
                    // need invuln and explosion
                    Config::config()->getStickman()->changeSize("giant");
                    getPlayer()->set_gravity(-9.8 * 200);
                } else if (type.compare("Checkpoint") == 0) {
                    m_finished = true;
                    m_won = true;
                }
                m_score += 10;
                Config::config()->getStickman()->updateStickman();
                setPlayerColliding(true);
            }
        }
    }
}

int Mediator::getScore() {
    return m_score;
}

bool Mediator::isFinished() {
    return m_finished;
}

bool Mediator::didWon() {
    return m_won;
}
