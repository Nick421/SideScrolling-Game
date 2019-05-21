#include "config.h"
#include "startdialog.h"
#include "stage2gamefactory.h"
#include "stage2gamestatefactory.h"
#include "tester.h"

#include <QApplication>
#include <QSound>

#include <iostream>
#include <memory>


//Allocating and initializing Config static data member. The pointer is being allocated - not the object itself
int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    //Sets up the config class for all files to use
    Config::config()->setupConfig();

    //Infinite loop of background music
    QSound sound(":sound/background_music.wav");
    sound.setLoops(-1);
    sound.play();

    // Create testing interface with a separate game state.
    auto state_factory = std::unique_ptr<GameStateFactory>(new Stage2GameStateFactory());
    Tester tester(state_factory);
    tester.run(2048);

    // Create rendered version of the game
    GameFactory* factory = new Stage2GameFactory();

    StartDialog start_dialog(factory);
    start_dialog.setWindowTitle("Main Menu");
    start_dialog.show();

    auto exit_code = a.exec();
    return exit_code;
}
