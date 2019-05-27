#include "scoreboarddialog.h"
#include "ui_scoreboarddialog.h"

ScoreboardDialog::ScoreboardDialog(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::ScoreboardDialog),
    old_score(0) {
    ui->setupUi(this);
}

ScoreboardDialog::~ScoreboardDialog() {
    delete ui;
}

void ScoreboardDialog::setScore(int score) {
    m_score = score;
}

void ScoreboardDialog::on_Add_pressed() {

    QList<QListWidgetItem*> list = ui->listWidget->findItems(ui->lineEdit->text(), Qt::MatchFlag::MatchStartsWith);
    if (list.size() == 0) {

        m_name = ui->lineEdit->text();
        ui->listWidget->addItem(m_name + " : " + QString::number(m_score));
    } else {
        for (auto it : list) {
            QStringList temp = (*it).text().split(" : ", QString::SkipEmptyParts);

            if (temp.first() == ui->lineEdit->text() && temp[1].toInt() != m_score ) {

                ui->listWidget->takeItem(ui->listWidget->row(it));
                ui->listWidget->addItem(m_name + " : " + QString::number(m_score));
            }
        }
    }

}

void ScoreboardDialog::on_Sort_pressed() {
    ui->listWidget->sortItems(Qt::DescendingOrder);
}
