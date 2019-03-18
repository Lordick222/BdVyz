#ifndef STUDENT_H
#define STUDENT_H
#include "header.h"

class Student
{
public:
    QString m_name;
    bool m_scholarship;
    int m_birthday;
    Student(QString name="", bool scholarship = 0, int birthday =0 );
    Student(const Student &student);
    void setname(QString name)
    {
        m_name=name;
    }

    void setscholarship(bool scholarship)
    {
        m_scholarship=scholarship;
    }

    void setbirthday(int birthday)
    {
        m_birthday=birthday;
    }

    QString getname()
    {
        return m_name;
    }
    int getbirthday()
    {
        return m_birthday;
    }
    bool getscholarship()
    {
        return m_scholarship;
    }
};




#endif // STUDENT_H
