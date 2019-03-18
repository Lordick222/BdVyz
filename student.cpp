#include "student.h"

Student::Student(QString name, bool scholarship,   int birthday)
    : m_name(name),m_scholarship(scholarship),m_birthday(birthday)
{
}

Student::Student(const Student &student)
    : 	m_name(student.m_name),
    m_scholarship(student.m_scholarship),
    m_birthday(student.m_birthday)
{
}
