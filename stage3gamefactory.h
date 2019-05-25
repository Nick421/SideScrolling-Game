#ifndef STAGE3GAMEFACTORY_H
#define STAGE3GAMEFACTORY_H

#include "gamefactory.h"
#include "stage3game.h"
#include "stage3gamestatefactory.h"

class Stage3GameFactory : public GameFactory {
  public:
    Stage3GameFactory() = default;
    ~Stage3GameFactory() override = default;

    GameDialog* createGame() override;
};

#endif // STAGE3GAMEFACTORY_H
