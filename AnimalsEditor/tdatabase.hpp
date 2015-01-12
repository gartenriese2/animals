#ifndef TDATABASE_HPP
#define TDATABASE_HPP

#include <QString>

#include <map>

class QXmlStreamReader;
class QFile;

namespace db {

template <typename T>
class TDatabase {

    static_assert(std::is_same<T, Animal>() || std::is_same<T, Move>() || std::is_same<T, Type>());

    public:

        TDatabase();
        ~TDatabase();

        auto get() -> std::map<QString, T> const { return m_data; }
        auto getByID() -> std::map<unsigned int, T> const;
        void set(const std::map<QString, T> & data) { m_data = data; }
        bool deleteData(const QString &);
        bool insertData(unsigned int, const T &);

        bool save();

    private:

        auto getData(QXmlStreamReader &) -> T const;
        bool parse();
        void fillData(QFile &, const QString &);

        std::map<QString, T> m_data;

};

} // namespace db

#include "tdatabase.tpp"

#endif // TDATABASE_HPP
