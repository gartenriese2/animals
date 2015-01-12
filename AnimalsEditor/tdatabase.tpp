#include <QFile>
#include <QIODevice>
#include <QtDebug>
#include <QXmlStreamReader>

#include <cassert>

namespace db {

template <typename T>
TDatabase<T>::TDatabase() {
    parse();
}

template <typename T>
TDatabase<T>::~TDatabase() {

}

template <typename T>
auto TDatabase<T>::getByID() -> std::map<unsigned int, T> const {

    std::map<unsigned int, T> map;

    for (const auto & p : m_data) {

        map.emplace(p.second.getID(), p.second);

    }

    return map;

}

template <typename T>
bool TDatabase<T>::deleteData(const QString & name) {

    if (m_data.count(name) == 0) {
        return false;
    }

    const auto ID = m_data.at(name).getID();

    for (auto & a : m_data) {

        if (a.second.getID() > ID) {
            a.second.setID(a.second.getID() - 1);
        }

    }

    m_data.erase(name);

    return true;

}

template <typename T>
bool TDatabase<T>::insertData(unsigned int ID, const T & data) {

    const auto map = getByID();

    if (ID != 1 && map.count(ID - 1) == 0) {
        return false;
    }

    for (auto & a : m_data) {

        if (a.second.getID() >= ID) {
            a.second.setID(a.second.getID() + 1);
        }

    }

    m_data.emplace(data.getName(), data);

    return true;

}

/*
 *
 *  Moves
 *
 */

const QString k_movePath("../AnimalsEditor/data/moves.xml");

template <>
inline bool TDatabase<Move>::save() {

    const auto dataByID = getByID();

    QFile file(k_movePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qCritical() << "Could not open " << k_movePath;
        return false;
    }

    QXmlStreamWriter writer(&file);

    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeStartElement("moves");

    for (const auto & p : dataByID) {

        const auto data = p.second;
        writer.writeStartElement("move");
        writer.writeAttribute("id", QString::number(p.first));

        writer.writeStartElement("name");
        writer.writeCharacters(data.getName());
        writer.writeEndElement();

        writer.writeStartElement("basedamage");
        writer.writeCharacters(QString::number(data.getBaseDamage()));
        writer.writeEndElement();

        writer.writeStartElement("type");
        writer.writeCharacters(data.getType());
        writer.writeEndElement();

        writer.writeStartElement("category");
        writer.writeCharacters(data.getCategory());
        writer.writeEndElement();

        writer.writeStartElement("accuracy");
        writer.writeCharacters(QString::number(data.getAccuracy()));
        writer.writeEndElement();

        writer.writeStartElement("priority");
        writer.writeCharacters(QString::number(data.getPriority()));
        writer.writeEndElement();

        writer.writeEndElement();

    }

    writer.writeEndElement();
    writer.writeEndDocument();

    return true;

}

template <>
inline auto TDatabase<Move>::getData(QXmlStreamReader & reader) -> Move const {

    assert(reader.name() == "move");

    Move data;

    auto attr = reader.attributes();
    if (!attr.hasAttribute("id")) {

        qWarning() << "Move has no ID!";
        return data;

    }

    while(!(reader.isEndElement() && reader.name() == "move")) {

        reader.readNext();
        if (reader.isEndElement()) {
            continue;
        }

        const auto name = reader.name();

        // name
        if (name == "name") {

            reader.readNext();
            if(!reader.isCharacters()) {

                qWarning() << "Name does not contain characters!";
                return data;

            } else {

                data.setName(reader.text().toString());

            }

        } else

        // basedamage
        if (name == "basedamage") {

            reader.readNext();
            if(!reader.isCharacters()) {

                qWarning() << "Base Damage does not contain characters!";
                return data;

            } else {

                data.setBaseDamage(reader.text().toUInt());

            }

        } else

        // type
        if (name == "type") {

            reader.readNext();
            if(!reader.isCharacters()) {

                qWarning() << "Type does not contain characters!";
                return data;

            } else {

                data.setType(reader.text().toString());

            }

        } else

        // category
        if (name == "category") {

            reader.readNext();
            if(!reader.isCharacters()) {

                qWarning() << "Category does not contain characters!";
                return data;

            } else {

                data.setCategory(reader.text().toString());

            }

        } else

        // accuracy
        if (name == "accuracy") {

            reader.readNext();
            if(!reader.isCharacters()) {

                qWarning() << "Accuracy does not contain characters!";
                return data;

            } else {

                data.setAccuracy(reader.text().toUInt());

            }

        } else

        // priority
        if (name == "priority") {

            reader.readNext();
            if(!reader.isCharacters()) {

                qWarning() << "Priority does not contain characters!";
                return data;

            } else {

                data.setPriority(reader.text().toInt());

            }

        }

    }

    return data;

}

template <>
inline bool TDatabase<Move>::parse() {

    QFile file(k_movePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qCritical() << "Could not open" << k_movePath;
        return false;
    }

    fillData(file, "move");

    return true;

}

/*
 *
 *  Animals
 *
 */

const QString k_animalPath("../AnimalsEditor/data/animals.xml");

template <>
inline bool TDatabase<Animal>::save() {

    const auto dataByID = getByID();

    QFile file(k_animalPath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qCritical() << "Could not open" << k_animalPath;
        return false;
    }

    QXmlStreamWriter writer(&file);

    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeStartElement("animals");

    for (const auto & p : dataByID) {

        const auto data = p.second;
        writer.writeStartElement("animal");
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

template <>
inline auto TDatabase<Animal>::getData(QXmlStreamReader & reader) -> Animal const {

    assert(reader.name() == "animal");

    Animal data;

    const auto attr = reader.attributes();
    if (!attr.hasAttribute("id")) {
        qWarning() << "Animal has no ID!";
        return data;
    }

    while(!(reader.isEndElement() && reader.name() == "animal")) {

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
                return data;

            } else {

                data.setName(reader.text().toString());

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
                        return data;

                    } else {

                        data.setPrimaryType(reader.text().toString());

                    }

                } else if (name == "secondary") {

                    reader.readNext();
                    if (!reader.isCharacters() && !reader.text().isEmpty()) {

                        qWarning() << "Secondary Type does not contain characters!";
                        return data;

                    } else {

                        data.setSecondaryType(reader.text().toString());

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
                        return data;

                    } else {

                        data.setBaseHP(reader.text().toUInt());

                    }

                } else if (name == "attack") {

                    reader.readNext();
                    if (!reader.isCharacters()) {

                        qWarning() << "Attack does not contain characters!";
                        return data;

                    } else {

                        data.setBaseAttack(reader.text().toUInt());

                    }

                } else if (name == "defense") {

                    reader.readNext();
                    if (!reader.isCharacters()) {

                        qWarning() << "Defense does not contain characters!";
                        return data;

                    } else {

                        data.setBaseDefense(reader.text().toUInt());

                    }

                } else if (name == "speed") {

                    reader.readNext();
                    if (!reader.isCharacters()) {

                        qWarning() << "Speed does not contain characters!";
                        return data;

                    } else {

                        data.setBaseSpeed(reader.text().toUInt());

                    }

                } else if (name == "specialattack") {

                    reader.readNext();
                    if (!reader.isCharacters()) {

                        qWarning() << "Special Attack does not contain characters!";
                        return data;

                    } else {

                        data.setBaseSpecialAttack(reader.text().toUInt());

                    }

                } else if (name == "specialdefense") {

                    reader.readNext();
                    if (!reader.isCharacters()) {

                        qWarning() << "Special Defense does not contain characters!";
                        return data;

                    } else {

                        data.setBaseSpecialDefense(reader.text().toUInt());

                    }

                } else if (name == "xp") {

                    reader.readNext();
                    if (!reader.isCharacters()) {

                        qWarning() << "base XP does not contain characters!";
                        return data;

                    } else {

                        data.setBaseXP(reader.text().toUInt());

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
                                return data;

                            } else {

                                moveName = reader.text().toString();

                            }

                        } else if (name == "level") {

                            reader.readNext();
                            if (!reader.isCharacters()) {

                                qWarning() << "Move Level does not contain characters!";
                                return data;

                            } else {

                                moveLevel = reader.text().toUInt();

                            }

                        }

                    }

                    moves.emplace(moveLevel, moveName);

                }

            }

            data.setMoves(moves);

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
                                return data;

                            } else {

                                evolutionName = reader.text().toString();

                            }

                        } else if (name == "method") {

                            reader.readNext();
                            if (!reader.isCharacters()) {

                                qWarning() << "Evolution Method does not contain characters!";
                                return data;

                            } else {

                                evolutionMethod = reader.text().toString();

                            }

                        } else if (name == "value") {

                            reader.readNext();
                            if (!reader.isCharacters()) {

                                qWarning() << "Evolution Value does not contain characters!";
                                return data;

                            } else {

                                evolutionValue = reader.text().toUInt();

                            }

                        }

                    }

                    evolutions.emplace_back(evolutionName, evolutionMethod, evolutionValue);

                }

            }

            data.setEvolutions(evolutions);

        }

    }

    return data;

}

template <>
inline bool TDatabase<Animal>::parse() {

    QFile file(k_animalPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qCritical() << "Could not open" << k_animalPath;
        return false;
    }

    fillData(file, "animal");

    return true;

}

/*
 *
 *  Types
 *
 */

const QString k_typePath("../AnimalsEditor/data/types.xml");

template <>
inline bool TDatabase<Type>::save() {

    const auto dataByID = getByID();

    QFile file(k_typePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qCritical() << "Could not open " << k_typePath;
        return false;
    }

    QXmlStreamWriter writer(&file);

    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeStartElement("types");

    for (const auto & p : dataByID) {

        const auto data = p.second;
        writer.writeStartElement("type");
        writer.writeAttribute("id", QString::number(p.first));

        writer.writeStartElement("name");
        writer.writeCharacters(data.getName());
        writer.writeEndElement();

        for (const auto & effect : data.effectivenesses()) {

            writer.writeStartElement("effectiveness");
            writer.writeAttribute("name", effect.first);
            writer.writeCharacters(Type::typeToString(effect.second));
            writer.writeEndElement();

        }

        writer.writeEndElement();

    }

    writer.writeEndElement();
    writer.writeEndDocument();

    return true;

}

template <>
inline auto TDatabase<Type>::getData(QXmlStreamReader & reader) -> Type const {

    assert(reader.name() == "type");

    Type data;

    auto attr = reader.attributes();
    if (!attr.hasAttribute("id")) {

        qWarning() << "Type has no ID!";
        return data;

    }

    std::map<QString, EffectiveType> effectMap;

    while(!(reader.isEndElement() && reader.name() == "type")) {

        reader.readNext();
        if (reader.isEndElement()) {
            continue;
        }

        const auto name = reader.name();

        //name
        if (name == "name") {

            reader.readNext();
            if(!reader.isCharacters()) {

                qWarning() << "Name does not contain characters!";
                return data;

            } else {

                data.setName(reader.text().toString());

            }

        } else

        //effectiveness
        if (name == "effectiveness") {

            attr = reader.attributes();
            if (!attr.hasAttribute("name")) {

                qWarning() << "Effectiveness has no name!";
                return data;

            }

            reader.readNext();
            if(!reader.isCharacters()) {

                qWarning() << "Effectiveness does not contain characters!";
                return data;

            } else {

                const auto name = attr.value("name").toString();
                const auto effect = reader.text().toString();
                effectMap.emplace(name, Type::stringToType(effect));

            }

        }

    }

    data.setEffectivenesses(effectMap);

    return data;

}

template <>
inline bool TDatabase<Type>::parse() {

    QFile file(k_typePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qCritical() << "Could not open" << k_typePath;
        return false;
    }

    fillData(file, "type");

    return true;

}

/*
 *
 *  Must be below getData specializations
 *
 */

template <typename T>
void TDatabase<T>::fillData(QFile & file, const QString & name) {

    QXmlStreamReader reader(&file);

    while (!reader.atEnd() && !reader.hasError()) {

        reader.readNext();
        if (reader.isStartElement() && reader.name() == name) {

            const auto ID = reader.attributes().value("id").toUInt();
            auto data = getData(reader);
            data.setID(ID);
            m_data.emplace(data.getName(), data);

        }

    }

}

} // namespace db
