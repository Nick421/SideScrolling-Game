#include "gamestate.h"

#include "background.h"
#include "entity.h"
#include "player.h"
#include "rectcollider.h"
//stage 3
#include "config.h"
#include "powerup.h"

GameState::GameState()
    : player(nullptr),
      background(nullptr),
      root_entity(nullptr),
      player_colliding(false) {}

GameState::~GameState() {
    delete player;
    delete background;
    delete root_entity;
}

Entity* GameState::getRootEntity() {
    return root_entity;
}

Entity* GameState::findEntityByName(const std::string& name) {
    return findEntityByNameRecursive(name, root_entity);
}

Entity* GameState::findEntityByNameRecursive(const std::string& name, Entity* root) {
    if (root->getName() == name) {
        return root;
    }
    Entity* found = nullptr;
    for (auto* child : root_entity->getChildren()) {
        found = findEntityByNameRecursive(name, child);
        if (found != nullptr) {
            return found;
        }
    }
    return nullptr;
}

std::vector<Entity*> GameState::findEntitiesByNameContains(const std::string& string) {
    std::vector<Entity*> list;
    findEntitiesByNameContainsRecursive(string, root_entity, list);
    return list;
}

void GameState::findEntitiesByNameContainsRecursive(const std::string& string, Entity* root, std::vector<Entity*>& list) {
    if (root->getName().find(string) != std::string::npos) {
        list.push_back(root);
    }

    for (auto* child : root->getChildren()) {
        findEntitiesByNameContainsRecursive(string, child, list);
    }
}

void GameState::setRootEntity(Entity* root) {
    root_entity = root;
}

Background* GameState::getBackground() {
    return background;
}

Player* GameState::getPlayer() {
    return player;
}

void GameState::setBackground(Background* bg) {
    background = bg;
}

void GameState::setPlayer(Player* player) {
    this->player = player;
}

void GameState::checkCollisions() {
    bool player_collided = false;
    for (auto* entity : findEntitiesByNameContains("")) {
        // Check collisions with player
        RectCollider* p_col = getPlayer()->getCollider();
        RectCollider* o_col = entity->getCollider();
        if (p_col != nullptr && o_col != nullptr) {
            if (p_col->checkCollision(*o_col)) {
                getPlayer()->onCollision(entity);
                entity->onCollision(getPlayer());
                player_collided = true;
            }
        }
    }

    // stage 3
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
                }

                Config::config()->getStickman()->updateStickman();
                player_collided = true;
            }
        }
    }
    player_colliding = player_collided;
}

void GameState::update(bool paused) {
    checkCollisions();
    double deltaTimeMilliseconds = 32; // Comes from hard coded timer interval value in Stage1Game.
    getRootEntity()->update(paused || player_colliding, deltaTimeMilliseconds);
    if (getPlayer() != nullptr) {
        getPlayer()->update(paused, deltaTimeMilliseconds);
    }
}
