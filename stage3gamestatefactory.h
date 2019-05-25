#ifndef STAGE3GAMESTATEFACTORY_H
#define STAGE3GAMESTATEFACTORY_H

#include "gamestatefactory.h"
#include "stickmanplayer.h"
#include "obstacle.h"
#include "gamestate.h"
#include "extendedconfig.h"
#include "emptyentity.h"
#include "powerup.h"
#include "backgroundstage3.h"
#include "mediator.h"
#include <sstream>

class Stage3GameStateFactory : public GameStateFactory {
  public:
    Stage3GameStateFactory() = default;
    ~Stage3GameStateFactory() override = default;
    virtual GameState* createGameState() override;
};

#endif // STAGE3GAMESTATEFACTORY_H
