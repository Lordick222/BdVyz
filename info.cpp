#include "info.h"
#include "ui_info.h"

info::info(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::info)
{
    ui->setupUi(this);
    ui->textEdit->setReadOnly(true);
}

info::~info()
{
    delete ui;
}
