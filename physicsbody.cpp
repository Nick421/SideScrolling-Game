#include "physicsbody.h"
#include "coordinate.h"

PhysicsBody::PhysicsBody(Coordinate* position)
    : position(position),
      a_x(0),
      a_y(0),
      v_x(0),
      v_y(0) {}

void PhysicsBody::apply(double timestep) {
    if (position != nullptr) {
        position->changeInXCoordinate(v_x*timestep + 0.5*a_x*timestep*timestep);
        position->changeInYCoordinate(v_y*timestep + 0.5*a_y*timestep*timestep);
        v_x += a_x*timestep;
        v_y += a_y*timestep;
    }
}
