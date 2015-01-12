#include "animaldatabase.h"

#include <QFile>
#include <QIODevice>
#include <QtDebug>
#include <QXmlStreamReader>

#include <cassert>
#include <vector>
#include <tuple>

namespace db {

const QString k_path("../AnimalsEditor/data/animals.xml");
const QString k_name("animal");

AnimalDatabase::AnimalDatabase()
  : Database()
{
    parse();
}

AnimalDatabase::~AnimalDatabase()
{

}

const std::map<unsigned int, Animal> AnimalDatabase::getByID() const {

    std::map<unsigned int, Animal> map;

    for (const auto & p : m_data) {

        map.emplace(p.second.getID(), p.second);

    }

    return map;

}

bool AnimalDatabase::deleteData(const QString & name) {

    if (m_data.count(name) == 0) return false;

    const auto ID = m_data.at(name).getID();

    for (auto & a : m_data) {

        if (a.second.getID() > ID) a.second.setID(a.second.getID() - 1);

    }

    m_data.erase(name);

    return true;

}

bool AnimalDatabase::insertData(unsigned int ID, const Animal & data) {

    const auto map = getByID();

    if (ID != 1 && map.count(ID - 1) == 0) {
        return false;
    }

    for (auto & a : m_data) {

        if (a.second.getID() >= ID) a.second.setID(a.second.getID() + 1);

    }

    m_data.emplace(data.getName(), data);

    return true;

}

bool AnimalDatabase::save() {

    const auto dataByID = getByID();

    QFile file(k_path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qCritical() << "Could not open" << k_path;
        return false;
    }

    QXmlStreamWriter writer(&file);

    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeStartElement("animals");

    for (const auto & p : dataByID) {

        const auto data = p.second;
        writer.writeStartElement(k_name);
        writer.writeAttribute("id", QString::number(p.first));

        writer.writeStartElement("name");
        writer.writeCharacters(data.getName());
        writer.writeEndElement();

        {
            writer.writeStartElement("type");

            writer.writeStartElement("primary");
            writer.writeCharacters(data.primaryType());
            writer.writeEndElement();
            writer.writeStartElement("secondary");
            writer.writeCharacters(data.secondaryType());
            writer.writeEndElement();

            writer.writeEndElement();
        }

        {
            writer.writeStartElement("basestats");

            writer.writeStartElement("hp");
            writer.writeCharacters(QString::number(data.baseHP()));
            writer.writeEndElement();
            writer.writeStartElement("attack");
            writer.writeCharacters(QString::number(data.baseAttack()));
            writer.writeEndElement();
            writer.writeStartElement("defense");
            writer.writeCharacters(QString::number(data.baseDefense()));
            writer.writeEndElement();
            writer.writeStartElement("speed");
            writer.writeCharacters(QString::number(data.baseSpeed()));
            writer.writeEndElement();
            writer.writeStartElement("specialattack");
            writer.writeCharacters(QString::number(data.baseSpecialAttack()));
            writer.writeEndElement();
            writer.writeStartElement("specialdefense");
            writer.writeCharacters(QString::number(data.baseSpecialDefense()));
            writer.writeEndElement();
            writer.writeStartElement("xp");
            writer.writeCharacters(QString::number(data.baseXP()));
            writer.writeEndElement();

            writer.writeEndElement();
        }

        {
            writer.writeStartElement("moves");
            for (const auto & move : data.moves()) {

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
            for (const auto & evolution : data.evolutions()) {

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

    return true;

}

bool AnimalDatabase::parse() {

    QFile file(k_path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qCritical() << "Could not open" << k_path;
        return false;
    }

    QXmlStreamReader reader(&file);

    while (!reader.atEnd() && !reader.hasError()) {

        reader.readNext();
        if (reader.isStartElement() && reader.name() == k_name) {

            const auto ID = reader.attributes().value("id").toUInt();
            auto data = getData(reader);
            data.setID(ID);
//            m_data.insert(std::pair<QString, Animal>(data.getName(), data));
            m_data.emplace(data.getName(), data);

        }

    }

    return true;

}

const Animal AnimalDatabase::getData(QXmlStreamReader & reader) {

    assert(reader.name() == k_name);

    Animal animal;

    const auto attr = reader.attributes();
    if (!attr.hasAttribute("id")) {
        qWarning() << "Animal has no ID!";
        return animal;
    }

    while(!(reader.isEndElement() && reader.name() == k_name)) {

        reader.readNext();
        if (reader.isEndElement()) {
            continue;
        }

        auto name = reader.name();

        // name
        if (name == "name") {

            reader.readNext();
            if(!reader.isCharacters()) {

                qWarning() << "Name does not contain characters!";
                return animal;

            } else {

                animal.setName(reader.text().toString());

            }

        } else

        // type
        if (name == "type") {

            while(!(reader.isEndElement() && reader.name() == "type")) {

                reader.readNext();
                if (reader.isEndElement()) {
                    continue;
                }

                name = reader.name();

                if (name == "primary") {

                    reader.readNext();
                    if (!reader.isCharacters()) {

                        qWarning() << "Primary Type does not contain characters!";
                        return animal;

                    } else {

                        animal.setPrimaryType(reader.text().toString());

                    }

                } else if (name == "secondary") {

                    reader.readNext();
                    if (!reader.isCharacters() && !reader.text().isEmpty()) {

                        qWarning() << "Secondary Type does not contain characters!";
                        return animal;

                    } else {

                        animal.setSecondaryType(reader.text().toString());

                    }

                }

            }

        } else

        // basestats
        if (name == "basestats") {

            while(!(reader.isEndElement() && reader.name() == "basestats")) {

                reader.readNext();
                if (reader.isEndElement()) {
                    continue;
                }

                name = reader.name();

                if (name == "hp") {

                    reader.readNext();
                    if (!reader.isCharacters()) {

                        qWarning() << "HP does not contain characters!";
                        return animal;

                    } else {

                        animal.setBaseHP(reader.text().toUInt());

                    }

                } else if (name == "attack") {

                    reader.readNext();
                    if (!reader.isCharacters()) {

                        qWarning() << "Attack does not contain characters!";
                        return animal;

                    } else {

                        animal.setBaseAttack(reader.text().toUInt());

                    }

                } else if (name == "defense") {

                    reader.readNext();
                    if (!reader.isCharacters()) {

                        qWarning() << "Defense does not contain characters!";
                        return animal;

                    } else {

                        animal.setBaseDefense(reader.text().toUInt());

                    }

                } else if (name == "speed") {

                    reader.readNext();
                    if (!reader.isCharacters()) {

                        qWarning() << "Speed does not contain characters!";
                        return animal;

                    } else {

                        animal.setBaseSpeed(reader.text().toUInt());

                    }

                } else if (name == "specialattack") {

                    reader.readNext();
                    if (!reader.isCharacters()) {

                        qWarning() << "Special Attack does not contain characters!";
                        return animal;

                    } else {

                        animal.setBaseSpecialAttack(reader.text().toUInt());

                    }

                } else if (name == "specialdefense") {

                    reader.readNext();
                    if (!reader.isCharacters()) {

                        qWarning() << "Special Defense does not contain characters!";
                        return animal;

                    } else {

                        animal.setBaseSpecialDefense(reader.text().toUInt());

                    }

                } else if (name == "xp") {

                    reader.readNext();
                    if (!reader.isCharacters()) {

                        qWarning() << "base XP does not contain characters!";
                        return animal;

                    } else {

                        animal.setBaseXP(reader.text().toUInt());

                    }

                }

            }

        } else

        // moves
        if (name == "moves") {

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

                                qWarning() << "Move Name does not contain characters!";
                                return animal;

                            } else {

                                moveName = reader.text().toString();

                            }

                        } else if (name == "level") {

                            reader.readNext();
                            if (!reader.isCharacters()) {

                                qWarning() << "Move Level does not contain characters!";
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

        } else

        // evolutions
        if (name == "evolutions") {

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

                                qWarning() << "Evolution Name does not contain characters!";
                                return animal;

                            } else {

                                evolutionName = reader.text().toString();

                            }

                        } else if (name == "method") {

                            reader.readNext();
                            if (!reader.isCharacters()) {

                                qWarning() << "Evolution Method does not contain characters!";
                                return animal;

                            } else {

                                evolutionMethod = reader.text().toString();

                            }

                        } else if (name == "value") {

                            reader.readNext();
                            if (!reader.isCharacters()) {

                                qWarning() << "Evolution Value does not contain characters!";
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

} // namespace db
