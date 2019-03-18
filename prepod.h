#ifndef PREPOD_H
#define PREPOD_H
#include "header.h"

class Prepod
{
public:
    QString m_name;
    QString m_academic;
    int m_salary;
    int id;
    Prepod(QString name="", QString academic ="",  int salary=0);
    Prepod(const Prepod &prepod);
    void setname(QString name)
    {
        m_name=name;
    }

    void setacademic(QString academic)
    {
        m_academic=academic;
    }
    void setsalary(int salary)
    {
        m_salary=salary;
    }

    QString getname()
    {
        return m_name;
    }
    QString getacademic()
    {
        return m_academic;
    }
    int getsalary()
    {
        return m_salary;
    }
};

#endif // PREPOD_H
