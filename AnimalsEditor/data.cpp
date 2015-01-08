#include "data.h"

Data::Data()
{

}

Data::~Data()
{

}

unsigned int Data::getID() const
{
    return m_ID;
}

void Data::setID(unsigned int ID)
{
    m_ID = ID;
}

QString Data::getName() const
{
    return m_name;
}

void Data::setName(const QString &name)
{
    m_name = name;
}



