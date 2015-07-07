#ifndef ADDPARAMETERSDIALOG_H
#define ADDPARAMETERSDIALOG_H

#include <QDialog>

namespace Ui {
class AddParametersDialog;
}

class AddParametersDialog : public QDialog
{
    Q_OBJECT

public:
    AddParametersDialog(int _activityID, QString dbName, QWidget *parent = 0);
    ~AddParametersDialog();

private:
    Ui::AddParametersDialog *ui;
};

#endif // ADDPARAMETERSDIALOG_H
