#include "stage2gamefactory.h"

#include "stage2game.h"
#include "stage2gamestatefactory.h"

GameDialog* Stage2GameFactory::createGame() {
    Stage2GameStateFactory* factory = new Stage2GameStateFactory();
    GameState* state = factory->createGameState();
    return new Stage2Game(state);
}
