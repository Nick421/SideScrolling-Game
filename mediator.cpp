#include "mediator.h"

Mediator::Mediator():
    m_score(0),
    m_finished(false),
    m_won(false),
    m_num_levels(0),
    m_giant(false) {

}

Mediator::~Mediator() {
    delete [] m_levels;
}

Entity* Mediator::getRootEntity() {
    return m_levels[getPlayer()->getCurrentLevel() - 1];
}

Entity* Mediator::findEntityByName(const std::string& name) {

    return findEntityByNameRecursive(name, m_levels[getPlayer()->getCurrentLevel() - 1]);
}

Entity* Mediator::findEntityByNameRecursive(const std::string& name, Entity* root) {
    if (root->getName() == name) {
        return root;
    }
    Entity* found = nullptr;
    for (auto* child : m_levels[getPlayer()->getCurrentLevel() - 1]->getChildren()) {
        found = findEntityByNameRecursive(name, child);
        if (found != nullptr) {
            return found;
        }
    }
    return nullptr;
}

std::vector<Entity*> Mediator::findEntitiesByNameContains(const std::string& string) {
    std::vector<Entity*> list;
    findEntitiesByNameContainsRecursive(string, m_levels[getPlayer()->getCurrentLevel() - 1], list);
    return list;
}

void Mediator::findEntitiesByNameContainsRecursive(const std::string& string, Entity* root, std::vector<Entity*>& list) {
    if (root->getName().find(string) != std::string::npos) {
        list.push_back(root);
    }

    for (auto* child : root->getChildren()) {
        findEntitiesByNameContainsRecursive(string, child, list);
    }
}

void Mediator::update(bool paused) {
    checkCollisions();
    double deltaTimeMilliseconds = 32; // Comes from hard coded timer interval value in Stage1Game.
    getRootEntity()->update(paused || getPlayerColliding(), deltaTimeMilliseconds);
    if (getPlayer() != nullptr) {
        getPlayer()->update(paused, deltaTimeMilliseconds);
    }
}

void Mediator::setLevels(Entity** root) {
    m_levels = root;
}

void Mediator::checkCollisions() {

    for (auto* entity : findEntitiesByNameContains("obstacle")) {
        // Check collisions with player
        RectCollider* p_col = getPlayer()->getCollider();
        RectCollider* o_col = entity->getCollider();
        if (p_col != nullptr && o_col != nullptr) {
            if (p_col->checkCollision(*o_col)) {
                getPlayer()->onCollision(entity);
                entity->onCollision(getPlayer());
                setPlayerColliding(true);
                if (m_giant == true) {
                    m_score += 10;
                    setPlayerColliding(false);
                    dynamic_cast<CompositeEntity*>(m_levels[getPlayer()->getCurrentLevel() - 1])->removeChild(entity);
                }
            }
        }
    }

    if (getPlayerColliding() == true) {
        if (m_giant != true && m_finished == false) {
            getPlayer()->lose_life();

            if (getPlayer()->get_lives() == 0) {
                m_finished = true;
            } else {
                dynamic_cast<CompositeEntity*>(m_levels[getPlayer()->getCurrentLevel() - 1])->resetLevel();
                setPlayerColliding(false);
            }
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
                    m_score += 10;
                    m_giant = false;
                    dynamic_cast<CompositeEntity*>(m_levels[getPlayer()->getCurrentLevel() - 1])->removeChild(entity);
                } else if (type.compare("Tiny") == 0) {
                    Config::config()->getStickman()->changeSize("tiny");
                    getPlayer()->set_gravity(-9.8 * 200);
                    m_score += 10;
                    m_giant = false;
                    dynamic_cast<CompositeEntity*>(m_levels[getPlayer()->getCurrentLevel() - 1])->removeChild(entity);
                } else if (type.compare("Large") == 0) {
                    Config::config()->getStickman()->changeSize("large");
                    getPlayer()->set_gravity(-9.8 * 400);
                    m_score += 10;
                    m_giant = false;
                    dynamic_cast<CompositeEntity*>(m_levels[getPlayer()->getCurrentLevel() - 1])->removeChild(entity);
                } else if (type.compare("Giant") == 0) {
                    // need explosion
                    Config::config()->getStickman()->changeSize("giant");
                    getPlayer()->set_gravity(-9.8 * 200);
                    m_giant = true;
                    m_score += 10;
                    dynamic_cast<CompositeEntity*>(m_levels[getPlayer()->getCurrentLevel() - 1])->removeChild(entity);
                } else if (type.compare("Checkpoint") == 0) {
                    if (getPlayer()->getCurrentLevel() == m_num_levels) {
                        m_finished = true;
                        m_won = true;
                    } else {
                        m_score += 10;
                        getPlayer()->setCurrentLevel(getPlayer()->getCurrentLevel() + 1);
                    }
                } else if (type.compare("Speedup") == 0) {
                    Config::config()->setInitialVelocity(Config::config()->getInitialVelocity() * 2);
                    m_score += 10;
                    m_giant = false;
                    dynamic_cast<CompositeEntity*>(m_levels[getPlayer()->getCurrentLevel() - 1])->removeChild(entity);
                }

                Config::config()->getStickman()->updateStickman();
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

void Mediator::setNumLevels(int level) {
    m_num_levels = level;
}
