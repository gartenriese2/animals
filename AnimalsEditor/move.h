#ifndef MOVE_H
#define MOVE_H

#include "data.h"

class Move : public Data
{
public:
    Move();
    ~Move();

    unsigned int getBaseDamage() const;
    void setBaseDamage(unsigned int baseDamage);

    QString getType() const;
    void setType(const QString &type);

    QString getCategory() const;
    void setCategory(const QString &category);

    unsigned int getAccuracy() const;
    void setAccuracy(unsigned int accuracy);

    int getPriority() const;
    void setPriority(int priority);

private:

    unsigned int m_baseDamage;
    QString m_type;
    QString m_category;
    unsigned int m_accuracy;
    int m_priority;

};

#endif // MOVE_H
