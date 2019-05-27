#ifndef STAGE3GAME_H
#define STAGE3GAME_H

#include "stage2game.h"
#include "mediator.h"
#include "scoreboarddialog.h"

class Stage3Game : public Stage2Game {
  public:
    Stage3Game(GameState* state);
    ~Stage3Game() override;

    void render(QPainter& painter) override;

  protected:
    void paintEvent(QPaintEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

};

#endif // STAGE3GAME_H
