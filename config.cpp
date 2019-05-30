#include "config.h"

#include <QWidget>
#include <QDesktopWidget>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QList>

#include <iostream>
#include <string>

void Config::setupConfig() {

    //Set up the frame size of the game
    Config::config()->setWorldWidth(1000);
    Config::config()->setWorldHeight(600);

    std::string config_size = "normal";
    int config_position = 0;
    double config_velocity = 0.0;

    QFile config_file(":config/config.txt");

    //Open the config file
    if (config_file.open(QIODevice::ReadOnly)) {

        QTextStream buffer(&config_file);

        while (!buffer.atEnd()) {

            QString line = buffer.readLine();

            QStringList split_line = line.split(":", QString::SkipEmptyParts);

            QString element = split_line.at(1);

            if (split_line.first() == "Size") {

                if (element.toStdString() != "tiny" && element.toStdString() != "normal" &&
                        element.toStdString() != "large" && element.toStdString() != "giant") {
                    std::cerr << "Not a defined size in config file, please make it a valid size" << std::endl <<
                              "Valid sizes are: tiny, normal, large, giant" << std::endl;
                    return;
                }

                config_size = element.toStdString();
            }

            else if (split_line.first() == "Position") {

                if (element.toInt() < 0 || element.toInt() > getWorldWidth()) {
                    std::cerr << "Position is out of bounds. Please make it a valid position" << std::endl <<
                              "[0 <= position <= " << getWorldWidth() << "]" << std::endl;
                    return;
                }


                config_position = element.toInt();
            }

            else if (split_line.first() == "Velocity") {
                config_velocity = element.toDouble();
            }

            else if (split_line.first() == "Background") {

                if (element.toInt() < 1 || element.toInt() > 2) {
                    std::cerr << "Background does not exist. Please make it a valid background" << std::endl <<
                              "[1 <= background_number <= 2]" << std::endl;
                    return;
                }

                Config::config()->setBackgroundNumber(element.toInt());
            }

        }

        config_file.close();
    } else {
        std::cerr << "Config file not found" << std::endl;
    }

    //Create the stickman, given the parameters from the config file
    Config::config()->setStickman(new Stickman(config_size, config_position, config_velocity));

    // stage 3
    // initialised all new member variables
    Config::config()->setInitialVelocity(int(config_velocity));
    Config::config()->setVelocity(int(config_velocity));
    Config::config()->setInitialSize(config_size);
}

