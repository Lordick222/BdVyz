#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QFile>
#include <QTextStream>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void tablestudresize();
    void addToTable();
    void addToTableS();
    QStandardItemModel *tablestud;
    QStandardItemModel *tableprepod;
    void save();
    void load();
    void closeEvent(QCloseEvent *event);



private slots:
    void on_pushButton_clicked();
    void slotEditRecord();
    void slotRemoveRecord();
    void slotAddStud();
    void slotCustomMenuRequested(QPoint pos);
    void showtableStud();


    void on_action_triggered();

    void on_action_2_triggered();

    void on_pushButton_2_clicked();

    void on_actionInfo_triggered();

private:
    Ui::MainWindow *ui;
};

void setStudent(QString name1, bool scholarship1,   int birthday1);
void redStudent(QString name1, bool scholarship1,   int birthday1,int a);

void setPrepod(QString name1, QString academic1 ,  int salary1);
void redPrepod(QString name1, QString academic1 ,  int salary1, int a);

int getkey();
int getnumbered();

int getstudentsize();
int getprepodsize();


QString getname1(int a);                //student
bool getscholarship(int a);
int getbirthday(int a);

QString getname2(int a);                //prepod
QString getacademic(int a);
int getsalary(int a);

void setMultiMap(int a,int b);

bool checkpair(int a,int b);

void save();
void load();

#endif // MAINWINDOW_H
