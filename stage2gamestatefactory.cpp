#include "stage2gamestatefactory.h"
#include "stage2game.h"
#include "stickmanplayer.h"
#include "obstacle.h"
#include "gamestate.h"
#include "extendedconfig.h"
#include "emptyentity.h"
#include "powerup.h"
#include <vector>
#include <sstream>

GameState* Stage2GameStateFactory::createGameState() {
    GameState* state = new GameState();

    unsigned int world_height = Config::config()->getWorldHeight();
    unsigned int world_width = Config::config()->getWorldWidth();

    // Create background and player
    BackgroundStage3* background = new BackgroundStage3(Coordinate(0, world_height, world_height, world_width));
    StickmanPlayer* player = new StickmanPlayer(new Coordinate(Config::config()->getStickman()->getXPosition() - (Config::config()->getStickman()->getWidth() * 0.5),
                                                               0 + Config::config()->getStickman()->getHeight(),
                                                               world_height,
                                                               world_width),
                                                "stickman");
    Coordinate* pos = new Coordinate(0, 0, world_height, world_width);
    EmptyEntity* root = new EmptyEntity(pos, "root");

    ExtendedConfig config(*Config::config());
    // Load obstacle data from file
    std::vector<ObstacleConfig*> obstacle_data = config.getObstacleData();

    // Calculate when to loop the obstacles
    double loop = world_width;
    for (auto* obstacleConfig : obstacle_data) {
        loop += obstacleConfig->offset_x;
    }

    // Create obstacles
    double previous_x = world_width;
    int count = 0;
    for (auto* obstacleConfig : obstacle_data) {
        previous_x = previous_x + obstacleConfig->offset_x;
        std::stringstream name;
        name << "obstacle_" << count;
        Coordinate* obs_pos = new Coordinate(previous_x, obstacleConfig->position_y, world_height, world_width);
        Obstacle* obs = new Obstacle(obs_pos, obstacleConfig->width, obstacleConfig->height,
                                     -Config::config()->getStickman()->getVelocity(), loop,
                                     QColor(obstacleConfig->colour_red, obstacleConfig->colour_green, obstacleConfig->colour_blue), name.str());
        root->addChild(obs);
        count++;
    }

    // Create entity tree
    state->setRootEntity(root);
    state->setBackground(background);
    state->setPlayer(player);

    return state;
}
