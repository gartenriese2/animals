#ifndef MOVEDATABASE_H
#define MOVEDATABASE_H

#include <QString>

#include <map>

#include "database.h"
#include "move.h"

class QXmlStreamReader;

namespace db {

class MoveDatabase : public Database {

    public:

        MoveDatabase();
        ~MoveDatabase();

        const std::map<QString, Move> & get() const { return m_data; }
        const std::map<unsigned int, Move> getByID() const;
        void set(const std::map<QString, Move> & data) { m_data = data; }
        bool deleteData(const QString &);
        bool insertData(unsigned int, const Move &);

        bool save();

    private:

        bool parse();
        const Move getData(QXmlStreamReader &);

        std::map<QString, Move> m_data;

};

} // namespace db

#endif // MOVEDATABASE_H
