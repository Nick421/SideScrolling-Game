#pragma once

class Coordinate;

class PhysicsBody {

public:
    PhysicsBody(Coordinate* position);
    void apply(double timestep);

    double getXAcceleration() {return a_x;}
    double getYAcceleration() {return a_y;}
    double getXVelocity() {return v_x;}
    double getYVelocity() {return v_y;}
    void setXAcceleration(double acceleration) {a_x = acceleration;}
    void setYAcceleration(double acceleration) {a_y = acceleration;}
    void setXVelocity(double velocity) {v_x = velocity;}
    void setYVelocity(double velocity) {v_y = velocity;}

protected:
    Coordinate* position;
    double a_x;
    double a_y;
    double v_x;
    double v_y;

};
