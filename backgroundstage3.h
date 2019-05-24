#ifndef BACKGROUNDSTAGE3_H
#define BACKGROUNDSTAGE3_H

#include "background.h"
#include "config.h"

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
