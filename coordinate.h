#pragma once

class Coordinate {
  public:
    Coordinate(
        double x_coordinate,
        double y_coordinate,
        unsigned int frame_height,
        unsigned int frame_width);

    int getQtRenderingXCoordinate() {
        return x_coordinate;
    }

    int getQtRenderingYCoordinate() {
        return frame_height - y_coordinate;
    }

    double getXCoordinate() {
        return x_coordinate;
    }

    double getYCoordinate() {
        return y_coordinate;
    }

    void changeInXCoordinate(double change) {
        x_coordinate += change;
    }
    void changeInYCoordinate(double change) {
        y_coordinate += change;
    }

    void setYCoordinateToZero(int offset) {
        y_coordinate = 0 + offset;
    }

    void setXCoordinateToZero(int offset) {
        x_coordinate = 0 + offset;
    }

    unsigned int getFrameHeight() {
        return frame_height;
    }

    unsigned int getFrameWidth() {
        return frame_width;
    }

  private:
    double x_coordinate;
    double y_coordinate;
    unsigned int frame_height;
    unsigned int frame_width;
};

