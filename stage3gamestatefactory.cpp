#include "stage3gamestatefactory.h"

GameState* Stage3GameStateFactory::createGameState() {

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
    Coordinate* pos = new Coordinate(0, 0, world_height, world_width);

    ExtendedConfig config(*Config::config());

    // allocate memory for levels
    EmptyEntity** root = new EmptyEntity*[config.getLevels()];

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
            Coordinate* obs_pos = new Coordinate(previous_x, obstacleConfig->position_y, world_height, world_width);
            Obstacle* obs = new Obstacle(obs_pos, obstacleConfig->width, obstacleConfig->height,
                                         -Config::config()->getStickman()->getVelocity(), loop,
                                         QColor(obstacleConfig->colour_red, obstacleConfig->colour_green, obstacleConfig->colour_blue), name.str());
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
            if (PowerUpsConfig->type.compare("Tiny") == 0) {
                image.load(":/img/misc/tiny.png");
            } else if (PowerUpsConfig->type.compare("Normal") == 0) {
                image.load(":/img/misc/normal.png");
            } else if (PowerUpsConfig->type.compare("Large") == 0) {
                image.load(":/img/misc/large.png");
            } else if (PowerUpsConfig->type.compare("Giant") == 0) {
                image.load(":/img/misc/giant.png");
            } else if (PowerUpsConfig->type.compare("Checkpoint") == 0) {
                image.load(":/img/misc/checkpoint.png");
            } else if (PowerUpsConfig->type.compare("Speedup") == 0) {
                image.load(":/img/misc/speedup.png");
            } else if (PowerUpsConfig->type.compare("Heart") == 0) {
                image.load(":/img/misc/heart.png");
            }
            Coordinate* obs_pos = new Coordinate(previous_x, PowerUpsConfig->position_y, world_height, world_width);
            PowerUp* obs = new PowerUp(obs_pos, image.width(), image.height(),
                                       -Config::config()->getStickman()->getVelocity(), loop,
                                       name.str(), PowerUpsConfig->type, image);
            if (PowerUpsConfig->level == i + 1) {
                root[i]->addChild(obs);
            }
            count++;
        }
    }

    player->set_lives(config.getLives());
    dynamic_cast<Mediator*>(state)->setNumLevels(config.getLevels());

    // Create entity tree
    state->setLevels(reinterpret_cast<Entity**>(root));
    state->setBackground(background);
    state->setPlayer(player);


    Config::config()->getStickman()->changeVelocity(0);
    Config::config()->getStickman()->changeSize(Config::config()->getInitialSize());
    Config::config()->setVelocity(Config::config()->getInitialVelocity());


    return state;
}
