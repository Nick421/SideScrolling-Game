#ifndef MEDIATOR_H
#define MEDIATOR_H

#include "gamestate.h"
#include "config.h"
#include "powerup.h"
#include "backgroundstage3.h"
#include "entity.h"
#include "player.h"
#include "rectcollider.h"

class Mediator : public GameState {
  public:
    Mediator();
    ~Mediator() override;

    Entity* getRootEntity() override;
    Entity* findEntityByName(const std::string& name) override;
    Entity* findEntityByNameRecursive(const std::string& name, Entity* root) override;
    std::vector<Entity*> findEntitiesByNameContains(const std::string& string) override;
    void findEntitiesByNameContainsRecursive(const std::string& string, Entity* root, std::vector<Entity*>& list) override;
    void update(bool paused) override;
    void setLevels(Entity** root) override;
    void checkCollisions() override;
    int getScore();
    bool isFinished();
    bool didWon();
    void setNumLevels(int level);

  private:
    int m_score;
    bool m_finished;
    bool m_won;
    Entity** m_levels;
    int m_num_levels;
    bool m_giant;
};

#endif // MEDIATOR_H
