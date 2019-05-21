#include "stage2game.h"

#include "entity.h"
#include "player.h"

Stage2Game::Stage2Game(GameState* state)
    : state(state) {}

Stage2Game::~Stage2Game()
{
    delete state;
}

void Stage2Game::render(QPainter &painter) {

    if (state->getBackground() != nullptr) {
        state->getBackground()->render(painter, paused || state->getPlayerColliding());
    }

    if (state->getPlayer() != nullptr) {
        state->getPlayer()->render(painter);
    }

    // Render all entities stored in the game state
    state->getRootEntity()->render(painter);
}

void Stage2Game::keyPressEvent(QKeyEvent *event) {
    // Call key press event for parent class
    Stage1Game::keyPressEvent(event);

    if (event->type()==QEvent::KeyPress) {
        if (event->key() == Qt::Key_Space) {
            // Make stickman jump
            state->getPlayer()->jump();
        }
    }
}

void Stage2Game::paintEvent(QPaintEvent* /*event*/) {
    // Update game
    state->update(paused);

    // Render game
    QPainter painter(this);
    render(painter);
}
