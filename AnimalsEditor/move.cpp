#include "move.h"

Move::Move()
  : m_baseDamage{0},
    m_type{"Normal"},
    m_category{"Status"},
    m_accuracy{100},
    m_priority{0}
{

}

Move::~Move()
{

}
unsigned int Move::getBaseDamage() const
{
    return m_baseDamage;
}

void Move::setBaseDamage(unsigned int baseDamage)
{
    m_baseDamage = baseDamage;
}
QString Move::getType() const
{
    return m_type;
}

void Move::setType(const QString &type)
{
    m_type = type;
}
QString Move::getCategory() const
{
    return m_category;
}

void Move::setCategory(const QString &category)
{
    m_category = category;
}
unsigned int Move::getAccuracy() const
{
    return m_accuracy;
}

void Move::setAccuracy(unsigned int accuracy)
{
    m_accuracy = accuracy;
}
int Move::getPriority() const
{
    return m_priority;
}

void Move::setPriority(int priority)
{
    m_priority = priority;
}






