#pragma once

// Responsible for storing the game state of the current game, independently of rendering.

#include <string>
#include <vector>

#include "backgroundstage3.h"

/*********************************************
 *  Design Pattern: Mediator                 *
 *  Mediator                                 *
 *********************************************/

class Background;
class Entity;
class Player;

class GameState {

  public:
    GameState();
    virtual ~GameState();

    virtual Entity* getRootEntity();
    void setRootEntity(Entity* root);

    virtual Entity* findEntityByName(const std::string& name);
    virtual std::vector<Entity*> findEntitiesByNameContains(const std::string& string);

    BackgroundStage3* getBackground();
    void setBackground(BackgroundStage3* bg);

    Player* getPlayer();
    void setPlayer(Player* player);

    virtual void update(bool paused);
    bool getPlayerColliding() {
        return player_colliding;
    }

    // stage 3
    void setPlayerColliding(bool collided) {
        player_colliding = collided;
    }
    // virtual method for mediator to implement
    virtual void setLevels(Entity** root) {}

  protected:
    virtual void checkCollisions();

  private:
    virtual Entity* findEntityByNameRecursive(const std::string& name, Entity* root);
    virtual void findEntitiesByNameContainsRecursive(const std::string& string, Entity* root, std::vector<Entity*>& list);

    Player* player;
    BackgroundStage3* background;
    Entity* root_entity;
    bool player_colliding;
};

