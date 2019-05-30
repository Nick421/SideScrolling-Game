#include "stage3gamestatefactory.h"

GameState* Stage3GameStateFactory::createGameState() {

    // instead of GameState we make a mediator instead
    GameState* state = new Mediator();

    unsigned int world_height = Config::config()->getWorldHeight();
    unsigned int world_width = Config::config()->getWorldWidth();

    // Create background and player
    BackgroundStage3* background = new BackgroundStage3(Coordinate(0, world_height, world_height, world_width));
    StickmanPlayer* player = new StickmanPlayer(new Coordinate(Config::config()->getStickman()->getXPosition() - (Config::config()->getStickman()->getWidth() * 0.5),
                                                               0 + Config::config()->getStickman()->getHeight(),
                                                               world_height,
                                                               world_width),
                                                "stickman");
    auto* pos = new Coordinate(0, 0, world_height, world_width);

    ExtendedConfig config(*Config::config());

    // allocate memory for levels
    auto** root = new EmptyEntity*[config.getLevels()];

    // Load obstacle data from file
    std::vector<ObstacleConfig*> obstacle_data = config.getObstacleData();

    // Calculate when to loop the obstacles
    double loop = world_width;
    for (auto* obstacleConfig : obstacle_data) {
        loop += obstacleConfig->offset_x;
    }

    // go through each level and add in objects
    for (int i = 0; i < config.getLevels(); ++i) {
        root[i] = new EmptyEntity(pos, "root");

        // Create obstacles
        double previous_x = world_width;
        int count = 0;
        for (auto* obstacleConfig : obstacle_data) {
            previous_x = previous_x + obstacleConfig->offset_x;
            std::stringstream name;
            name << "obstacle_" << count;
            auto* obs_pos = new Coordinate(previous_x, obstacleConfig->position_y, world_height, world_width);
            Obstacle* obs = new Obstacle(obs_pos, obstacleConfig->width, obstacleConfig->height,
                                         -Config::config()->getStickman()->getVelocity(), loop,
                                         QColor(obstacleConfig->colour_red, obstacleConfig->colour_green, obstacleConfig->colour_blue), name.str());
            // if it is in the current level add them
            if (obstacleConfig->level == i + 1) {
                root[i]->addChild(obs);
            }
            count++;
        }

        // Create powerups, checkpoints
        std::vector<PowerUpsConfig*> other_objects_data = config.getOtherObjectsData();
        count = 0;
        for (auto* PowerUpsConfig : other_objects_data) {
            previous_x = previous_x + PowerUpsConfig->offset_x;
            std::stringstream name;
            name << "powerups_" << count;
            QImage image;

            // check what type of objects they are and load the coressponding image
            if (PowerUpsConfig->type == "Tiny") {
                image.load(":/img/misc/tiny.png");
            } else if (PowerUpsConfig->type == "Normal") {
                image.load(":/img/misc/normal.png");
            } else if (PowerUpsConfig->type == "Large") {
                image.load(":/img/misc/large.png");
            } else if (PowerUpsConfig->type == "Giant") {
                image.load(":/img/misc/giant.png");
            } else if (PowerUpsConfig->type == "Checkpoint") {
                image.load(":/img/misc/checkpoint.png");
            } else if (PowerUpsConfig->type == "Speedup") {
                image.load(":/img/misc/speedup.png");
            } else if (PowerUpsConfig->type == "Heart") {
                image.load(":/img/misc/heart.png");
            }
            // create the powerups
            auto* obs_pos = new Coordinate(previous_x, PowerUpsConfig->position_y, world_height, world_width);
            PowerUp* obs = new PowerUp(obs_pos, image.width(), image.height(),
                                       -Config::config()->getStickman()->getVelocity(), loop,
                                       name.str(), PowerUpsConfig->type, image);
            // if it is in the current level add them
            if (PowerUpsConfig->level == i + 1) {
                root[i]->addChild(obs);
            }
            count++;
        }
    }

    // set lives and number of levels
    player->setLives(config.getLives());
    dynamic_cast<Mediator*>(state)->setNumLevels(config.getLevels());

    // Create entity tree
    state->setLevels(reinterpret_cast<Entity**>(root));
    state->setBackground(background);
    state->setPlayer(player);

    // set velocity to 0 when game start, set size to inital size
    // make sure the game reset each time it is play
    Config::config()->getStickman()->changeVelocity(0);
    Config::config()->getStickman()->changeSize(Config::config()->getInitialSize());
    Config::config()->setVelocity(Config::config()->getInitialVelocity());

    return state;
}
