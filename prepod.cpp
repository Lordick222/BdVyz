#include "prepod.h"

Prepod::Prepod(QString name, QString academic ,  int salary )
    : m_name(name),m_academic(academic),m_salary(salary)
{
}
Prepod::Prepod(const Prepod &prepod)
    : 	m_name(prepod.m_name),
    m_academic(prepod.m_academic),
    m_salary(prepod.m_salary)
{
}
