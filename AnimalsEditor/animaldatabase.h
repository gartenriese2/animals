#ifndef ANIMALDATABASE_H
#define ANIMALDATABASE_H

#include <QString>

#include <map>

#include "database.h"
#include "animal.h"

class QXmlStreamReader;

namespace db {

class AnimalDatabase : public Database {

    public:

        AnimalDatabase();
        ~AnimalDatabase();

        const std::map<QString, Animal> & get() const { return m_data; }
        const std::map<unsigned int, Animal> getByID() const;
        void set(const std::map<QString, Animal> & data) { m_data = data; }
        bool deleteData(const QString &);
        bool insertData(unsigned int, const Animal &);

        bool save();

        virtual QString test() const { return "AnimalDatabase"; }

    private:

        bool parse();
        const Animal getData(QXmlStreamReader &);

        std::map<QString, Animal> m_data;

};

} // namespace db

#endif // ANIMALDATABASE_H
