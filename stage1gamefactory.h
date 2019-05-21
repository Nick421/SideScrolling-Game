#pragma once

#include "gamefactory.h"
#include "stage1game.h"

class Stage1GameFactory : public GameFactory
{
public:
    Stage1GameFactory() = default;
    ~Stage1GameFactory() override = default;

    Stage1Game* createGame() override {
        return new Stage1Game();
    }
};
