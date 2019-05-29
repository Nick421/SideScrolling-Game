#ifndef STAGE3GAME_H
#define STAGE3GAME_H

#include "stage2game.h"
#include "mediator.h"
#include "scoreboarddialog.h"

static std::vector<Qt::Key> konami_sequence;

class Stage3Game : public Stage2Game {
  public:
    Stage3Game(GameState* state);
    ~Stage3Game() override;

    void render(QPainter& painter) override;

  protected:
    void paintEvent(QPaintEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void konamiSequenceMaker();
    bool konamiSequenceChecker(QKeyEvent* event);
  private:
    unsigned long currentCode;

};

#endif // STAGE3GAME_H
