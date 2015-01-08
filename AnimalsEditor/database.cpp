#include "database.h"

#include <QFile>
#include <QMessageBox>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

#include <iostream>
#include <cassert>

const std::string k_animalPath("../AnimalsEditor/data/animals.xml");
const std::string k_typePath("../AnimalsEditor/data/types.xml");
const std::string k_movePath("../AnimalsEditor/data/moves.xml");

Database::Database()
{

    parseAnimals();
    parseTypes();
    parseMoves();

}

const std::map<unsigned int, Animal> Database::getAnimalsByID() const
{
    std::map<unsigned int, Animal> map;
    for (const auto & p : m_animals) {
        map.emplace(p.second.getID(), p.second);
    }
    return map;
}

const std::map<unsigned int, Move> Database::getMovesByID() const
{
    std::map<unsigned int, Move> map;
    for (const auto & p : m_moves) {
        map.emplace(p.second.getID(), p.second);
    }
    return map;
}

bool Database::deleteMove(const QString & name)
{
    if (m_moves.count(name) == 0) return false;

    const auto ID = m_moves.at(name).getID();
    for (auto & a : m_moves) {
        if (a.second.getID() > ID) a.second.setID(a.second.getID() - 1);
    }
    m_moves.erase(name);

    return true;
}

bool Database::deleteAnimal(const QString & name)
{

    if (m_animals.count(name) == 0) return false;

    const auto ID = m_animals.at(name).getID();
    for (auto & a : m_animals) {
        if (a.second.getID() > ID) a.second.setID(a.second.getID() - 1);
    }
    m_animals.erase(name);

    return true;
}

bool Database::insertAnimal(unsigned int ID, const Animal & animal)
{
    const auto map = getAnimalsByID();
    if (ID != 1 && map.count(ID - 1) == 0) return false;

    for (auto & a : m_animals) {
        if (a.second.getID() >= ID) a.second.setID(a.second.getID() + 1);
    }

    m_animals.emplace(animal.getName(), animal);

    return true;
}

bool Database::insertMove(unsigned int ID, const Move & move)
{
    const auto map = getMovesByID();
    if (ID != 1 && map.count(ID - 1) == 0) return false;

    for (auto & a : m_moves) {
        if (a.second.getID() >= ID) a.second.setID(a.second.getID() + 1);
    }

    m_moves.emplace(move.getName(), move);

    return true;
}

const std::map<unsigned int, Type> Database::getTypesByID() const
{
    std::map<unsigned int, Type> map;
    for (const auto & p : m_types) {
        map.emplace(p.second.getID(), p.second);
    }
    return map;
}

bool Database::deleteType(const QString & name)
{
    if (m_types.count(name) == 0) return false;

    const auto ID = m_types.at(name).getID();
    for (auto & a : m_types) {
        if (a.second.getID() > ID) a.second.setID(a.second.getID() - 1);
    }
    m_types.erase(name);

    return true;
}

bool Database::insertType(unsigned int ID, const Type & type)
{
    const auto map = getTypesByID();
    if (ID != 1 && map.count(ID - 1) == 0) return false;

    for (auto & a : m_types) {
        if (a.second.getID() >= ID) a.second.setID(a.second.getID() + 1);
    }

    m_types.emplace(type.getName(), type);

    return true;
}

const Animal Database::getAnimal(QXmlStreamReader & reader) {

    assert(reader.name() == "animal");

    Animal animal;

    const auto attr = reader.attributes();
    if (!attr.hasAttribute("id")) {
        std::cout << "Animal has no ID!" << std::endl;
        return animal;
    }

    while(!(reader.isEndElement() && reader.name() == "animal")) {

        reader.readNext();

        if (reader.isEndElement()) {
            continue;
        }

        auto name = reader.name();

        if (name == "name") {
            reader.readNext();
            if(!reader.isCharacters()) {
                std::cout << "Name does not contain characters!" << std::endl;
                return animal;
            } else {
                animal.setName(reader.text().toString());
            }
        } else if (name == "primary") {
            reader.readNext();
            if (!reader.isCharacters()) {
                std::cout << "Primary Type does not contain characters!" << std::endl;
                return animal;
            } else {
                animal.setPrimaryType(reader.text().toString());
            }
        } else if (name == "secondary") {
            reader.readNext();
            if (!reader.isCharacters()) {
                if (reader.text().toString() != "") {
                    std::cout << "Secondary Type does not contain characters!" << std::endl;
                    return animal;
                }
            } else {
                animal.setSecondaryType(reader.text().toString());
            }
        } else if (name == "hp") {
            reader.readNext();
            if (!reader.isCharacters()) {
                std::cout << "HP does not contain characters!" << std::endl;
                return animal;
            } else {
                animal.setBaseHP(reader.text().toUInt());
            }
        } else if (name == "attack") {
            reader.readNext();
            if (!reader.isCharacters()) {
                std::cout << "Attack does not contain characters!" << std::endl;
                return animal;
            } else {
                animal.setBaseAttack(reader.text().toUInt());
            }
        } else if (name == "defense") {
            reader.readNext();
            if (!reader.isCharacters()) {
                std::cout << "Defense does not contain characters!" << std::endl;
                return animal;
            } else {
                animal.setBaseDefense(reader.text().toUInt());
            }
        } else if (name == "speed") {
            reader.readNext();
            if (!reader.isCharacters()) {
                std::cout << "Speed does not contain characters!" << std::endl;
                return animal;
            } else {
                animal.setBaseSpeed(reader.text().toUInt());
            }
        } else if (name == "specialattack") {
            reader.readNext();
            if (!reader.isCharacters()) {
                std::cout << "Special Attack does not contain characters!" << std::endl;
                return animal;
            } else {
                animal.setBaseSpecialAttack(reader.text().toUInt());
            }
        } else if (name == "specialdefense") {
            reader.readNext();
            if (!reader.isCharacters()) {
                std::cout << "Special Defense does not contain characters!" << std::endl;
                return animal;
            } else {
                animal.setBaseSpecialDefense(reader.text().toUInt());
            }
        } else if (name == "xp") {
            reader.readNext();
            if (!reader.isCharacters()) {
                std::cout << "base XP does not contain characters!" << std::endl;
                return animal;
            } else {
                animal.setBaseXP(reader.text().toUInt());
            }
        } else if (name == "moves") {

            std::multimap<unsigned int, QString> moves;

            while(!(reader.isEndElement() && reader.name() == "moves")) {

                reader.readNext();

                if (reader.isEndElement()) {
                    continue;
                }

                name = reader.name();

                if (name == "move") {

                    QString moveName;
                    unsigned int moveLevel;

                    while(!(reader.isEndElement() && reader.name() == "move")) {

                        reader.readNext();

                        if (reader.isEndElement()) {
                            continue;
                        }

                        name = reader.name();

                        if (name == "name") {
                            reader.readNext();
                            if (!reader.isCharacters()) {
                                std::cout << "Move Name does not contain characters!" << std::endl;
                                return animal;
                            } else {
                                moveName = reader.text().toString();
                            }
                        } else if (name == "level") {
                            reader.readNext();
                            if (!reader.isCharacters()) {
                                std::cout << "Move Level does not contain characters!" << std::endl;
                                return animal;
                            } else {
                                moveLevel = reader.text().toUInt();
                            }
                        }

                    }

                    moves.emplace(moveLevel, moveName);

                }

            }

            animal.setMoves(moves);

        } else if (name == "evolutions") {

            std::vector<std::tuple<QString, QString, unsigned int>> evolutions;

            while(!(reader.isEndElement() && reader.name() == "evolutions")) {

                reader.readNext();

                if (reader.isEndElement()) {
                    continue;
                }

                name = reader.name();

                if (name == "evolution") {

                    QString evolutionName;
                    QString evolutionMethod;
                    unsigned int evolutionValue;

                    while(!(reader.isEndElement() && reader.name() == "evolution")) {

                        reader.readNext();

                        if (reader.isEndElement()) {
                            continue;
                        }

                        name = reader.name();

                        if (name == "name") {
                            reader.readNext();
                            if (!reader.isCharacters()) {
                                std::cout << "Evolution Name does not contain characters!" << std::endl;
                                return animal;
                            } else {
                                evolutionName = reader.text().toString();
                            }
                        } else if (name == "method") {
                            reader.readNext();
                            if (!reader.isCharacters()) {
                                std::cout << "Evolution Method does not contain characters!" << std::endl;
                                return animal;
                            } else {
                                evolutionMethod = reader.text().toString();
                            }
                        } else if (name == "value") {
                            reader.readNext();
                            if (!reader.isCharacters()) {
                                std::cout << "Evolution Value does not contain characters!" << std::endl;
                                return animal;
                            } else {
                                evolutionValue = reader.text().toUInt();
                            }
                        }

                    }

                    evolutions.emplace_back(evolutionName, evolutionMethod, evolutionValue);

                }

            }

            animal.setEvolutions(evolutions);

        }


    }

    return animal;

}

void Database::saveAnimals()
{

    std::map<unsigned int, Animal> animals;
    for (const auto & p : m_animals) {
        animals.emplace(p.second.getID(), p.second);
    }

    QFile file(k_animalPath.c_str());
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        std::cout << "Could not open " << k_animalPath << std::endl;
        return;
    }

    QXmlStreamWriter writer(&file);

    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeStartElement("animals");

    for (const auto & p : animals) {
        const auto animal = p.second;
        writer.writeStartElement("animal");
        writer.writeAttribute("id", QString::number(p.first));

        writer.writeStartElement("name");
        writer.writeCharacters(p.second.getName());
        writer.writeEndElement();

        {
            writer.writeStartElement("type");

            writer.writeStartElement("primary");
            writer.writeCharacters(p.second.primaryType());
            writer.writeEndElement();
            writer.writeStartElement("secondary");
            writer.writeCharacters(p.second.secondaryType());
            writer.writeEndElement();

            writer.writeEndElement();
        }

        {
            writer.writeStartElement("basestats");

            writer.writeStartElement("hp");
            writer.writeCharacters(QString::number(p.second.baseHP()));
            writer.writeEndElement();
            writer.writeStartElement("attack");
            writer.writeCharacters(QString::number(p.second.baseAttack()));
            writer.writeEndElement();
            writer.writeStartElement("defense");
            writer.writeCharacters(QString::number(p.second.baseDefense()));
            writer.writeEndElement();
            writer.writeStartElement("speed");
            writer.writeCharacters(QString::number(p.second.baseSpeed()));
            writer.writeEndElement();
            writer.writeStartElement("specialattack");
            writer.writeCharacters(QString::number(p.second.baseSpecialAttack()));
            writer.writeEndElement();
            writer.writeStartElement("specialdefense");
            writer.writeCharacters(QString::number(p.second.baseSpecialDefense()));
            writer.writeEndElement();
            writer.writeStartElement("xp");
            writer.writeCharacters(QString::number(p.second.baseXP()));
            writer.writeEndElement();

            writer.writeEndElement();
        }

        {
            writer.writeStartElement("moves");
            for (const auto & move : p.second.moves()) {
                writer.writeStartElement("move");

                writer.writeStartElement("name");
                writer.writeCharacters(move.second);
                writer.writeEndElement();
                writer.writeStartElement("level");
                writer.writeCharacters(QString::number(move.first));
                writer.writeEndElement();

                writer.writeEndElement();
            }
            writer.writeEndElement();
        }

        {
            writer.writeStartElement("evolutions");
            for (const auto & evolution : p.second.evolutions()) {
                writer.writeStartElement("evolution");

                writer.writeStartElement("name");
                writer.writeCharacters(std::get<0>(evolution));
                writer.writeEndElement();
                writer.writeStartElement("method");
                writer.writeCharacters(std::get<1>(evolution));
                writer.writeEndElement();
                writer.writeStartElement("value");
                writer.writeCharacters(QString::number(std::get<2>(evolution)));
                writer.writeEndElement();

                writer.writeEndElement();
            }
            writer.writeEndElement();
        }

        writer.writeEndElement();

    }

    writer.writeEndElement();
    writer.writeEndDocument();

}

void Database::parseAnimals() {

    QFile file(k_animalPath.c_str());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cout << "Could not open " << k_animalPath << std::endl;
        return;
    }

    QXmlStreamReader reader(&file);

    while (!reader.atEnd() && !reader.hasError()) {

        reader.readNext();
        if (reader.isStartElement() && reader.name() == "animal") {

            const auto ID = reader.attributes().value("id").toUInt();
            auto animal = getAnimal(reader);
            animal.setID(ID);
            m_animals.emplace(animal.getName(), animal);

        }

    }

}

const Type Database::getType(QXmlStreamReader & reader) {

    assert(reader.name() == "type");

    Type type;

    auto attr = reader.attributes();
    if (!attr.hasAttribute("id")) {

        std::cout << "Type has no ID!" << std::endl;
        return type;

    }

    std::map<QString, EffectiveType> effectMap;

    while(!(reader.isEndElement() && reader.name() == "type")) {

        reader.readNext();

        if (reader.isEndElement()) {
            continue;
        }

        const auto name = reader.name();

        if (name == "name") {

            reader.readNext();

            if(!reader.isCharacters()) {

                std::cout << "Name does not contain characters!" << std::endl;
                return type;

            } else {

                type.setName(reader.text().toString());

            }

        } else if (name == "effectiveness") {

            attr = reader.attributes();
            if (!attr.hasAttribute("name")) {

                std::cout << "Effectiveness has no name!" << std::endl;
                return type;

            }

            reader.readNext();

            if(!reader.isCharacters()) {

                std::cout << "Effectiveness does not contain characters!" << std::endl;
                return type;

            } else {

                const auto name = attr.value("name").toString();
                const auto effect = reader.text().toString();
                effectMap.emplace(name, Type::stringToType(effect));

            }

        }

    }

    type.setEffectivenesses(effectMap);

    return type;

}

void Database::saveTypes()
{

    std::map<unsigned int, Type> types;
    for (const auto & p : m_types) {
        types.emplace(p.second.getID(), p.second);
    }

    QFile file(k_typePath.c_str());
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        std::cout << "Could not open " << k_typePath << std::endl;
        return;
    }

    QXmlStreamWriter writer(&file);

    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeStartElement("types");

    for (const auto & p : types) {
        const auto type = p.second;
        writer.writeStartElement("type");
        writer.writeAttribute("id", QString::number(p.first));

        writer.writeStartElement("name");
        writer.writeCharacters(p.second.getName());
        writer.writeEndElement();

        for (const auto & effect : type.effectivenesses()) {

            writer.writeStartElement("effectiveness");
            writer.writeAttribute("name", effect.first);
            writer.writeCharacters(Type::typeToString(effect.second));
            writer.writeEndElement();

        }

        writer.writeEndElement();
    }

    writer.writeEndElement();
    writer.writeEndDocument();
}

void Database::parseTypes() {

    QFile file(k_typePath.c_str());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cout << "Could not open " << k_typePath << std::endl;
        return;
    }

    QXmlStreamReader reader(&file);

    while (!reader.atEnd() && !reader.hasError()) {

        reader.readNext();
        if (reader.isStartElement() && reader.name() == "type") {

            const auto ID = reader.attributes().value("id").toUInt();
            auto type = getType(reader);
            type.setID(ID);
            const auto name = type.getName();
            m_types.emplace(name, type);

        }

    }

}

const Move Database::getMove(QXmlStreamReader & reader) {

    assert(reader.name() == "move");

    Move move;

    auto attr = reader.attributes();
    if (!attr.hasAttribute("id")) {

        std::cout << "Type has no ID!" << std::endl;
        return move;

    }

    while(!(reader.isEndElement() && reader.name() == "move")) {

        reader.readNext();

        if (reader.isEndElement()) {
            continue;
        }

        const auto name = reader.name();

        if (name == "name") {

            reader.readNext();

            if(!reader.isCharacters()) {

                std::cout << "Name does not contain characters!" << std::endl;
                return move;

            } else {

                move.setName(reader.text().toString());

            }

        } else if (name == "basedamage") {

            reader.readNext();

            if(!reader.isCharacters()) {

                std::cout << "Base Damage does not contain characters!" << std::endl;
                return move;

            } else {

                move.setBaseDamage(reader.text().toUInt());

            }

        } else if (name == "type") {

            reader.readNext();

            if(!reader.isCharacters()) {

                std::cout << "Type does not contain characters!" << std::endl;
                return move;

            } else {

                move.setType(reader.text().toString());

            }

        } else if (name == "category") {

            reader.readNext();

            if(!reader.isCharacters()) {

                std::cout << "Category does not contain characters!" << std::endl;
                return move;

            } else {

                move.setCategory(reader.text().toString());

            }

        } else if (name == "accuracy") {

            reader.readNext();

            if(!reader.isCharacters()) {

                std::cout << "Accuracy does not contain characters!" << std::endl;
                return move;

            } else {

                move.setAccuracy(reader.text().toUInt());

            }

        } else if (name == "priority") {

            reader.readNext();

            if(!reader.isCharacters()) {

                std::cout << "Priority does not contain characters!" << std::endl;
                return move;

            } else {

                move.setPriority(reader.text().toInt());

            }

        }

    }

    return move;

}

void Database::saveMoves()
{

    auto movesByID = getMovesByID();

    QFile file(k_movePath.c_str());
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        std::cout << "Could not open " << k_movePath << std::endl;
        return;
    }

    QXmlStreamWriter writer(&file);

    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeStartElement("moves");

    for (const auto & p : movesByID) {

        const auto move = p.second;
        writer.writeStartElement("move");
        writer.writeAttribute("id", QString::number(p.first));

        writer.writeStartElement("name");
        writer.writeCharacters(p.second.getName());
        writer.writeEndElement();

        writer.writeStartElement("basedamage");
        writer.writeCharacters(QString::number(p.second.getBaseDamage()));
        writer.writeEndElement();

        writer.writeStartElement("type");
        writer.writeCharacters(p.second.getType());
        writer.writeEndElement();

        writer.writeStartElement("category");
        writer.writeCharacters(p.second.getCategory());
        writer.writeEndElement();

        writer.writeStartElement("accuracy");
        writer.writeCharacters(QString::number(p.second.getAccuracy()));
        writer.writeEndElement();

        writer.writeStartElement("priority");
        writer.writeCharacters(QString::number(p.second.getPriority()));
        writer.writeEndElement();

        writer.writeEndElement();
    }

    writer.writeEndElement();
    writer.writeEndDocument();

}

void Database::parseMoves() {

    QFile file(k_movePath.c_str());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cout << "Could not open " << k_movePath << std::endl;
        return;
    }

    QXmlStreamReader reader(&file);

    while (!reader.atEnd() && !reader.hasError()) {

        reader.readNext();
        if (reader.isStartElement() && reader.name() == "move") {

            const auto ID = reader.attributes().value("id").toUInt();
            auto move = getMove(reader);
            move.setID(ID);
            const auto name = move.getName();
            m_moves.emplace(name, move);

        }

    }

}
