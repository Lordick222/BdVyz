#ifndef REDSTUDENTWINDOW_H
#define REDSTUDENTWINDOW_H

#include <QDialog>

namespace Ui {
class RedStudentWindow;
}

class RedStudentWindow : public QDialog
{
    Q_OBJECT

public:
    explicit RedStudentWindow(QWidget *parent = nullptr);
    ~RedStudentWindow();

private slots:
    void on_buttonBox_accepted();
    
    void on_buttonBox_rejected();

    void on_pushButton_2_clicked();

private:
    Ui::RedStudentWindow *ui;
};

#endif // REDSTUDENTWINDOW_H
