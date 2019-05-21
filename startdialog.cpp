#include "startdialog.h"
#include "ui_startdialog.h"

#include "config.h"
#include "gamedialog.h"
#include "gamefactory.h"

#include <QKeyEvent>
#include <memory>

StartDialog::StartDialog(GameFactory* gameFactory, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartDialog),
    gameFactory(gameFactory) {

    ui->setupUi(this);
    // this->setStyleSheet("background-color: #FFFFFF;"); //White
    this->setFixedSize(this->width(), this->height());
    setUpUI();

}

StartDialog::~StartDialog() {
    delete ui;
    delete gameFactory;
}

//Sets up the start screen with the values from the config screen as well as the background options
void StartDialog::setUpUI() {

    QPixmap bg1_image(":img/background1/background.png");
    bg1_image = bg1_image.scaled(ui->bg1->width(), ui->bg1->height());
    ui->bg1->setPixmap(bg1_image);

    QPixmap bg2_image(":img/background2/background.png");
    bg2_image = bg2_image.scaled(ui->bg2->width(), ui->bg2->height());
    ui->bg2->setPixmap(bg2_image);

    if (Config::config()->getBackgroundNumber() == 1) {
        ui->bg1_radio->setChecked(true);
    } else {
        ui->bg2_radio->setChecked(true);
    }
}


void StartDialog::on_bg1_radio_clicked() {
    Config::config()->setBackgroundNumber(1);
}

void StartDialog::on_bg2_radio_clicked() {
    Config::config()->setBackgroundNumber(2);
}

void StartDialog::on_start_clicked() {

    /*
     * Close the main menu dialog
     * Show the game dialog
    */

    close();

    auto game_dialog = std::unique_ptr<GameDialog>(gameFactory->createGame());
    game_dialog->setModal(true);
    game_dialog->setWindowTitle("Running Stickman");
    game_dialog->exec();

    show();
}

void StartDialog::keyPressEvent(QKeyEvent *event) {

    if (event->type()==QEvent::KeyPress) {

        QKeyEvent* key = static_cast<QKeyEvent*>(event);

        if ( (key->key()==Qt::Key_Q) ) { //P was pressed

            //Close the main menu dialog (meaning the whole game)
            close();

        }

    }
}

