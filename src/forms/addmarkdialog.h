#ifndef ADDMARKDIALOG_H
#define ADDMARKDIALOG_H

#include <QDialog>

namespace Ui {
class AddMarkDialog;
}

class AddMarkDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddMarkDialog(QWidget *parent = 0);
    ~AddMarkDialog();

private:
    Ui::AddMarkDialog *ui;
};

#endif // ADDMARKDIALOG_H
