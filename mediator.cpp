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

// override from GameState to return the current level
Entity* Mediator::getRootEntity() {
    return m_levels[getPlayer()->getCurrentLevel() - 1];
}

// override from GameState to return the entity in current level
Entity* Mediator::findEntityByName(const std::string& name) {

    return findEntityByNameRecursive(name, m_levels[getPlayer()->getCurrentLevel() - 1]);
}

// override from GameState to search the current level
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

// override from GameState to search the current level
std::vector<Entity*> Mediator::findEntitiesByNameContains(const std::string& string) {
    std::vector<Entity*> list;
    findEntitiesByNameContainsRecursive(string, m_levels[getPlayer()->getCurrentLevel() - 1], list);
    return list;
}

// override from GameState as it was a private method
void Mediator::findEntitiesByNameContainsRecursive(const std::string& string, Entity* root, std::vector<Entity*>& list) {
    if (root->getName().find(string) != std::string::npos) {
        list.push_back(root);
    }

    for (auto* child : root->getChildren()) {
        findEntitiesByNameContainsRecursive(string, child, list);
    }
}

// override from GameState as it was a private method
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

// override from GameState to handle powerups and other objects
void Mediator::checkCollisions() {

    // check collisions for obstacles only
    for (auto* entity : findEntitiesByNameContains("obstacle")) {
        // Check collisions with player
        RectCollider* p_col = getPlayer()->getCollider();
        RectCollider* o_col = entity->getCollider();
        if (p_col != nullptr && o_col != nullptr) {
            if (p_col->checkCollision(*o_col)) {
                getPlayer()->onCollision(entity);
                entity->onCollision(getPlayer());
                setPlayerColliding(true);

                // if in giant mode destory the obstacle
                if (m_giant) {
                    m_score += 10;
                    setPlayerColliding(false);
                    dynamic_cast<CompositeEntity*>(m_levels[getPlayer()->getCurrentLevel() - 1])->removeChild(entity);
                }

            }
        }
    }

    // if hitting obstacle and not giant, lose life

    if (getPlayerColliding()) {
        if (!m_giant && !m_finished) {
            getPlayer()->loseLife();

            // if life is 0 then gameover else reset
            if (getPlayer()->getLives() == 0) {
                m_finished = true;
            } else {
                dynamic_cast<CompositeEntity*>(m_levels[getPlayer()->getCurrentLevel() - 1])->resetLevel();
                setPlayerColliding(false);
            }
        }
    }

    // Check collision with only powerups and checkpoint
    for (auto* entity : findEntitiesByNameContains("power")) {
        // Check collisions with player
        RectCollider* p_col = getPlayer()->getCollider();
        RectCollider* o_col = entity->getCollider();
        if (p_col != nullptr && o_col != nullptr) {
            if (p_col->checkCollision(*o_col)) {
                getPlayer()->onCollision(entity);
                entity->onCollision(getPlayer());
                // get the type of object collided with
                std::string type = dynamic_cast<PowerUp*>(entity)->getType();

                // call respective method for each objects
                if (type == "Normal") {
                    normalPowerup();
                    destroyObject(entity);
                } else if (type == "Tiny") {
                    tinyPowerup();
                    destroyObject(entity);
                } else if (type == "Large") {
                    largePowerup();
                    destroyObject(entity);
                } else if (type == "Giant") {
                    giantPowerup();
                    destroyObject(entity);
                } else if (type == "Checkpoint") {
                    checkpoint();
                } else if (type == "Speedup") {
                    speedup();
                    destroyObject(entity);
                } else if (type == "Heart") {
                    heart();
                    destroyObject(entity);
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

// Large mode can jump higher so gravity is modify
void Mediator::largePowerup() {
    Config::config()->getStickman()->changeSize("large");
    getPlayer()->setGravity(-9.8 * 400);
    m_score += 10;
    m_giant = false;
}

void Mediator::tinyPowerup() {
    Config::config()->getStickman()->changeSize("tiny");
    getPlayer()->setGravity(-9.8 * 200);
    m_score += 10;
    m_giant = false;
}

void Mediator::normalPowerup() {
    Config::config()->getStickman()->changeSize("normal");
    getPlayer()->setGravity(-9.8 * 200);
    m_score += 10;
    m_giant = false;
}

void Mediator::giantPowerup() {
    Config::config()->getStickman()->changeSize("giant");
    getPlayer()->setGravity(-9.8 * 200);
    m_giant = true;
    m_score += 10;
}

// speed up doubles your velocity
void Mediator::speedup() {
    Config::config()->setVelocity(Config::config()->getInitialVelocity() * 2);
    m_score += 10;
    m_giant = false;
}

void Mediator::checkpoint() {
    // if player is on last level and reached checkpoint
    // set finisehd and won to true
    // else +10 to score and go to next level
    if (getPlayer()->getCurrentLevel() == m_num_levels) {
        m_finished = true;
        m_won = true;
    } else {
        m_score += 10;
        getPlayer()->setCurrentLevel(getPlayer()->getCurrentLevel() + 1);
    }
}

void Mediator::heart() {
    getPlayer()->setLives(getPlayer()->getLives() + 1);
    m_score += 10;
    m_giant = false;
}

// Konami code allows you to randomly destory number of obstacles
// depends on how many lives you have
// if you have 1 life you can't use it
// rand() % 2 is 50% chance of destroying an obstacle
void Mediator::konamiCode() {
    for (auto* entity : findEntitiesByNameContains("obstacle")) {
        if (getPlayer()->getLives() == 1) {
            break;
        }
        if (rand() % 2 == 0) {
            destroyObject(entity);
            getPlayer()->loseLife();
        }
    }
}

// remove the entity from the level (destory)
void Mediator::destroyObject(Entity* e) {
    dynamic_cast<CompositeEntity*>(m_levels[getPlayer()->getCurrentLevel() - 1])->removeChild(e);
}
