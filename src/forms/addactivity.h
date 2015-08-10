#ifndef ADDACTIVITY_H
#define ADDACTIVITY_H

#include <QDialog>

namespace Ui {
class AddActivity;
}

class AddActivity : public QDialog
{
    Q_OBJECT

public:
    explicit AddActivity(QWidget *parent = 0);
    ~AddActivity();

private:
    Ui::AddActivity *ui;
public slots:
    void add();
};

#endif // ADDACTIVITY_H
