#pragma once

#include <QDialog>

namespace Ui {
class GameDialog;
}

class GameDialog : public QDialog {

    Q_OBJECT

public slots:
    void nextFrame();

public:
    explicit GameDialog(QWidget *parent = nullptr);
    ~GameDialog() override;

protected:
    //Functions to get paused state but also set the pause state
    void pause() { paused = true; }
    void unpause() { paused = false; }
    bool getPausedState() { return paused; }

    Ui::GameDialog *ui;

    bool paused;
};
