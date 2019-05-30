#ifndef MEDIATOR_H
#define MEDIATOR_H

#include "gamestate.h"
#include "config.h"
#include "powerup.h"
#include "backgroundstage3.h"
#include "entity.h"
#include "player.h"
#include "rectcollider.h"


/*********************************************
 *  Design Pattern: Mediator                 *
 *  Concrete Mediator
 *********************************************/

// this class is a subclass of Gamestate which was a psuedo mediator already
// it overrides all the method to support multiple levels

class Mediator : public GameState {
  public:
    Mediator();
    ~Mediator() override;

    // all method from GameState class
    Entity* getRootEntity() override;
    Entity* findEntityByName(const std::string& name) override;
    Entity* findEntityByNameRecursive(const std::string& name, Entity* root) override;
    std::vector<Entity*> findEntitiesByNameContains(const std::string& string) override;
    void findEntitiesByNameContainsRecursive(const std::string& string, Entity* root, std::vector<Entity*>& list) override;
    void update(bool paused) override;
    void setLevels(Entity** root) override;
    void checkCollisions() override;

    // Getters and setters
    int getScore();
    bool isFinished();
    bool didWon();
    void setNumLevels(int level);

    // methods for powerups and other objects
    void largePowerup();
    void tinyPowerup();
    void normalPowerup();
    void giantPowerup();
    void speedup();
    void checkpoint();
    void heart();
    void konamiCode();

    void destroyObject(Entity* e);

  private:
    Entity** m_levels{}; // List of list of entities each level of list of entities
    int m_score;
    bool m_finished;
    bool m_won;
    int m_num_levels;
    bool m_giant;
};

#endif // MEDIATOR_H
