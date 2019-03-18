#include "addstudkyrs.h"
#include "ui_addstudkyrs.h"
#include "header.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

AddStudKyrs::AddStudKyrs(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddStudKyrs)
{
    ui->setupUi(this);
    for (int i=0;i< getstudentsize();i++)
    {
        ui->comboBox->addItem(getname1(i));
    }
}

AddStudKyrs::~AddStudKyrs()
{
    delete ui;
}

void AddStudKyrs::on_comboBox_activated(const QString &arg1)
{

}

void AddStudKyrs::on_pushButton_clicked()
{
    for (int i=0;i< getstudentsize();i++)
    {
        if(ui->comboBox->currentText()==getname1(i))
        {
            if(checkpair(getnumbered(),i))
            {
                QMessageBox::about(this,"","Студент уже добавлен на курс");
            }
            else
            {
                setMultiMap(getnumbered(),i);
                QMessageBox::about(this,"","Студент добавлен на курс");
                QWidget::close();
                break;
            }
        }
    }
     //QMessageBox::about(this,"","Студент добавлен на курс");
     //QWidget::close();
}
