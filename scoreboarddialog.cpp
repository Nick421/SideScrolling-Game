#include "scoreboarddialog.h"
#include "ui_scoreboarddialog.h"

ScoreboardDialog::ScoreboardDialog(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::ScoreboardDialog) {
    ui->setupUi(this);
    // read the text file for previous scoreboard if exist
    readBoard();
}

ScoreboardDialog::~ScoreboardDialog() {
    delete ui;
}

void ScoreboardDialog::setScore(int score) {
    m_score = score;
}

/*
 * Initialise the previous scoreboard
 * The file uses here is relative path as Mac OS have some problems
 * Please change the file path to where u want to save the txt file
*/
void ScoreboardDialog::readBoard() {
    QFile file("/Users/nicktheng/Documents/GitHub/SideScrolling-Game/scoreboard.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    // store all score and names in a map
    std::map<int, std::string> map;
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList record = line.split(" : ", QString::SkipEmptyParts);
        int score = record[1].toInt();
        std::string name = record[0].toStdString();
        map.emplace(score, name);

    }

    // since hashmap is sorted we can add them back to the listWidget

    for (auto it = map.rbegin(); it != map.rend(); ++it) {
        auto* item = new QListWidgetItem;
        QString name = it->second.c_str();
        QString score = QString::number(it->first);
        QString line = name + " : " + score;
        item->setText(line);
        ui->listWidget->addItem(item);
    }

    file.close();

}

/*
 * On add button add the player name and their score
*/
void ScoreboardDialog::on_Add_pressed() {

    // find if the name already exists in the list
    QList<QListWidgetItem*> list = ui->listWidget->findItems(ui->lineEdit->text(), Qt::MatchFlag::MatchStartsWith);

    // if it doesn't, add it in
    // else we find the name in the list and replace if their high score changes
    if (list.empty() && !ui->lineEdit->text().isEmpty()) {
        m_name = ui->lineEdit->text();
        ui->listWidget->addItem(m_name + " : " + QString::number(m_score));

    } else if (!ui->lineEdit->text().isEmpty()) {
        for (auto it : list) {
            QStringList temp = (*it).text().split(" : ", QString::SkipEmptyParts);

            if (temp.first() == ui->lineEdit->text() && temp[1].toInt() != m_score) {

                ui->listWidget->takeItem(ui->listWidget->row(it));
                ui->listWidget->addItem(m_name + " : " + QString::number(m_score));
            }
        }
    }

}

// on Ok button pressed we save the scoreboard to txt
void ScoreboardDialog::on_buttonBox_accepted() {

    // please replace this file path with your local one as Mac OS had issues with relative path
    QFile file("/Users/nicktheng/Documents/GitHub/SideScrolling-Game/scoreboard.txt");
    if (!file.open(QFile::WriteOnly | QIODevice::Text)) {
        return;
    }

    // go through the list and write to file
    for(int row = 0; row < ui->listWidget->count(); row++) {
        QListWidgetItem* item = ui->listWidget->item(row);
        QTextStream out(&file);
        out << item->text().simplified() << "\n";
    }

    file.close();
}
