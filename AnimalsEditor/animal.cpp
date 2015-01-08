#include "animal.h"

#include <QDebug>

Animal::Animal()
  : m_primaryType{"Normal"},
    m_baseHP{1},
    m_baseAttack{1},
    m_baseDefense{1},
    m_baseSpeed{1},
    m_baseSpecialAttack{1},
    m_baseSpecialDefense{1},
    m_baseXP{1}
{

}

Animal::~Animal()
{

}

QString Animal::primaryType() const
{
    return m_primaryType;
}

void Animal::setPrimaryType(const QString &primaryType)
{
    m_primaryType = primaryType;
}
QString Animal::secondaryType() const
{
    return m_secondaryType;
}

void Animal::setSecondaryType(const QString &secondaryType)
{
    m_secondaryType = secondaryType;
}
unsigned int Animal::baseHP() const
{
    return m_baseHP;
}

void Animal::setBaseHP(unsigned int baseHP)
{
    m_baseHP = baseHP;
}

unsigned int Animal::baseAttack() const
{
    return m_baseAttack;
}

void Animal::setBaseAttack(unsigned int baseAttack)
{
    m_baseAttack = baseAttack;
}
unsigned int Animal::baseDefense() const
{
    return m_baseDefense;
}

void Animal::setBaseDefense(unsigned int baseDefense)
{
    m_baseDefense = baseDefense;
}
unsigned int Animal::baseSpeed() const
{
    return m_baseSpeed;
}

void Animal::setBaseSpeed(unsigned int baseSpeed)
{
    m_baseSpeed = baseSpeed;
}
unsigned int Animal::baseSpecialAttack() const
{
    return m_baseSpecialAttack;
}

void Animal::setBaseSpecialAttack(unsigned int baseSpecialAttack)
{
    m_baseSpecialAttack = baseSpecialAttack;
}
unsigned int Animal::baseSpecialDefense() const
{
    return m_baseSpecialDefense;
}

void Animal::setBaseSpecialDefense(unsigned int baseSpecialDefense)
{
    m_baseSpecialDefense = baseSpecialDefense;
}
std::multimap<unsigned int, QString> Animal::moves() const
{
    return m_moves;
}

void Animal::setMoves(const std::multimap<unsigned int, QString> &moves)
{
    m_moves = moves;
}

bool Animal::addMove(unsigned int lvl, const QString & name)
{
qDebug() << "lvl" << lvl << "name" << name;
    const auto itPair = m_moves.equal_range(lvl);
    for (auto it = std::get<0>(itPair); it != std::get<1>(itPair); ++it) {
        qDebug() << (*it).second;
        if ((*it).second == name) return false;
    }

    m_moves.emplace(lvl, name);
    return true;

}

bool Animal::deleteMove(unsigned int lvl, const QString & name)
{
    const auto itPair = m_moves.equal_range(lvl);
    for (auto it = std::get<0>(itPair); it != std::get<1>(itPair); ++it) {
        if ((*it).second == name) {
            m_moves.erase(it);
            return true;
        }
    }
    return false;
}

std::vector<std::tuple<QString, QString, unsigned int> > Animal::evolutions() const
{
    return m_evolutions;
}

void Animal::setEvolutions(const std::vector<std::tuple<QString, QString, unsigned int> > &evolutions)
{
    m_evolutions = evolutions;
}

unsigned int Animal::baseXP() const
{
    return m_baseXP;
}

void Animal::setBaseXP(unsigned int baseXP)
{
    m_baseXP = baseXP;
}











