#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <map>

#include "type.h"
#include "animal.h"
#include "move.h"

class QXmlStreamReader;

namespace db {

class Database
{

public:

    Database();
    virtual ~Database() {}

//    const std::map<QString, Animal> & getAnimals() const { return m_animals; }
//    const std::map<unsigned int, Animal> getAnimalsByID() const;
//    void setAnimals(const std::map<QString, Animal> & animals) { m_animals = animals; }
//    bool deleteAnimal(const QString &);
//    bool insertAnimal(unsigned int, const Animal &);

    const std::map<QString, Type> & getTypes() const { return m_types; }
    const std::map<unsigned int, Type> getTypesByID() const;
    void setTypes(const std::map<QString, Type> & types) { m_types = types; }
    bool deleteType(const QString &);
    bool insertType(unsigned int, const Type &);

    const std::map<QString, Move> & getMoves() const { return m_moves; }
    const std::map<unsigned int, Move> getMovesByID() const;
    void setMoves(const std::map<QString, Move> & moves) { m_moves = moves; }
    bool deleteMove(const QString &);
    bool insertMove(unsigned int, const Move &);

    void saveTypes();
//    void saveAnimals();
    void saveMoves();
    virtual QString test() const { return "Database"; }

protected:

   // virtual void parse() = 0;


private:

//    std::map<QString, Animal> m_animals;
    std::map<QString, Type> m_types;
    std::map<QString, Move> m_moves;

//    void parseAnimals();
//    const Animal getAnimal(QXmlStreamReader &);

    void parseTypes();
    const Type getType(QXmlStreamReader &);

    void parseMoves();
    const Move getMove(QXmlStreamReader &);

};

} // namespace db

#endif // DATABASE_H
