#ifndef MARKTRAININGDIALOG_H
#define MARKTRAININGDIALOG_H

#include <QDialog>

namespace Ui {
class MarkTrainingDialog;
}

class MarkTrainingDialog : public QDialog
{
    Q_OBJECT

public:
    MarkTrainingDialog(int _activityID, QString dbName, QWidget *parent = 0);
    ~MarkTrainingDialog();

private:
    Ui::MarkTrainingDialog *ui;
};

#endif // MARKTRAININGDIALOG_H
