#include "redstudentwindow.h"
#include "ui_redstudentwindow.h"
#include "student.h"
#include "header.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "header.h"


RedStudentWindow::RedStudentWindow(QWidget  *parent) :
    QDialog(parent),
    ui(new Ui::RedStudentWindow)
{
        ui->setupUi(this);
      /* QRegExp rx("[0-3][0-9].[0-1][0-9].[1-2][0-9][0-3][0-9]");
        QRegExpValidator *validator = new QRegExpValidator(QRegExp(rx),ui->lineEdit_2);
        ui->lineEdit_2->setValidator(validator);*/
        ui->lineEdit_2->setInputMask("HH.HH.HHHH");

}

RedStudentWindow::~RedStudentWindow()
{
    delete ui;
}

void RedStudentWindow::on_buttonBox_accepted()
{

}

void RedStudentWindow::on_buttonBox_rejected()
{
    QWidget::close();
}

void RedStudentWindow::on_pushButton_2_clicked()
{

}
