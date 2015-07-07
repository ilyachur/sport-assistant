#ifndef PREDICTDIALOG_H
#define PREDICTDIALOG_H

#include <QDialog>

namespace Ui {
class PredictDialog;
}

class PredictDialog : public QDialog
{
    Q_OBJECT

public:
    PredictDialog(QString typeByDefault, QWidget *parent = 0);
    ~PredictDialog();

private:
    Ui::PredictDialog *ui;
};

#endif // PREDICTDIALOG_H
