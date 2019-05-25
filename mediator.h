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

    void checkCollisions() override;
    int getScore();
    bool isFinished();
    bool didWon();

  private:
    int m_score;
    bool m_finished;
    bool m_won;
};

#endif // MEDIATOR_H
