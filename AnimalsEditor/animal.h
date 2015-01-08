#ifndef ANIMAL_H
#define ANIMAL_H

#include "data.h"

#include <QString>
#include <map>
#include <vector>
#include <tuple>

class Animal : public Data
{
public:
    Animal();
    ~Animal();

    QString primaryType() const;
    void setPrimaryType(const QString &primaryType);

    QString secondaryType() const;
    void setSecondaryType(const QString &secondaryType);

    unsigned int baseHP() const;
    void setBaseHP(unsigned int baseHP);

    unsigned int baseAttack() const;
    void setBaseAttack(unsigned int baseAttack);

    unsigned int baseDefense() const;
    void setBaseDefense(unsigned int baseDefense);

    unsigned int baseSpeed() const;
    void setBaseSpeed(unsigned int baseSpeed);

    unsigned int baseSpecialAttack() const;
    void setBaseSpecialAttack(unsigned int baseSpecialAttack);

    unsigned int baseSpecialDefense() const;
    void setBaseSpecialDefense(unsigned int baseSpecialDefense);

    std::multimap<unsigned int, QString> moves() const;
    void setMoves(const std::multimap<unsigned int, QString> &moves);
    bool addMove(unsigned int, const QString &);
    bool deleteMove(unsigned int, const QString &);

    std::vector<std::tuple<QString, QString, unsigned int> > evolutions() const;
    void setEvolutions(const std::vector<std::tuple<QString, QString, unsigned int> > &evolutions);

    unsigned int baseXP() const;
    void setBaseXP(unsigned int baseXP);

private:

    QString m_primaryType;
    QString m_secondaryType;
    unsigned int m_baseHP;
    unsigned int m_baseAttack;
    unsigned int m_baseDefense;
    unsigned int m_baseSpeed;
    unsigned int m_baseSpecialAttack;
    unsigned int m_baseSpecialDefense;
    unsigned int m_baseXP;
    std::multimap<unsigned int, QString> m_moves;
    std::vector<std::tuple<QString, QString, unsigned int>> m_evolutions;

};

#endif // ANIMAL_H
