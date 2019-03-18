#ifndef ADDPREPOD_H
#define ADDPREPOD_H

#include <QDialog>
#include <QValidator>

namespace Ui {
class AddPrepodWindow;
}

class AddPrepodWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddPrepodWindow(QWidget *parent = nullptr);
    ~AddPrepodWindow();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_pushButton_2_clicked();

private:
    Ui::AddPrepodWindow *ui;
    QRegExpValidator name_validator;
};

#endif // ADDPREPOD_H
