#ifndef TYPE_H
#define TYPE_H

#include "data.h"

#include <QString>

#include <map>
#include <cstdint>

enum class EffectiveType : std::uint8_t { ZERO, HIGHLY_INEFFECTIVE, INEFFECTIVE,
                                          SLIGHTLY_INEFFECTIVE, NEUTRAL, SLIGHTLY_EFFECTIVE,
                                          EFFECTIVE, HIGHLY_EFFECTIVE, MOST_EFFECTIVE };

class Type : public Data
{
public:

    Type();
    ~Type();

    std::map<QString, EffectiveType> effectivenesses() const;
    void setEffectivenesses(const std::map<QString, EffectiveType> &effectivenesses);

    static EffectiveType stringToType(const QString &);
    static const QString typeToString(EffectiveType);
    static float typeToFloat(EffectiveType);

private:

    std::map<QString, EffectiveType> m_effectivenesses;

};

#endif // TYPE_H
