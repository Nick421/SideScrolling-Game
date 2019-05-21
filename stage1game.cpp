#include "stage1game.h"

#include <QTimer>
#include <QPainter>

#include "config.h"
#include "coordinate.h"
#include "pausedialog.h"
#include "startdialog.h"

Stage1Game::Stage1Game(QWidget *parent) :
    GameDialog(parent),
    background(Background(Coordinate(0, this->height(), this->height(), this->width()))),
    stickman_frame(1),
    counter(0) {


    this->setFixedSize(Config::config()->getWorldWidth(), Config::config()->getWorldHeight());

    if (Config::config()->getBackgroundNumber() == 2) {
        this->setStyleSheet("background-color: #002855;"); //Dark Blue
    } else {
        this->setStyleSheet("background-color: #14ACF6;"); //Light Blue
    }

    //Initially have pause as false;
    paused = false;

    //Timer is used to have a continous loop
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    timer->start(32);

}

Stage1Game::~Stage1Game() {
    delete timer;
}

void Stage1Game::paintEvent(QPaintEvent* /*event*/) {

    QPainter painter(this);

    background.render(painter, paused);

    //Once the frame is the last, reset
    if (stickman_frame > 9) {
        stickman_frame = 1;
    }

    //Get the Pixmap of the respective frame
    QPixmap stickman = Config::config()->getStickman()->getPixmap(stickman_frame);

    //Used to slow down the animation
    if (counter == 2) {
        stickman_frame++;
        counter = 0;
    }

    //Only increment the counter if its not paused
    if (!paused) {
        counter++;
    }

    Coordinate stickman_coordinate(Config::config()->getStickman()->getXPosition() - (Config::config()->getStickman()->getWidth()*0.5),
                                   0 + Config::config()->getStickman()->getHeight(),
                                   this->height(),
                                   this->width());

    //Draw the stickman to the screen
    painter.drawPixmap(stickman_coordinate.getQtRenderingXCoordinate(),
                       stickman_coordinate.getQtRenderingYCoordinate(),
                       Config::config()->getStickman()->getWidth(),
                       Config::config()->getStickman()->getHeight(),
                       stickman);

}

void Stage1Game::keyPressEvent(QKeyEvent *event) {

    //See if a key on the keyboard has been pressed
    if (event->type()==QEvent::KeyPress) {

        QKeyEvent* key = static_cast<QKeyEvent*>(event);

        if ( (key->key()==Qt::Key_P) ) { //P was pressed

            /*
             * Pause the screen
             * Show the pause dialog
            */

            pause();

            PauseDialog pause_dialog(&this->paused);
            pause_dialog.setModal(true);
            pause_dialog.setWindowTitle("Pause Screen");
            pause_dialog.exec();

        }

        if ( (key->key()==Qt::Key_Q) ) { //Q was pressed

            /*
             * Close the game dialog
             * Show the main menu dialog
            */

            close();

        }

    }

}

