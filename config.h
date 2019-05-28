#pragma once

#include "stickman.h"

class Config {

  public:

    static Config* config() {

        static Config config_instance;

        return &config_instance;
    }

    virtual ~Config() = default;

    virtual void setupConfig();

    //Getter functions
    Stickman* getStickman() {
        return stickman;
    }
    unsigned int getWorldWidth() {
        return world_width;
    }
    unsigned int getWorldHeight() {
        return world_height;
    }
    int getBackgroundNumber() {
        return background_number;
    }

    //Setter functions
    void setWorldWidth(unsigned int width) {
        world_width = width;
    }
    void setWorldHeight(unsigned int height) {
        world_height = height;
    }
    void setBackgroundNumber(int number) {
        background_number = number;
    }
    void setStickman(Stickman* new_stickman) {
        stickman = new_stickman;
    }

    // stage 3
    void setInitialVelocity(int velocity) {
        m_initial_vel = velocity;
    }
    int getInitialVelocity() {
        return m_initial_vel;
    }
    void setVelocity(int velocity) {
        m_velocity = velocity;
    }
    int getVelocity() {
        return m_velocity;
    }
    void setInitialSize(std::string size) {
        m_initial_size = size;
    }
    std::string getInitialSize() {
        return m_initial_size;
    }

  private:

    // Private so that it can not be called
    Config() = default;

    unsigned int world_width = 0;
    unsigned int world_height = 0;
    int background_number = 0;
    Stickman* stickman = nullptr;

    // stage 3
    int m_initial_vel;
    int m_velocity;
    std::string m_initial_size;
};

