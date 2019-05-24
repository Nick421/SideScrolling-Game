#pragma once

// Responsible for storing the game state of the current game, independently of rendering.

#include <string>
#include <vector>

#include <backgroundstage3.h>

class Background;
class Entity;
class Player;

class GameState {

  public:
    GameState();
    virtual ~GameState();

    Entity* getRootEntity();
    void setRootEntity(Entity* root);

    Entity* findEntityByName(const std::string& name);
    std::vector<Entity*> findEntitiesByNameContains(const std::string& string);

    BackgroundStage3* getBackground();
    void setBackground(BackgroundStage3* bg);

    Player* getPlayer();
    void setPlayer(Player* player);

    void update(bool paused);
    bool getPlayerColliding() {
        return player_colliding;
    }

  protected:
    void checkCollisions();

  private:
    Entity* findEntityByNameRecursive(const std::string& name, Entity* root);
    void findEntitiesByNameContainsRecursive(const std::string& string, Entity* root, std::vector<Entity*>& list);

    Player* player;
    BackgroundStage3* background;
    Entity* root_entity;
    bool player_colliding;
};

