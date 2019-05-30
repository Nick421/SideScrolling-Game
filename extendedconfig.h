#pragma once

#include <vector>

#include "config.h"
#include "configuration.h"

// stage 3
// Powerup config struct to store all its parameter
struct PowerUpsConfig {
    double width;
    double height;
    double offset_x;
    double position_y;
    QImage image;
    std::string type;
    int level;
};

class ExtendedConfig : public Configuration {
  public:
    ExtendedConfig(Config& config);
    ~ExtendedConfig() override;

    virtual unsigned int getWorldWidth() override;
    virtual unsigned int getWorldHeight() override;
    virtual std::vector<ObstacleConfig*> getObstacleData() override;

    //stage 3
    // this initalised all objects in other_objects_data
    void setUpPowerUps(const std::map<std::string, std::string>& map);
    // getter to return the other_objects_data
    std::vector<PowerUpsConfig*> getOtherObjectsData();
    // getter for number of lives and number of levels
    int getLives();
    int getLevels();

  protected:
    virtual void setupConfig() override;

  private:
    Config& config;
    std::vector<ObstacleConfig*> obstacle_data;
    // stage 3
    // vector which stored PowerUpsConfig structs for each objects
    std::vector<PowerUpsConfig*> other_objects_data;
    int m_lives{};
    int m_levels{};
};

