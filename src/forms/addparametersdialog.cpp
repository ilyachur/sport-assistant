#include "addparametersdialog.h"
#include "ui_addparametersdialog.h"

#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QHeaderView>
#include <QMessageBox>
#include <QTableWidgetItem>

#include "addactivity.h"

AddParametersDialog::AddParametersDialog(int activityID, QString dbName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddParametersDialog)
{
    ui->setupUi(this);

    this->activityID = activityID;
    dataBaseName = dbName;

    setWindowIcon(QIcon(":/icons/heart.ico"));

    QObject::connect(ui->btnCancel, SIGNAL(clicked(bool)), this, SLOT(close()));
    QObject::connect(ui->submit, SIGNAL(clicked(bool)), this, SLOT(submit()));
    QObject::connect(ui->create, SIGNAL(clicked(bool)), this, SLOT(createScheme()));
    QObject::connect(ui->btnMinus, SIGNAL(clicked(bool)), this, SLOT(removeRow()));
    QObject::connect(ui->btnPlus, SIGNAL(clicked(bool)), this, SLOT(addRow()));

    QObject::connect(ui->comboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(changeScheme()));

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setColumnCount(2);
    tablesItems.append(new QTableWidgetItem("Parameters"));
    tablesItems.append(new QTableWidgetItem("Values"));
    ui->tableWidget->setHorizontalHeaderItem(0, tablesItems.at(0));
    ui->tableWidget->setHorizontalHeaderItem(1, tablesItems.at(1));

    athleteDB.setNameDB(dataBaseName);

    activityTypes = athleteDB.getActivityTypes();
    if (activityTypes.size() > 0)
        currentScheme = activityTypes.at(0).at(0);

    setActivityTypes();
}

AddParametersDialog::~AddParametersDialog()
{
    clearTable();
    delete ui;
}

void AddParametersDialog::submit() {
    QString valuesStr;

    if (ui->tableWidget->rowCount() == 0) {
        QMessageBox::warning(this, "Warning! Table is empty.", "Table size is 0. Table is empty!");
        return;
    }

    QStringList fields = getParams(0);
    if (!fields.size())
        return;
    QStringList values = getParams(1);
    if (!values.size())
        return;

    if (fields.size() != values.size()) {
        return;
    }

    QString paramsList = "";
    if (!athleteDB.getTablesList().contains(currentScheme)) {
        QString paramsTypes = "";
        for(auto i(0); i < values.size(); i++) {
            QString currentType = "";
            if (values.at(i).contains(".")) {
                bool ok;
                values.at(i).toDouble(&ok);
                if (ok) {
                    currentType = "REAL";
                } else {
                    currentType = "TEXT";
                }
            } else {
                bool ok;
                values.at(i).toInt(&ok);
                if(ok) {
                    currentType = "INTEGER";
                } else {
                    currentType = "TEXT";
                }
            }


            fields.replace(i, fields.at(i) + "(" + currentType + ")");
            if (i == fields.size() - 1) {
                paramsTypes += "\"" + fields.at(i) + "\" " + currentType;
                paramsList += "\"" + fields.at(i) + "\"";
            } else {
                paramsTypes += "\"" + fields.at(i) + "\" " + currentType + ", ";
                paramsList += "\"" + fields.at(i) + "\",";
            }
        }
        QString withoutQuotesParamsList = paramsList;
        withoutQuotesParamsList.replace("\"", "");
        QStringList commands;
        commands.append("CREATE TABLE IF NOT EXISTS " + currentScheme + " (id integer PRIMARY KEY, " +
                        "activityID integer, " + paramsTypes + ", FOREIGN KEY(activityID) REFERENCES activities(ID))");
        commands.append("INSERT INTO activityTypes (activityType, paramsList) VALUES (\"" +
                        currentScheme + "\", \"" + withoutQuotesParamsList + "\")");
        athleteDB.execCommands(commands, true);
    } else {
        for(auto i(0); i < fields.size(); i++) {
            if (i == fields.size() - 1) {
                paramsList += fields.at(i);
            } else {
                paramsList += fields.at(i) + ",";
            }
        }
    }

    for(auto i(0); i < values.size(); i++) {
        valuesStr += "\"" + values.at(i) + "\"";
        if (i != values.size() - 1) {
            valuesStr += ", ";
        }
    }

    QStringList commands;
    commands.append("SELECT * FROM " + currentScheme + " WHERE activityID = " + QString::number(activityID));
    QSqlQuery existQuery = athleteDB.execCommands(commands, false).at(0);
    if (!existQuery.next()) {
        commands.clear();
        commands.append("INSERT INTO " + currentScheme + " (activityID, " + paramsList + ") VALUES (\"" +
                        QString::number(activityID) + "\", " + valuesStr + ")");
        athleteDB.execCommands(commands, true);
    } else {
        commands.clear();
        for (auto i(0); i < fields.size(); i++) {
            commands.append("UPDATE " + currentScheme + " SET \"" + fields.at(i) +
                            "\" = \"" + values.at(i) + "\" WHERE activityID = " + QString::number(activityID));
        }
        athleteDB.execCommands(commands, true);
    }
    close();
}

void AddParametersDialog::createScheme() {
    AddActivity addActivityDialog(this);
    addActivityDialog.exec();
}

void AddParametersDialog::removeRow() {
    if (ui->comboBox->count()) {
        ui->tableWidget->removeRow(ui->tableWidget->currentRow());
    }
}

void AddParametersDialog::addRow() {
    if (ui->comboBox->count()) {
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    }
}

QStringList AddParametersDialog::getParams(int col) {
    QStringList returnList;

    int rowCount = ui->tableWidget->rowCount();
    for(auto i(0); i < rowCount; i++) {
        QTableWidgetItem *item = ui->tableWidget->item(i, col);
        if (item == nullptr) {
            QMessageBox::warning(this, "Warning! Table has empty fields.", "Table has empty fields!");
            return QStringList();
        } else {
            returnList.append(ui->tableWidget->item(i, col)->text());
        }
    }
    return returnList;
}

void AddParametersDialog::setParams(int row) {
    if (row >= activityTypes.size()) {
        return;
    }

    clearTable();

    QStringList parameters = activityTypes.at(row).at(1).split(",");
    QStringList commands;
    commands.append("SELECT * FROM " + currentScheme + " WHERE activityID = " + QString::number(activityID));
    QSqlQuery query = athleteDB.execCommands(commands, false).at(0);
    QStringList values;
    while(query.next()) {
        for (auto i(2); ; i++) {
            if (!query.value(i).isValid())
                break;
            values.append(query.value(i).toString());
        }
    }

    ui->tableWidget->setRowCount(parameters.size());
    for(auto i(0); i < parameters.size(); i++) {
        QTableWidgetItem *newItem = new QTableWidgetItem(parameters.at(i));
        tablesItems.append(newItem);
        ui->tableWidget->setItem(i, 0, newItem);
        if (values.size() > i) {
            newItem = new QTableWidgetItem(values.at(i));
            tablesItems.append(newItem);
            ui->tableWidget->setItem(i, 1, newItem);
        }
    }
}

void AddParametersDialog::changeScheme() {
    currentScheme = ui->comboBox->currentText();
    for(auto i(0); i < activityTypes.size(); i++) {
        if (currentScheme == activityTypes.at(i).at(0)) {
            setParams(i);
            break;
        }
    }
}

void AddParametersDialog::setActivityTypes(QString newActivity) {
    if (newActivity == "" && ui->comboBox->count() > 0)
        return;
    ui->comboBox->clear();
    activityTypes = athleteDB.getActivityTypes();
    for(auto i(0); i < activityTypes.size(); i++) {
        ui->comboBox->addItem(activityTypes.at(i).at(0));
    }

    if (newActivity != "") {
        int index = ui->comboBox->count();
        ui->comboBox->addItem(newActivity);
        currentScheme = newActivity;
        ui->comboBox->setCurrentIndex(index);
        clearTable();
    }
}

void AddParametersDialog::clearTable() {
    for(auto i(0); i < tablesItems.size(); i++) {
        delete tablesItems.at(i);
    }
    tablesItems.clear();
    ui->tableWidget->setRowCount(0);
}
