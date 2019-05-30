#ifndef STAGE3GAME_H
#define STAGE3GAME_H

#include "stage2game.h"
#include "mediator.h"
#include "scoreboarddialog.h"

/*********************************************
 *  Design Pattern: Mediator                 *
 *  Concrete Colleague                       *
 *********************************************/

// vector to store the konami code
static std::vector<Qt::Key> konami_sequence;

// this class is subclass of stage 2 to override some methods
class Stage3Game : public Stage2Game {
  public:
    Stage3Game(GameState* state);
    ~Stage3Game() override;

    void render(QPainter& painter) override;

  protected:
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void konamiSequenceMaker();
    bool konamiSequenceChecker(QKeyEvent* event);
  private:
    // store the current index of konami code
    unsigned long currentCode;

};

#endif // STAGE3GAME_H
