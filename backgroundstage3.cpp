#include "backgroundstage3.h"

BackgroundStage3::BackgroundStage3(Coordinate main_coordinate):
    Background (main_coordinate),
    first_coordinate(main_coordinate),
    second_coordinate(main_coordinate),
    third_coordinate(main_coordinate) {

}

BackgroundStage3::~BackgroundStage3() = default;

void BackgroundStage3::render(QPainter& painter, bool paused) {
    Coordinate first_coordinate_wrap(first_coordinate.getXCoordinate() + (100 + Config::config()->getWorldWidth()),
                                     first_coordinate.getYCoordinate(),
                                     first_coordinate.getFrameHeight(),
                                     first_coordinate.getFrameWidth());

    int loading_gap = 0;
    if (Config::config()->getBackgroundNumber() == 2) {
        loading_gap = 100;
    }

    Coordinate second_coordinate_wrap(second_coordinate.getXCoordinate() + (loading_gap + Config::config()->getWorldWidth()),
                                      second_coordinate.getYCoordinate(),
                                      second_coordinate.getFrameHeight(),
                                      second_coordinate.getFrameWidth());

    Coordinate third_coordinate_wrap(third_coordinate.getXCoordinate() + Config::config()->getWorldWidth(),
                                     third_coordinate.getYCoordinate(),
                                     third_coordinate.getFrameHeight(),
                                     third_coordinate.getFrameWidth());

    if (first_coordinate.getQtRenderingXCoordinate() < 0 - getFirst().width()) {
        first_coordinate.setXCoordinateToZero(100);
    }

    if (Config::config()->getBackgroundNumber() == 2) {
        if (second_coordinate.getQtRenderingXCoordinate() > Config::config()->getWorldWidth()) {
            second_coordinate.setXCoordinateToZero(-100);
        }
    } else {
        if (second_coordinate.getQtRenderingXCoordinate() < 0 - getSecond().width()) {
            second_coordinate.setXCoordinateToZero(0);
        }
    }

    painter.drawPixmap(first_coordinate.getQtRenderingXCoordinate(),
                       first_coordinate.getQtRenderingYCoordinate(),
                       getFirst());

    painter.drawPixmap(first_coordinate_wrap.getQtRenderingXCoordinate(),
                       first_coordinate_wrap.getQtRenderingYCoordinate(),
                       getFirst());

    painter.drawPixmap(second_coordinate.getQtRenderingXCoordinate(),
                       second_coordinate.getQtRenderingYCoordinate(),
                       getSecond());

    painter.drawPixmap(second_coordinate_wrap.getQtRenderingXCoordinate(),
                       second_coordinate_wrap.getQtRenderingYCoordinate(),
                       getSecond());

    int width = getThird().width();
    int height = getThird().height();

    // Calculate the x coordinate to start tiling the image from.
    int start_x = int(third_coordinate_wrap.getQtRenderingXCoordinate()) % width - width;

    // Tile multiple copies of the image to fill the screen.
    for (int x = start_x; x < painter.device()->width(); x += width) {
        for (int y = 0; y < painter.device()->height(); y += height) {
            painter.drawPixmap(x, y, getThird());
        }
    }

    //If it isn't in pause, then adjust the position of all the components.
    if (!paused) {
        first_coordinate.changeInXCoordinate(-0.2);
        if (Config::config()->getBackgroundNumber() == 2) {
            second_coordinate.changeInXCoordinate(0.5);
        } else {
            second_coordinate.changeInXCoordinate(-0.3);
        }
        third_coordinate.changeInXCoordinate(-Config::config()->getStickman()->getVelocity());
    }

}
