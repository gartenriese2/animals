#ifndef DATA_H
#define DATA_H

#include <QString>

class Data {

    public:

        Data();
        virtual ~Data();

        unsigned int getID() const;
        void setID(unsigned int ID);

        QString getName() const;
        void setName(const QString &name);

    protected:

        unsigned int m_ID;
        QString m_name;

};

#endif // DATA_H
