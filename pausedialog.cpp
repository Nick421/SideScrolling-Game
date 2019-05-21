#include "pausedialog.h"
#include "ui_pausedialog.h"

PauseDialog::PauseDialog(bool *paused, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PauseDialog),
    paused(paused) {

    ui->setupUi(this);
    //this->setStyleSheet("background-color: #FFFFFF;"); //White
    this->setFixedSize(this->width(), this->height());
    setUpUI();

}

PauseDialog::~PauseDialog() {
    delete ui;
}


//Sets up the pause screen with the values from the config screen
void PauseDialog::setUpUI() {

    std::string stickman_size = Config::config()->getStickman()->getSize();
    int stickman_x_position = Config::config()->getStickman()->getXPosition();

    if (stickman_size == "tiny") {
        ui->tiny_radio->setChecked(true);
    }
    else if (stickman_size == "normal") {
        ui->normal_radio->setChecked(true);
    }
    else if (stickman_size == "large") {
        ui->large_radio->setChecked(true);
    }
    else if (stickman_size == "giant") {
        ui->giant_radio->setChecked(true);
    }

    ui->position_slider->setMaximum(Config::config()->getWorldWidth());
    ui->position_slider->setValue(stickman_x_position);

}


void PauseDialog::on_buttonBox_clicked(QAbstractButton *button) {
    // See what radio button is pressed
    if ((QPushButton *)button == ui->buttonBox->button(QDialogButtonBox::Close)) {

        if (ui->tiny_radio->isChecked()) {
            ui->tiny_radio->setChecked(true);
        }
        else if (ui->normal_radio->isChecked()) {
            ui->normal_radio->setChecked(true);
        }
        else if (ui->large_radio->isChecked()) {
            ui->large_radio->setChecked(true);
        }
        else if (ui->giant_radio->isChecked()) {
            ui->giant_radio->setChecked(true);
        }

        *this->paused = false;
    }

}


//Real-time update of the x position of the stickman
void PauseDialog::on_position_slider_actionTriggered(int /*action*/) {
    Config::config()->getStickman()->changeXPosition(ui->position_slider->value());
}


//Following methods update in real-time the size of the stickman

void PauseDialog::on_tiny_radio_clicked() {
    Config::config()->getStickman()->changeSize("tiny");
    Config::config()->getStickman()->updateStickman();
}


void PauseDialog::on_normal_radio_clicked() {
    Config::config()->getStickman()->changeSize("normal");
    Config::config()->getStickman()->updateStickman();
}

void PauseDialog::on_large_radio_clicked() {
    Config::config()->getStickman()->changeSize("large");
    Config::config()->getStickman()->updateStickman();
}

void PauseDialog::on_giant_radio_clicked() {
    Config::config()->getStickman()->changeSize("giant");
    Config::config()->getStickman()->updateStickman();
}

