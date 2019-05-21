#include "coordinate.h"

Coordinate::Coordinate(double x_coordinate,
           double y_coordinate,
           unsigned int frame_height,
           unsigned int frame_width)
    : x_coordinate(x_coordinate),
      y_coordinate(y_coordinate),
      frame_height(frame_height),
      frame_width(frame_width) {}
