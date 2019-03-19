#include "addstudentwindow.h"
#include "ui_addstudentwindow.h"
#include "student.h"
#include "prepod.h"
#include "header.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "header.h"


AddStudentWindow::AddStudentWindow(QWidget  *parent) :
    QDialog(parent),
    ui(new Ui::AddStudentWindow),
    name_validator(QRegExp("\\D{40}"))
{
        ui->setupUi(this);
        for(int i=1;i<32;i++)
        {
           ui->comboBox->addItem(QString::number(i));
        }
        for(int i=1;i<13;i++)
        {
           ui->comboBox_2->addItem(QString::number(i));
        }
        for(int i=2019;i>1900;i--)
        {
           ui->comboBox_3->addItem(QString::number(i));
        }
        ui->lineEdit->setValidator(&name_validator);
        switch(getkey())
        {
            case 0:
                 this->setWindowTitle("Добавить студента");
                 ui->pushButton_2->setText("Добавить");
                 break;
            case 1:
                 this->setWindowTitle("Отредактировать студента");
                 ui->pushButton_2->setText("Принять");
                 ui->lineEdit->setText(getname1(getnumbered()));
                 if(getscholarship(getnumbered())==0)                 {
                     ui->checkBox->setChecked(false);
                 }
                 else {
                     ui->checkBox->setChecked(true);
                 }
                 int i1 = getbirthday(getnumbered())/1000000;
                 int i2 = (getbirthday(getnumbered())-(i1*1000000))/10000;
                 int i3 = getbirthday(getnumbered())-(i1*1000000)-(i2*10000);
                 ui->comboBox->setCurrentText(QString::number(i1));
                 ui->comboBox_2->setCurrentText(QString::number(i2));
                 ui->comboBox_3->setCurrentText(QString::number(i3));
                 break;
        }
}

AddStudentWindow::~AddStudentWindow()
{
    delete ui;
}

void AddStudentWindow::on_buttonBox_accepted()
{

}

void AddStudentWindow::on_buttonBox_rejected()
{
    QWidget::close();
}

void AddStudentWindow::on_pushButton_2_clicked()
{
    switch(getkey())
    {
        case 0:{
            if(ui->lineEdit->text()=="")
            {
                QMessageBox::about(this,"info","Поля незаполненны");
                break;
            }
                MainWindow one;
                bool x = 0;
                if(ui->checkBox->isChecked())
                {
                    x=1;
                }
                else
                {
                    x=0;
                }
                int i = (ui->comboBox->currentText().toInt())*1000000+(ui->comboBox_2->currentText().toInt())*10000+(ui->comboBox_3->currentText().toInt());
                setStudent(ui->lineEdit->text(),x,i);
                QMessageBox::about(this,"Info","Студент добавлен");
                QWidget::close();
                break;

        }
        case 1:{
        if(ui->lineEdit->text()=="")
        {
            QMessageBox::about(this,"Info","Поля незаполненны");
            break;
        }
            MainWindow one;
            bool x = 0;
            if(ui->checkBox->isChecked())
            {
                x=1;
            }
            else
            {
                x=0;
            }
            int i = (ui->comboBox->currentText().toInt())*1000000+(ui->comboBox_2->currentText().toInt())*10000+(ui->comboBox_3->currentText().toInt());
            redStudent(ui->lineEdit->text(),x,i,getnumbered());
            QMessageBox::about(this,"Info","Студент отредактирован");
            QWidget::close();
            break;
        }

    }
}
