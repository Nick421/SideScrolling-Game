#ifndef SCOREBOARDDIALOG_H
#define SCOREBOARDDIALOG_H

#include <QDialog>
#include <QList>
#include <QTextStream>
#include <QFile>

/*
 * Scoreboard class which display the scoreboard
 * Used a static instance in order to make it persist through out the game
*/
namespace Ui {
class ScoreboardDialog;
}

class ScoreboardDialog : public QDialog {
    Q_OBJECT

  public:
    static ScoreboardDialog* scoreboard() {

        static ScoreboardDialog scoreboard_instance;

        return &scoreboard_instance;
    }

    explicit ScoreboardDialog(QWidget* parent = nullptr);
    ~ScoreboardDialog();

    // set the score
    void setScore(int score);
    // read the scoreboard text file
    void readBoard();

  private slots:

    void on_Add_pressed();

    void on_buttonBox_accepted();

  private:
    Ui::ScoreboardDialog* ui;
    int m_score{}; // current score
    QString m_name; // player name
};

#endif // SCOREBOARDDIALOG_H
