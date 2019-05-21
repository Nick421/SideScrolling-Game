#pragma once

class GameState;

class GameStateFactory {
public:
    GameStateFactory();
    virtual ~GameStateFactory() = default;
    virtual GameState* createGameState() = 0;

};
