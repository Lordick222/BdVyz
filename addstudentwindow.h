#ifndef ADDSTUDENTWINDOW_H
#define ADDSTUDENTWINDOW_H

#include <QDialog>
#include <QValidator>

namespace Ui {
class AddStudentWindow;
}

class AddStudentWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddStudentWindow(QWidget *parent = nullptr);
    ~AddStudentWindow();

private slots:
    void on_buttonBox_accepted();
    
    void on_buttonBox_rejected();

    void on_pushButton_2_clicked();

private:
    Ui::AddStudentWindow *ui;
    QRegExpValidator name_validator;
};

#endif // ADDSTUDENTWINDOW_H
