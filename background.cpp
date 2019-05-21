#include "background.h"

#include "config.h"

Background::Background(Coordinate main_coordinate)
    : main_coordinate(main_coordinate),
      first_coordinate(main_coordinate),
      second_coordinate(main_coordinate),
      third_coordinate(main_coordinate) {

    //Load the respective background components into variables
    this->first.load(":img/background" + QString::number(Config::config()->getBackgroundNumber()) + "/first.png");
    this->second.load(":img/background" + QString::number(Config::config()->getBackgroundNumber()) + "/second.png");
    this->third.load(":img/background" + QString::number(Config::config()->getBackgroundNumber()) + "/third.png");

    //Scale the images to suit the size of the game screen
    this->first = this->first.scaled(Config::config()->getWorldWidth(),
                                     Config::config()->getWorldHeight(),
                                     Qt::AspectRatioMode());

    this->second = this->second.scaled(Config::config()->getWorldWidth(),
                                       Config::config()->getWorldHeight(),
                                       Qt::AspectRatioMode());

    this->third = this->third.scaled(Config::config()->getWorldWidth(),
                                     Config::config()->getWorldHeight(),
                                     Qt::AspectRatioMode());
}


/*
 * Renders the background, the background has a parallax effect so there is
 * 3 different components that move along the x-axis
*/
void Background::render(QPainter &painter, bool paused) {

    /*
     * Create three new coordinates to represent a wrap around.
     * All three continously created and are rendered to be at the end of the
     * original coordinate of the respective component
    */
    Coordinate first_coordinate_wrap(first_coordinate.getXCoordinate() + (100 + Config::config()->getWorldWidth()),
                                 first_coordinate.getYCoordinate(),
                                 first_coordinate.getFrameHeight(),
                                 first_coordinate.getFrameWidth());


    // A gap is created to ensure the 2nd component doesn't show instantly once it moves off the screen
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

    /*The following if statements are used to set the components at the original position once
    * they have moved completely off the screen
    */
    if (first_coordinate.getQtRenderingXCoordinate() < 0 - getFirst().width()) {
        first_coordinate.setXCoordinateToZero(100);
    }

    //When the background is the second set, it needs to be negative becuase it moves the opposite direction
    if (Config::config()->getBackgroundNumber() == 2) {
        if (second_coordinate.getQtRenderingXCoordinate() > Config::config()->getWorldWidth()) {
            second_coordinate.setXCoordinateToZero(-100);
        }
    } else {
        if (second_coordinate.getQtRenderingXCoordinate() < 0 - getSecond().width()) {
            second_coordinate.setXCoordinateToZero(0);
        }
    }

    if (third_coordinate.getQtRenderingXCoordinate() < 0 - getThird().width()) {
        third_coordinate.setXCoordinateToZero(0);
    }

    //Draw all the respective components onto the screen
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

    painter.drawPixmap(third_coordinate.getQtRenderingXCoordinate(),
        third_coordinate.getQtRenderingYCoordinate(),
        getThird());

    painter.drawPixmap(third_coordinate_wrap.getQtRenderingXCoordinate(),
        third_coordinate_wrap.getQtRenderingYCoordinate(),
        getThird());


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
