#include "movedatabase.h"

#include <QFile>
#include <QIODevice>
#include <QtDebug>
#include <QXmlStreamReader>

#include <cassert>

namespace db {

const QString k_path("../AnimalsEditor/data/moves.xml");
const QString k_name("move");

MoveDatabase::MoveDatabase() {

    parse();

}

MoveDatabase::~MoveDatabase() {

}

const std::map<unsigned int, Move> MoveDatabase::getByID() const {

    std::map<unsigned int, Move> map;

    for (const auto & p : m_data) {

        map.emplace(p.second.getID(), p.second);

    }

    return map;

}

bool MoveDatabase::deleteData(const QString & name) {

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

bool MoveDatabase::insertData(unsigned int ID, const Move & data) {

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

bool MoveDatabase::save() {

    auto dataByID = getByID();

    QFile file(k_path);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qCritical() << "Could not open " << k_path;
        return false;
    }

    QXmlStreamWriter writer(&file);

    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeStartElement("moves");

    for (const auto & p : dataByID) {

        const auto data = p.second;
        writer.writeStartElement(k_name);
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

bool MoveDatabase::parse() {

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
            m_data.emplace(data.getName(), data);

        }

    }

    return true;

}

const Move MoveDatabase::getData(QXmlStreamReader & reader) {

    assert(reader.name() == k_name);

    Move move;

    auto attr = reader.attributes();
    if (!attr.hasAttribute("id")) {

        qWarning() << "Move has no ID!";
        return move;

    }

    while(!(reader.isEndElement() && reader.name() == k_name)) {

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
                return move;

            } else {

                move.setName(reader.text().toString());

            }

        } else

        // basedamage
        if (name == "basedamage") {

            reader.readNext();
            if(!reader.isCharacters()) {

                qWarning() << "Base Damage does not contain characters!";
                return move;

            } else {

                move.setBaseDamage(reader.text().toUInt());

            }

        } else

        // type
        if (name == "type") {

            reader.readNext();
            if(!reader.isCharacters()) {

                qWarning() << "Type does not contain characters!";
                return move;

            } else {

                move.setType(reader.text().toString());

            }

        } else

        // category
        if (name == "category") {

            reader.readNext();
            if(!reader.isCharacters()) {

                qWarning() << "Category does not contain characters!";
                return move;

            } else {

                move.setCategory(reader.text().toString());

            }

        } else

        // accuracy
        if (name == "accuracy") {

            reader.readNext();
            if(!reader.isCharacters()) {

                qWarning() << "Accuracy does not contain characters!";
                return move;

            } else {

                move.setAccuracy(reader.text().toUInt());

            }

        } else

        // priority
        if (name == "priority") {

            reader.readNext();
            if(!reader.isCharacters()) {

                qWarning() << "Priority does not contain characters!";
                return move;

            } else {

                move.setPriority(reader.text().toInt());

            }

        }

    }

    return move;

}

} // namespace db
