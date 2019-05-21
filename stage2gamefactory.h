#pragma once

#include "gamefactory.h"

class Stage2GameFactory : public GameFactory {

public:
    Stage2GameFactory() = default;
    ~Stage2GameFactory() override = default;

    GameDialog* createGame() override;

};

