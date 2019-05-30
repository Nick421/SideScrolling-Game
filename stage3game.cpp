#include "stage3game.h"

Stage3Game::Stage3Game(GameState* state):
    Stage2Game (state),
    currentCode(0) {
    // initialise the konami codes
    konamiSequenceMaker();
}

Stage3Game::~Stage3Game() = default;

void Stage3Game::render(QPainter& painter) {

    if (state->getBackground() != nullptr) {
        state->getBackground()->render(painter, paused || state->getPlayerColliding());
    }

    if (state->getPlayer() != nullptr) {
        state->getPlayer()->render(painter);
    }

    // Render the current stage
    state->getRootEntity()->render(painter);

    // render the score, lives and current stage on screen
    char text[40];
    sprintf(text, "Score: %d, Lives: %d, Stage: %d", dynamic_cast<Mediator*>(state)->getScore(),
            state->getPlayer()->getLives(), state->getPlayer()->getCurrentLevel());
    QFont font = QFont("Helvetica");
    font.setPointSize(font.pointSize() * 2);
    painter.setFont(font);
    painter.drawText(5, 20, text);

    // if the game has ended, render end screen
    if (dynamic_cast<Mediator*>(state)->isFinished()) {
        pause();
        QFont font = QFont("Helvetica [Cronyx]");
        font.setPointSize(font.pointSize() * 4);
        painter.setFont(font);

        // apply dark filter over the screen
        QRectF windowRect(0, 0, painter.device()->width(), painter.device()->height());
        painter.fillRect(windowRect, QBrush(QColor(0, 0, 0, 128)));

        char finalscore[20];
        std::string finaltext;

        // if the game was won or the player died
        if (dynamic_cast<Mediator*>(state)->didWon()) {
            finaltext = "Game complete!";
        } else {
            finaltext = "Game over";
        }

        // print out final score
        sprintf(finalscore, "Final score: %d", dynamic_cast<Mediator*>(state)->getScore());
        painter.drawText(250, 100, finaltext.c_str());
        painter.drawText(200, 200, finalscore);
        painter.drawText(300, 300, "PRESS ENTER");
    }
}

// override the key press event to add in stage 3 functions
void Stage3Game::keyPressEvent(QKeyEvent* event) {
    // call stage 2 to handle its keys (etc jump) this also call stage 1
    Stage2Game::keyPressEvent(event);

    // handle moving left and right
    if (event->key() == Qt::Key_Right) {
        Config::config()->getStickman()->changeVelocity(Config::config()->getVelocity());
        Config::config()->getStickman()->updateStickman();
    } else if (event->key() == Qt::Key_Left) {
        Config::config()->getStickman()->changeVelocity(-Config::config()->getVelocity());
        Config::config()->getStickman()->updateStickman();
    }
    // check for konami sequence
    if (konamiSequenceChecker(event)) {
        dynamic_cast<Mediator*>(state)->konamiCode();
    }

    // check if game has ended, then they can press enter to go to scoreboard
    if (dynamic_cast<Mediator*>(state)->isFinished() && event->key() == Qt::Key_Return) {
        // close the game and displaye scoreboard
        close();
        ScoreboardDialog::scoreboard()->setScore(dynamic_cast<Mediator*>(state)->getScore());
        ScoreboardDialog::scoreboard()->show();

    }
}

// if key is not pressed the stickman stays still
void Stage3Game::keyReleaseEvent(QKeyEvent* /*event*/) {
    Config::config()->getStickman()->changeVelocity(0);
    Config::config()->getStickman()->updateStickman();
}

// initialise all konami codes
void Stage3Game::konamiSequenceMaker() {
    konami_sequence.push_back(Qt::Key_Up);
    konami_sequence.push_back(Qt::Key_Up);
    konami_sequence.push_back(Qt::Key_Down);
    konami_sequence.push_back(Qt::Key_Down);
    konami_sequence.push_back(Qt::Key_Left);
    konami_sequence.push_back(Qt::Key_Right);
    konami_sequence.push_back(Qt::Key_Left);
    konami_sequence.push_back(Qt::Key_Right);
    konami_sequence.push_back(Qt::Key_B);
    konami_sequence.push_back(Qt::Key_A);
}

// check if the input match konami code
bool Stage3Game::konamiSequenceChecker(QKeyEvent* event) {
    // if correct, move to next index
    // else restart
    if (event->key() == konami_sequence.at(currentCode)) {
        currentCode++;
    } else {
        currentCode = 0;
    }
    // if we reach the end of the code, successful
    if (currentCode == konami_sequence.size()) {
        currentCode = 0;
        return true;
    }
    return false;
}
