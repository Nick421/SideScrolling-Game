#pragma once

#include "gamedialog.h"

#include <QDialog>
#include <QPixmap>
#include <QDesktopWidget>
#include <QApplication>

#include "background.h"

class QTimer;
class QWidget;
class QPaintEvent;
class QKeyEvent;

class Stage1Game : public GameDialog {
public:
    explicit Stage1Game(QWidget *parent = nullptr);
    ~Stage1Game() override;

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

    //Functions to get paused state but also set the pause state
    void pause() { paused = true; }
    void unpause() { paused = false; }
    bool getPausedState() { return paused; }

private:
    QTimer *timer;
    Background background;
    int stickman_frame;
    int counter;
};
