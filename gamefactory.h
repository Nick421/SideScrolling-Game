#pragma once

#include "gamedialog.h"

class GameFactory {
public:
    virtual GameDialog* createGame() = 0;
    virtual ~GameFactory() = default;
};
