#ifndef SCOREBOARDDIALOG_H
#define SCOREBOARDDIALOG_H

#include <QDialog>
#include <QList>

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

    void setScore(int score);

  private slots:
    void on_Add_pressed();

    void on_Sort_pressed();

  private:
    Ui::ScoreboardDialog* ui;
    int m_score;
    int old_score;
    QString m_name;
};

#endif // SCOREBOARDDIALOG_H