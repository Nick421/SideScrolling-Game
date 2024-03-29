#include "extendedconfig.h"

#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

#include <iostream>
#include <utility>

using namespace std;

// stage 3

// combine section and key to use for map key
string search_key(const string& section, const string& key) {
    return section + "." + key;
}

// return the value from the map
string get(string section, string key, map <string, string> obstacles_infos) {
    auto it = obstacles_infos.find(search_key(section, key));
    if (it != obstacles_infos.end()) {
        return it->second;
    }
    return "";
}

// initialised all objects(except obstacle) into the vector so factory can create them
void ExtendedConfig::setUpPowerUps(const map<string, string>& map) {
    bool parse_check = false;
    int num_object = 0;

    while (true) {
        num_object++;
        char str[20];
        sprintf(str, "Powerup%d", num_object);
        std::string check = get(str, "type", map);

        // check if we read all of them or things don't exist in the map
        if (check == "") {
            qDebug() << "READ ALL OF THE POWERSUPS IN THE CONFIG FILES\n";
            break;
        }

        // parse all parameters
        int start_x = QString(get(str, "x", map).c_str()).toInt(&parse_check);
        if (!parse_check && start_x < 0) {
            start_x = 0;
        }

        int start_y = QString(get(str, "y", map).c_str()).toInt(&parse_check);
        if (!parse_check && start_y < 0) {
            start_y = 0;
        }

        int height = QString(get(str, "height", map).c_str()).toInt(&parse_check);
        if (!parse_check || height < 1) {
            height = 100;
        }

        int width = QString(get(str, "width", map).c_str()).toInt(&parse_check);
        if (!parse_check || width < 1) {
            width = 100;
        }

        int level = QString(get(str, "level", map).c_str()).toInt(&parse_check);
        if (!parse_check || level == 0) {
            level = 1;
        }

        string type = get(str, "type", map);

        // sanity check if type is specified or not
        if (type != "") {

            // load all value into struct
            auto* p_config = new PowerUpsConfig();
            p_config->width = width;
            p_config->height = height;
            p_config->offset_x = start_x;
            p_config->position_y = start_y;
            p_config->type = type;
            p_config->level = level;

            // Check that it doesnt overlap with other obstacles.
            bool overlap = false;
            double x_pos = 0;
            std::vector<ObstacleConfig*>::iterator it;
            for (it = obstacle_data.begin(); it != obstacle_data.end(); ++it) {
                x_pos += (*it)->offset_x;
            }

            double cumulative_x_pos = 0;
            for (it = obstacle_data.begin(); it != obstacle_data.end(); ++it) {
                cumulative_x_pos += (*it)->offset_x;
                double old_min_x = cumulative_x_pos - (*it)->width / 2.0;
                double old_max_x = cumulative_x_pos + (*it)->width / 2.0;
                double old_min_y = (*it)->position_y - (*it)->height / 2.0;
                double old_max_y = (*it)->position_y + (*it)->height / 2.0;
                double new_min_x = x_pos + start_x - width / 2.0;
                double new_max_x = x_pos + start_x + width / 2.0;
                double new_min_y = start_y - width / 2.0;
                double new_max_y = start_y + width / 2.0;
                if (!(old_min_x > new_max_x || old_max_x < new_min_x) && !(old_min_y > new_max_y || old_max_y < new_min_y)) {
                    if ((*it)->level == p_config->level) {
                        qDebug() << "Powerups overlap with an obstacle";
                        overlap = true;
                        break;
                    }
                }
            }
            if (overlap) {
                continue;
            }
            other_objects_data.push_back(p_config);

        } else {
            qDebug() << "SHAPE NOT SPECIFIED FOR " << str << " THIS OBSTACLE WILL BE IGNORED\n";
        }
    }

}

std::vector<PowerUpsConfig*> ExtendedConfig::getOtherObjectsData() {
    return other_objects_data;
}

int ExtendedConfig::getLives() {
    return m_lives;
}

int ExtendedConfig::getLevels() {
    return m_levels;
}

ExtendedConfig::ExtendedConfig(Config& config)
    : config(config),
      obstacle_data(std::vector<ObstacleConfig*>()),
      other_objects_data(vector<PowerUpsConfig*>()) {
    setupConfig();
}

ExtendedConfig::~ExtendedConfig() {
    for (auto* obs : obstacle_data) {
        delete obs;
    }
}

unsigned int ExtendedConfig::getWorldWidth() {
    return config.getWorldWidth();
}

unsigned int ExtendedConfig::getWorldHeight() {
    return config.getWorldHeight();
}

std::vector<ObstacleConfig*> ExtendedConfig::getObstacleData() {
    return obstacle_data;
}

void ExtendedConfig::setupConfig() {
    //stage 3
    map <string, string> additionalObjects_info;
    string current_section;
    bool in_section = false;

    QFile config_file(":config/config.txt");

    //Open the config file
    if (config_file.open(QIODevice::ReadOnly)) {

        QTextStream buffer(&config_file);

        while (!buffer.atEnd()) {

            QString line = buffer.readLine();

            QStringList split_line = line.split(":", QString::SkipEmptyParts);

            QString element = split_line.at(1);

            if (split_line.first() == "Size" || split_line.first() == "Position" || split_line.first() == "Velocity" || split_line.first() == "Background") {
                // Already handled by original config file, ignore.
                continue;

            } else if (split_line.first() == "Obstacles") {
                // Element should have format: 50,50,400,0,255,0,0|50,50,400,0,255,0,0 ...
                QStringList obstacles = element.split("|", QString::SkipEmptyParts);
                for (int i = 0; i < obstacles.size(); i++) {
                    ObstacleConfig* obstacle_config = new ObstacleConfig();
                    QStringList obstacle_fields = obstacles.at(i).split(",", QString::SkipEmptyParts);
                    // minor change for stage 3
                    if (obstacle_fields.size() < 7 ) {
                        std::cerr << "Invalid obstacle data at index " << i << std::endl;
                        continue;
                    } else {
                        try {

                            double width = obstacle_fields.at(0).toDouble();
                            double height = obstacle_fields.at(1).toDouble();
                            double offset = obstacle_fields.at(2).toDouble();
                            double y_pos = obstacle_fields.at(3).toDouble();
                            int r = obstacle_fields.at(4).toInt();
                            int g = obstacle_fields.at(5).toInt();
                            int b = obstacle_fields.at(6).toInt();

                            if (width <= 0 || height <= 0 || offset < 0 || y_pos < 0 || r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) {
                                std::cerr << "Invalid obstacle data at index " << i << std::endl;
                            } else {

                                // Check that it doesnt overlap with other obstacles.
                                bool overlap = false;
                                double x_pos = 0;
                                std::vector<ObstacleConfig*>::iterator it;
                                for (it = obstacle_data.begin(); it != obstacle_data.end(); ++it) {
                                    x_pos += (*it)->offset_x;
                                }

                                double cumulative_x_pos = 0;
                                for (it = obstacle_data.begin(); it != obstacle_data.end(); ++it) {
                                    cumulative_x_pos += (*it)->offset_x;
                                    double old_min_x = cumulative_x_pos - (*it)->width / 2.0;
                                    double old_max_x = cumulative_x_pos + (*it)->width / 2.0;
                                    double old_min_y = (*it)->position_y - (*it)->height / 2.0;
                                    double old_max_y = (*it)->position_y + (*it)->height / 2.0;
                                    double new_min_x = x_pos + offset - width / 2.0;
                                    double new_max_x = x_pos + offset + width / 2.0;
                                    double new_min_y = y_pos - width / 2.0;
                                    double new_max_y = y_pos + width / 2.0;
                                    if (!(old_min_x > new_max_x || old_max_x < new_min_x) && !(old_min_y > new_max_y || old_max_y < new_min_y)) {
                                        std::cerr << "Invalid obstacle data at index " << i << " due to overlap" << std::endl;
                                        overlap = true;
                                        break;
                                    }
                                }

                                if (overlap) {
                                    continue;
                                }

                                obstacle_config->width = width;
                                obstacle_config->height = height;
                                obstacle_config->offset_x = offset;
                                obstacle_config->position_y = y_pos;
                                obstacle_config->colour_red = r;
                                obstacle_config->colour_green = g;
                                obstacle_config->colour_blue = b;

                                // stage 3
                                if (obstacle_fields.size() == 8) {
                                    int level = obstacle_fields.at(7).toInt();
                                    obstacle_config->level = level;
                                }

                                obstacle_data.push_back(obstacle_config);
                            }
                        } catch (const std::exception& /*e*/) {
                            std::cerr << "Invalid obstacle data at index " << i << std::endl;
                            continue;
                        }
                    }
                }
                // stage 3
                // if the line starts a Powerup, checkpoint config
            } else if (split_line.first().startsWith("<")) {
                // check if the section is correct
                if (split_line[0].at(split_line[0].length() - 1) == '>') {

                    // set current section name by taking string between <>
                    current_section = current_section = split_line[0].toStdString().substr(1, split_line[0].size() - 2);
                    in_section = true;
                }
                // if in section and line doesn't start with <
            } else if (in_section && split_line[0].at(0) != '<') {
                string key = split_line.at(0).toStdString();
                string value = split_line.at(1).toStdString();

                // put key value into the map
                // example key.value = value
                additionalObjects_info[current_section + "." + key] = value;
                // number of lives specified in config
            } else if (split_line.first() == "Lives") {
                m_lives = element.toInt();
                if (m_lives <= 0) {
                    m_lives = 1;
                }
                // number of levels specified in config
            } else if (split_line.first() == "Levels") {
                m_levels = element.toInt();
                if (m_levels <= 0) {
                    m_levels = 1;
                }
            }

        }

        config_file.close();
        // stage 3
        // load all power ups
        setUpPowerUps(additionalObjects_info);
    } else {
        std::cerr << "Config file not found" << std::endl;
    }
}
