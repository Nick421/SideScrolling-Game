#include "stage3gamefactory.h"

// create stage3game
GameDialog* Stage3GameFactory::createGame() {
    auto* factory = new Stage3GameStateFactory();
    GameState* state = factory->createGameState();
    return new Stage3Game(state);
}
