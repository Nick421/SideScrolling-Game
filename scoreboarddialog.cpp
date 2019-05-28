#include "scoreboarddialog.h"
#include "ui_scoreboarddialog.h"

ScoreboardDialog::ScoreboardDialog(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::ScoreboardDialog),
    old_score(0) {
    ui->setupUi(this);
    readBoard();
}

ScoreboardDialog::~ScoreboardDialog() {
    delete ui;
}

void ScoreboardDialog::setScore(int score) {
    m_score = score;
}

void ScoreboardDialog::readBoard() {
    QFile file("/Users/nicktheng/Documents/GitHub/SideScrolling-Game/scoreboard.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    std::map<int, std::string> map;
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList record = line.split(" : ", QString::SkipEmptyParts);
        int score = record[1].toInt();
        std::string name = record[0].toStdString();
        map.emplace(score, name);

    }

    for (auto it = map.rbegin(); it != map.rend(); ++it) {
        QListWidgetItem* item = new QListWidgetItem;
        QString name = it->second.c_str();
        QString score = QString::number(it->first);
        QString line = name + " : " + score;
        item->setText(line);
        ui->listWidget->addItem(item);
    }

    file.close();

}

void ScoreboardDialog::on_Add_pressed() {

    QList<QListWidgetItem*> list = ui->listWidget->findItems(ui->lineEdit->text(), Qt::MatchFlag::MatchStartsWith);
    if (list.size() == 0) {

        m_name = ui->lineEdit->text();
        ui->listWidget->addItem(m_name + " : " + QString::number(m_score));
    } else {
        for (auto it : list) {
            QStringList temp = (*it).text().split(" : ", QString::SkipEmptyParts);

            if (temp.first() == ui->lineEdit->text() && temp[1].toInt() != m_score) {

                ui->listWidget->takeItem(ui->listWidget->row(it));
                ui->listWidget->addItem(m_name + " : " + QString::number(m_score));
            }
        }
    }

}

void ScoreboardDialog::on_buttonBox_accepted() {
    QFile file("/Users/nicktheng/Documents/GitHub/SideScrolling-Game/scoreboard.txt");
    if (!file.open(QFile::WriteOnly | QIODevice::Text)) {
        return;
    }

    for(int row = 0; row < ui->listWidget->count(); row++) {
        QListWidgetItem* item = ui->listWidget->item(row);
        QTextStream out(&file);
        out << item->text().simplified() << "\n";
    }

    file.close();
}
