#include "stage3game.h"

Stage3Game::Stage3Game(GameState* state):
    Stage2Game (state) {

}

Stage3Game::~Stage3Game() {

}

void Stage3Game::render(QPainter& painter) {

    if (state->getBackground() != nullptr) {
        state->getBackground()->render(painter, paused || state->getPlayerColliding());
    }

    if (state->getPlayer() != nullptr) {
        state->getPlayer()->render(painter);
    }

    // Render the current stage
    state->getRootEntity()->render(painter);

    char text[40];
    sprintf(text, "Score: %d, Lives: %d", dynamic_cast<Mediator*>(state)->getScore(), state->getPlayer()->get_lives());
    painter.drawText(5, 20, text);

    // need to change this
    // maybe an end dialog like start?
    if (dynamic_cast<Mediator*>(state)->isFinished()) {
        pause();
        QFont font = QFont("Helvetica");
        font.setPointSize(font.pointSize() * 4);
        painter.setFont(font);


        QRectF windowRect(0, 0, painter.device()->width(), painter.device()->height());
        painter.fillRect(windowRect, QBrush(QColor(0, 0, 0, 128)));
        char finalscore[20];
        std::string finaltext;

        if (dynamic_cast<Mediator*>(state)->didWon()) {
            finaltext = "Game complete!";
        } else {
            finaltext = "Game over";
        }

        sprintf(finalscore, "Final score: %d", dynamic_cast<Mediator*>(state)->getScore());
        painter.drawText(250, 100, finaltext.c_str());
        painter.drawText(200, 200, finalscore);
    }
}

void Stage3Game::paintEvent(QPaintEvent* event) {
    // Update game
    state->update(paused);

    // Render game
    QPainter painter(this);
    render(painter);
}

void Stage3Game::keyPressEvent(QKeyEvent* event) {
    Stage2Game::keyPressEvent(event);

    if (event->key() == Qt::Key_Right) {
        Config::config()->getStickman()->changeVelocity(20);
        Config::config()->getStickman()->updateStickman();
    } else if (event->key() == Qt::Key_Left) {
        Config::config()->getStickman()->changeVelocity(-20);
        Config::config()->getStickman()->updateStickman();
    }
}

void Stage3Game::keyReleaseEvent(QKeyEvent* event) {
    Config::config()->getStickman()->changeVelocity(0);
    Config::config()->getStickman()->updateStickman();
}
