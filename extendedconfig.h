#pragma once

#include <vector>

#include "config.h"
#include "configuration.h"

// stage 3
struct PowerUpsConfig {
    double width;
    double height;
    double offset_x;
    double position_y;
    QImage image;
    std::string type;
};

class ExtendedConfig : public Configuration {
  public:
    ExtendedConfig(Config& config);
    ~ExtendedConfig() override;

    virtual unsigned int getWorldWidth() override;
    virtual unsigned int getWorldHeight() override;
    virtual std::vector<ObstacleConfig*> getObstacleData() override;

    //stage 3
    void setUpPowerUps(std::map<std::string, std::string> map);
    std::vector<PowerUpsConfig*> getOtherObjectsData();

  protected:
    virtual void setupConfig() override;

  private:
    Config& config;
    std::vector<ObstacleConfig*> obstacle_data;
    // stage 3
    std::vector<PowerUpsConfig*> other_objects_data;
};

