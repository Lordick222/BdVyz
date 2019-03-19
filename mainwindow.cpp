#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addstudentwindow.h"
#include "addprepod.h"
#include "addstudkyrs.h"
#include "info.h"
#include "header.h"
#include "prepod.h"
#include "student.h"
#include <QByteArray>



int numberred;
bool key=0; bool key2=0; bool key3=0;
int sizestudent=0;      //students
QVector<Student*> student;
QVector<Student*> studentdel;
int sizeprepod=0;      //students
QVector<Prepod*> prepod;
bool  schet = 1;
QMultiMap <Prepod*, Student*> myMultimap;
Prepod *prepodselect;



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QTextCodec::setCodecForLocale( QTextCodec::codecForName( "UTF-8" ) );
    ui->setupUi(this);
    ui->lineEdit->setReadOnly(true);
    ui->lineEdit->setText("Студенты обучающиеся у преподавателя");
    ui->lineEdit->setAlignment(Qt::AlignCenter);
    ui->tableViewStudent->setRowCount(0);
    ui->tableViewStudent->setColumnCount(3);
    ui->tableViewStudent->setHorizontalHeaderLabels(QStringList() << "Ф.И.О" << "Стипендия" << "Дата рождения");
    ui->tableViewStudent->horizontalHeader()->setStretchLastSection(true);
    ui->tableViewStudent->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableViewStudent->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableViewStudent, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotCustomMenuRequested(QPoint)));

    ui->tableViewPrepod->setRowCount(0);
    ui->tableViewPrepod->setColumnCount(3);
    ui->tableViewPrepod->setHorizontalHeaderLabels(QStringList() << "Ф.И.О" << "Ученная степень" << "Зарплата");
    ui->tableViewPrepod->horizontalHeader()->setStretchLastSection(true);
    ui->tableViewPrepod->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableViewPrepod->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableViewPrepod, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(showtableStud()));
    connect(ui->tableViewPrepod, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotCustomMenuRequested(QPoint)));
                                                                                                //table of student
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Ф.И.О" << "Стипендия" << "Дата рождения");
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotCustomMenuRequested(QPoint)));
}


void MainWindow::slotCustomMenuRequested(QPoint pos)
{
            QMenu * menu = new QMenu(this);


                QAction * deleteDevice = new QAction(("Удалить"), this);
                connect(deleteDevice, SIGNAL(triggered()), this, SLOT(slotRemoveRecord()));
                menu->addAction(deleteDevice);

            if ((ui->tableViewPrepod->hasFocus())||(ui->tableViewStudent->hasFocus()))
            {
                QAction * editDevice = new QAction(("Редактировать"), this);
                connect(editDevice, SIGNAL(triggered()), this, SLOT(slotEditRecord()));
                menu->addAction(editDevice);
            }
            if ((ui->tableViewPrepod->hasFocus()))
            {
                QAction * addStud = new QAction(("Добавить на курс"), this);
                connect(addStud, SIGNAL(triggered()), this, SLOT(slotAddStud()));
                menu->addAction(addStud);
            }
            menu->popup(QCursor::pos());
}





void MainWindow::slotRemoveRecord()
{
    if ((ui->tableViewStudent->hasFocus()))
    {
        int row = ui->tableViewStudent->selectionModel()->currentIndex().row();
        if(row >= 0){
            if (QMessageBox::warning(this,
                                     ("Удаление записи"),
                                     ("Вы уверены, что хотите удалить эту запись?"),
                                     QMessageBox::Yes | QMessageBox::No) == QMessageBox::No)
            {
                return;
            }
            else
            {
                int sizestudent_del=sizestudent - row-1;
                auto itMultimap = myMultimap.begin();
                for (itMultimap = myMultimap.begin(); itMultimap != myMultimap.end(); itMultimap++)
                {
                    if (student[row]==itMultimap.value())
                        {
                            myMultimap.erase(itMultimap);
                        }
                }
                key2=0;
                showtableStud();
                key2=1;
                for(int i=0;i<sizestudent_del;i++)
                {
                    student[row]=student[row+1];
                    row++;
                }
                sizestudent--;
                student.resize(sizestudent);
                ui->tableViewStudent->setRowCount(sizestudent);
                addToTable();
                QMessageBox::about(this,"Info","Студент удален");
            }
         }
    } else if ((ui->tableViewPrepod->hasFocus())) {
        int row = ui->tableViewPrepod->selectionModel()->currentIndex().row();
        if(row >= 0){
            if (QMessageBox::warning(this,
                                     ("Удаление записи"),
                                     ("Вы уверены, что хотите удалить эту запись?"),
                                     QMessageBox::Yes | QMessageBox::No) == QMessageBox::No)
            {
                return;
            }
            else
            {
                int sizeprepod_del=sizeprepod - row-1;
                auto itMultimap = myMultimap.begin();
                for (itMultimap = myMultimap.begin(); itMultimap != myMultimap.end(); itMultimap++)
                {
                    if (prepod[row]==itMultimap.key())
                        {
                            myMultimap.erase(itMultimap);
                        }
                }
                key2=0;
                showtableStud();
                key2=1;
                for(int i=0;i<sizeprepod_del;i++)
                {
                   prepod[row]=prepod[row+1];
                   row++;
                }
                sizeprepod--;
                prepod.resize(sizeprepod);
                ui->tableViewPrepod->setRowCount(sizeprepod);
                addToTableS();
                QMessageBox::about(this,"Info","Преподаватель удален");
            }
        }
    }
    else{
        int row = ui->tableWidget->selectionModel()->currentIndex().row();
        if(row >= 0){
            if (QMessageBox::warning(this,
                                     ("Удаление записи"),
                                     ("Вы уверены, что хотите удалить эту запись?"),
                                     QMessageBox::Yes | QMessageBox::No) == QMessageBox::No)
            {
                return;
            }
            else
            {
                auto itMultimap = myMultimap.begin();
                int i=0;
                for (itMultimap = myMultimap.begin(); itMultimap != myMultimap.end(); itMultimap++)
                {
                    if (prepodselect==itMultimap.key())
                        {
                            if(studentdel.size()<i+1)
                            {
                                studentdel.push_back(new Student);
                            }
                            studentdel[i]=itMultimap.value();
                            i++;
                        }
                }
                myMultimap.remove(prepodselect,studentdel[row]);
                key2=0;
                showtableStud();
                key2=1;
            }
         }


    }
}


void MainWindow::slotAddStud()
{
        key2 = 0;
        int row = ui->tableViewPrepod->selectionModel()->currentIndex().row();
        numberred = row;
        AddStudKyrs addstud1;
        addstud1.setModal(true);
        addstud1.exec();
        showtableStud();
        key2=1;
}

void MainWindow::showtableStud()
{
    if(ui->tableViewPrepod->hasFocus())
    {
        int row;
        row = ui->tableViewPrepod->selectionModel()->currentIndex().row();
        prepodselect=prepod[row];
    }
    ui->tableWidget->setRowCount(myMultimap.count(prepodselect));
    auto itMultimap = myMultimap.begin();
    int i=0;
            for (itMultimap = myMultimap.begin(); itMultimap != myMultimap.end(); itMultimap++)
            {
                if (prepodselect==itMultimap.key())
                {
                    QTableWidgetItem *a = new QTableWidgetItem(tr("%1").arg(itMultimap.value()->getname()));
                    ui->tableWidget->setItem(i,0,a);
                    QWidget *checkBoxWidget = new QWidget();
                    QCheckBox *checkBox = new QCheckBox();
                    QHBoxLayout *layoutCheckBox = new QHBoxLayout(checkBoxWidget);
                    layoutCheckBox->addWidget(checkBox);
                    layoutCheckBox->setAlignment(Qt::AlignCenter);
                    layoutCheckBox->setContentsMargins(0,0,0,0);
                    if(itMultimap.value()->getscholarship()==1)
                    {
                       checkBox->setChecked(true);
                    }
                    else
                    {
                        checkBox->setChecked(false);
                    }
                    checkBox->setEnabled(false);
                    ui->tableWidget->setCellWidget(i,1, checkBoxWidget);
                    QString g;
                    int i1 = itMultimap.value()->getbirthday()/1000000;
                    g = QString::number(i1);
                    g.append(".");
                    int i2 = ((itMultimap.value()->getbirthday())-(i1*1000000))/10000;
                    g.append(QString::number(i2));
                    g.append(".");
                    int i3 = ((itMultimap.value()->getbirthday())-(i1*1000000))-i2*10000;
                    g.append(QString::number(i3));
                    QTableWidgetItem *c = new QTableWidgetItem(tr("%1").arg(g));
                    ui->tableWidget->setItem(i,2,c);
                    i++;
                }
            }
    if(key2 == 1)
    {
        QMessageBox::about(this,"Info","Таблица обновленна");
    }
}
void MainWindow::slotEditRecord()
{
    if(ui->tableViewStudent->hasFocus())
    {
        key=1;
        int row = ui->tableViewStudent->selectionModel()->currentIndex().row();
        numberred = row;
        AddStudentWindow addstud1;
        addstud1.setModal(true);
        addstud1.exec();
        addToTable();
        key2=0;
        showtableStud();
        key2=1;
    }
    if(ui->tableViewPrepod->hasFocus())
    {
        key=1;
        int row = ui->tableViewPrepod->selectionModel()->currentIndex().row();
        numberred = row;
        AddPrepodWindow addstud1;
        addstud1.setModal(true);
        addstud1.exec();
        addToTableS();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::closeEvent(QCloseEvent *event)
{
        event->ignore();
        if (QMessageBox::Yes == QMessageBox::warning(this, "Закрыть?",
                              "Уверены?",
                              QMessageBox::Yes|QMessageBox::No))
        {
        event->accept();
        if (QMessageBox::warning(this,
                                  ("Закрыть?"),
                                  ("Сохранить базу данных перед выходом?"),
                                  QMessageBox::Yes | QMessageBox::No) == QMessageBox::No)
         {
             return;
         }
         else
         {
             save();
         }
        }
}

void MainWindow::on_pushButton_clicked()
{
    key=0;
    AddStudentWindow addstud1;
    addstud1.setModal(true);
    addstud1.exec();
    ui->tableViewStudent->setRowCount(sizestudent);
    addToTable();
}



void MainWindow::addToTable()
{
    for(int i=0;i<sizestudent;i++)
     {
             QTableWidgetItem *a = new QTableWidgetItem(tr("%1").arg(student[i]->getname()));
             ui->tableViewStudent->setItem(i,0,a);
             QWidget *checkBoxWidget = new QWidget();
             QCheckBox *checkBox = new QCheckBox();
             QHBoxLayout *layoutCheckBox = new QHBoxLayout(checkBoxWidget);
             layoutCheckBox->addWidget(checkBox);
             layoutCheckBox->setAlignment(Qt::AlignCenter);
             layoutCheckBox->setContentsMargins(0,0,0,0);
             if(student[i]->getscholarship()==1)
             {
                checkBox->setChecked(true);
             }
             else
             {
                 checkBox->setChecked(false);
             }
             checkBox->setEnabled(false);
             ui->tableViewStudent->setCellWidget(i,1, checkBoxWidget);
             QString g;
             int i1 = student[i]->getbirthday()/1000000;
             g = QString::number(i1);
             g.append(".");
             int i2 = ((student[i]->getbirthday())-(i1*1000000))/10000;
             g.append(QString::number(i2));
             g.append(".");
             int i3 = ((student[i]->getbirthday())-(i1*1000000))-i2*10000;
             g.append(QString::number(i3));
             QTableWidgetItem *c = new QTableWidgetItem(tr("%1").arg(g));
             ui->tableViewStudent->setItem(i,2,c);
     }
}

void MainWindow::addToTableS()
{
    for(int i=0;i<sizeprepod;i++)
     {
             QTableWidgetItem *a = new QTableWidgetItem(tr("%1").arg(prepod[i]->getname()));
             ui->tableViewPrepod->setItem(i,0,a);

             QTableWidgetItem *b = new QTableWidgetItem(tr("%1").arg(prepod[i]->getacademic()));
             ui->tableViewPrepod->setItem(i,1,b);

             QTableWidgetItem *c = new QTableWidgetItem(tr("%1").arg(prepod[i]->getsalary()));
             ui->tableViewPrepod->setItem(i,2,c);
     }
}

void setStudent(QString name1, bool scholarship1,   int birthday1)
{
    student.push_back(new Student);
    student[sizestudent]->setname(name1);
    student[sizestudent]->setscholarship(scholarship1);
    student[sizestudent]->setbirthday(birthday1);
    sizestudent++;
}
void redStudent(QString name1, bool scholarship1,   int birthday1,int a)
{
    student[a]->setname(name1);
    student[a]->setscholarship(scholarship1);
    student[a]->setbirthday(birthday1);
}


void setPrepod(QString name1, QString academic1 ,  int salary1)
{
    prepod.push_back(new Prepod);
    prepod[sizeprepod]->setname(name1);
    prepod[sizeprepod]->setacademic(academic1);
    prepod[sizeprepod]->setsalary(salary1);
    sizeprepod++;
}
void redPrepod(QString name1, QString academic1 ,  int salary1, int a)
{
    prepod[a]->setname(name1);
    prepod[a]->setacademic(academic1);
    prepod[a]->setsalary(salary1);
}


void MainWindow::on_action_2_triggered()
{

    load();
}

void MainWindow::on_pushButton_2_clicked()
{
    key=0;
    AddPrepodWindow addprepod1;
    addprepod1.setModal(true);
    addprepod1.exec();
    ui->tableViewPrepod->setRowCount(sizeprepod);
    addToTableS();
}




int getkey(){               return key;}
int getstudentsize(){       return sizestudent;}
int getnumbered(){          return numberred;}


QString getname1(int a){    return student[a]->getname();}          //student
bool getscholarship(int a){    return student[a]->getscholarship();}
int getbirthday(int a){    return student[a]->getbirthday();}

QString getname2(int a){  return prepod[a]->getname();}               //prepod
QString getacademic(int a){  return prepod[a]->getacademic();}
int getsalary(int a){  return prepod[a]->getsalary();}


void setMultiMap(int a,int b)
{
    myMultimap.insert(prepod[a],student[b]);
}

bool checkpair(int a,int b)
{
    auto itMultimap = myMultimap.begin();
            for (itMultimap = myMultimap.begin(); itMultimap != myMultimap.end(); itMultimap++)
            {
                if (prepod[a]==itMultimap.key()&&student[b]==itMultimap.value())
                {
                   return 1;
                }
            }
    return 0;
}

void MainWindow::save()
{
    QFile fileOut("fileout.txt");
    if(fileOut.open(QIODevice::WriteOnly | QIODevice::Text))
    {
            QTextStream writeStream(&fileOut);
            writeStream << sizestudent << "\n";
            writeStream << sizeprepod << "\n";
            for(int i=0;i<sizestudent;i++)
            {
                writeStream << student[i]->getname() << "\n";
                writeStream << student[i]->getscholarship() << "\n";
                writeStream << student[i]->getbirthday() << "\n";
            }
            for(int i=0;i<sizeprepod;i++)
            {
                writeStream << prepod[i]->getname() << "\n";
                writeStream << prepod[i]->getacademic()<< "\n";
                writeStream << prepod[i]->getsalary()<< "\n";
            }
            writeStream << myMultimap.size() << "\n";
                auto itMultimap = myMultimap.begin();
                for (itMultimap = myMultimap.begin(); itMultimap != myMultimap.end(); itMultimap++)
                {
                    for(int i=0;i<sizeprepod;i++)
                    {
                        if(prepod[i]==itMultimap.key())
                        {
                            writeStream << i<< "\n";
                            break;
                        }
                    }
                    for(int i=0;i<sizestudent;i++)
                    {
                        if(student[i]==itMultimap.value())
                        {
                            writeStream << i<< "\n";
                            break;
                        }
                    }
                  }
            fileOut.close();
            QMessageBox::about(this,"Info","База данных сохранена");
    }
}

void MainWindow::load()
{
    QFile filein("fileout.txt");
    if(filein.open(QIODevice::ReadOnly | QIODevice::Text))
    {
       student.clear();
       prepod.clear();
       sizestudent= (filein.readLine().toInt());
       sizeprepod= (filein.readLine().toInt());
       for(int i=0;i<sizestudent;i++)
       {
           student.push_back(new Student);
           student[i]->setname((filein.readLine()).trimmed());
           student[i]->setscholarship(filein.readLine().toInt());
           student[i]->setbirthday(filein.readLine().toInt());
       }
       for(int i=0;i<sizeprepod;i++)
       {
           prepod.push_back(new Prepod);
           prepod[i]->setname(filein.readLine().trimmed());
           prepod[i]->setacademic(filein.readLine().trimmed());
           prepod[i]->setsalary(filein.readLine().toInt());
       }
       int a = filein. readLine().toInt();
       int x;
       int y;
       myMultimap.clear();
       for(int i=0;i<a;i++)
       {
           x = filein.readLine().toInt();
           y=filein.readLine().toInt();
           myMultimap.insert(prepod[x],student[y]);
       }
    }
    filein.close();
    QMessageBox::about(this,"Info","База данных загружена");
    ui->tableViewPrepod->setRowCount(sizeprepod);
    ui->tableViewStudent->setRowCount(sizestudent);
    addToTable();
    addToTableS();
    key2=0;
    showtableStud();
    key2=1;
}

void MainWindow::on_action_triggered()
{
    save();
}

void MainWindow::on_actionInfo_triggered()
{
     info a1;
     a1.setModal(true);
     a1.exec();
}
