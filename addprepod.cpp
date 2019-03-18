#include "addprepod.h"
#include "ui_addprepod.h"
#include "student.h"
#include "prepod.h"
#include "header.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "header.h"


AddPrepodWindow::AddPrepodWindow(QWidget  *parent) :
    QDialog(parent),
    ui(new Ui::AddPrepodWindow),
    name_validator(QRegExp("\\D{40}"))
{
        ui->setupUi(this);
        ui->lineEdit->setValidator(&name_validator);
        ui->lineEdit_2->setValidator(new QIntValidator( 0,1000000 ));
        switch(getkey())
        {
            case 0:
                 this->setWindowTitle("Добавить преподавателя");
                 ui->pushButton_2->setText("Добавить");
                 break;
            case 1:
                this->setWindowTitle("Отредактировать преподавателя");
                ui->pushButton_2->setText("Принять");
                ui->lineEdit->setText(getname2(getnumbered()));
                ui->lineEdit_2->setText(QString::number(getsalary(getnumbered())));
                ui->comboBox->setCurrentText(getacademic(getnumbered()));
                break;
        }
}

AddPrepodWindow::~AddPrepodWindow()
{
    delete ui;
}

void AddPrepodWindow::on_buttonBox_accepted()
{

}

void AddPrepodWindow::on_buttonBox_rejected()
{
    QWidget::close();
}

void AddPrepodWindow::on_pushButton_2_clicked()
{
    switch(getkey())
    {
        case 0:{
            MainWindow one;
            setPrepod(ui->lineEdit->text(),ui->comboBox->currentText(),(ui->lineEdit_2->text()).toInt());
            QMessageBox::about(this,"","Преподаватель добавлен");
            QWidget::close();
            break;
        }
        case 1:{
            redPrepod(ui->lineEdit->text(),ui->comboBox->currentText(),(ui->lineEdit_2->text()).toInt(), getnumbered());
            QMessageBox::about(this,"","Преподаватель отредактирован");
            QWidget::close();
            break;
        }
    }
}
