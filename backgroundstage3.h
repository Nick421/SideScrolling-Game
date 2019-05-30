#ifndef BACKGROUNDSTAGE3_H
#define BACKGROUNDSTAGE3_H

#include "background.h"
#include "config.h"

/*********************************************
 *  Design Pattern: Mediator                 *
 *  Concrete Colleague                       *
 *********************************************/

// this class is simply subclass of Background
// minor fix with how the background tiled to makesure it tiled to the left also
class BackgroundStage3 : Background {
  public:
    BackgroundStage3(Coordinate main_coordinate);
    ~BackgroundStage3() override;

    void render(QPainter& painter, bool paused) override;
  private:
    Coordinate first_coordinate;
    Coordinate second_coordinate;
    Coordinate third_coordinate;

};

#endif // BACKGROUNDSTAGE3_H
