#ifndef ADDSTUDKYRS_H
#define ADDSTUDKYRS_H

#include <QDialog>

namespace Ui {
class AddStudKyrs;
}

class AddStudKyrs : public QDialog
{
    Q_OBJECT

public:
    explicit AddStudKyrs(QWidget *parent = nullptr);
    ~AddStudKyrs();

private slots:
    void on_comboBox_activated(const QString &arg1);

    void on_pushButton_clicked();

private:
    Ui::AddStudKyrs *ui;
};

#endif // ADDSTUDKYRS_H
