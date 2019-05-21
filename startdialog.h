#pragma once

#include <QDialog>

class GameFactory;

namespace Ui {
class StartDialog;
}

class StartDialog : public QDialog {
    Q_OBJECT

public:
    explicit StartDialog(GameFactory* gameFactory, QWidget *parent = nullptr);
    ~StartDialog();

    virtual void setUpUI();

protected:
    void keyPressEvent(QKeyEvent *event);

private slots:

    void on_bg1_radio_clicked();
    void on_bg2_radio_clicked();
    void on_start_clicked();

private:
    Ui::StartDialog *ui;
    GameFactory* gameFactory;
};

