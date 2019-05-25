#include "stickmanplayer.h"

#include "coordinate.h"

StickmanPlayer::StickmanPlayer(Coordinate* position, std::string name)
    : Player(position, name),
      offset_position(new Coordinate(0, 0, position->getFrameHeight(), position->getFrameWidth())),
      physics_body(PhysicsBody(offset_position)),
      collider(RectCollider(new Coordinate(0, 0, position->getFrameHeight(), position->getFrameWidth()),
                            new Coordinate(0, 0, position->getFrameHeight(), position->getFrameWidth()))),
      jump_height(150),
      gravity(-9.8 * 200), // Assume 100 pixels = 1m
      jump_count(0),
      frame_number(1),
      counter(0),
      m_lives(0),
      m_current_level(1) {
    physics_body.setYAcceleration(gravity);
}

StickmanPlayer::~StickmanPlayer() {
    delete offset_position;
}

void StickmanPlayer::jump() {
    if (jump_count < max_jump_count) {
        jump_count += 1;
        physics_body.setYVelocity(std::sqrt(-2 * gravity * jump_height));
    }
}

void StickmanPlayer::landed() {
    jump_count = 0;
    physics_body.setYVelocity(0);
}

void StickmanPlayer::checkGroundCollision() {
    if (offset_position->getYCoordinate() <= 0) {
        offset_position->setYCoordinateToZero(0);
        landed();
    }
}

void StickmanPlayer::onCollision(Entity* other) {
    std::cout << other->getName() << std::endl;
}

void StickmanPlayer::update(bool paused, double time_since_last_frame) {
    // Physics updates
    physics_body.apply(time_since_last_frame / 1000.0);

    checkGroundCollision();

    // Keep position coordinate and collider coordinates in sync with the Config
    this->getPosition()->setXCoordinateToZero(Config::config()->getStickman()->getXPosition() - (Config::config()->getStickman()->getWidth() * 0.5) + offset_position->getXCoordinate());
    this->getPosition()->setYCoordinateToZero(Config::config()->getStickman()->getHeight() + offset_position->getYCoordinate());
    this->collider.getV1()->setXCoordinateToZero(this->getPosition()->getXCoordinate());
    this->collider.getV1()->setYCoordinateToZero(this->getPosition()->getYCoordinate());
    this->collider.getV2()->setXCoordinateToZero(this->getPosition()->getXCoordinate() + Config::config()->getStickman()->getWidth());
    this->collider.getV2()->setYCoordinateToZero(this->getPosition()->getYCoordinate() - Config::config()->getStickman()->getHeight());

    //Used to slow down the animation
    if (counter == 2) {
        frame_number++;
        counter = 0;
    }

    //Once the frame is the last, reset
    if (frame_number > 9) {
        frame_number = 1;
    }

    //Only increment the counter if its not paused
    if (!paused) {
        counter++;
    }
}

void StickmanPlayer::render(QPainter& painter) {
    QPixmap sprite = Config::config()->getStickman()->getPixmap(frame_number);
    painter.drawPixmap(this->getPosition()->getQtRenderingXCoordinate(),
                       this->getPosition()->getQtRenderingYCoordinate(),
                       Config::config()->getStickman()->getWidth(),
                       Config::config()->getStickman()->getHeight(),
                       sprite);
}

// stgae 3
void StickmanPlayer::set_gravity(double gravity) {
    this->gravity = gravity;
}

int StickmanPlayer::get_lives() {
    return m_lives;
}

void StickmanPlayer::set_lives(int lives) {
    this->m_lives = lives;
}

void StickmanPlayer::lose_life() {
    m_lives--;
}

int StickmanPlayer::getCurrentLevel() {
    return m_current_level;
}

void StickmanPlayer::setCurrentLevel(int level) {
    m_current_level = level;
}
