#pragma once

#include <iostream>
#include <string>
#include <QPixmap>

class Stickman {

public:

    Stickman(std::string size = "small",
            int position = 0,
            double starting_velocity = 0.0);

    virtual ~Stickman();

    //Getter functions
    std::string getSize() { return size; }
    int getXPosition() { return position; }
    double getVelocity() { return velocity; }
    double getWidth() { return width; }
    double getHeight() { return height; }
    virtual QPixmap getPixmap(unsigned int frame);

    //Change and set functions
    void changeSize(std::string new_size) { size = new_size; }
    void changeXPosition(int new_position) { position = new_position; }
    void changeVelocity(int new_velocity) { velocity = new_velocity; }
    virtual void setDimensions();
    virtual void updateStickman();


private:

    std::string size;
    int position;
    double velocity;
    int width;
    int height;

};

