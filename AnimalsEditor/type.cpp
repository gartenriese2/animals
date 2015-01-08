#include "type.h"

Type::Type()
{

}

Type::~Type()
{

}

std::map<QString, EffectiveType> Type::effectivenesses() const
{
    return m_effectivenesses;
}

void Type::setEffectivenesses(const std::map<QString, EffectiveType> &effectivenesses)
{
    m_effectivenesses = effectivenesses;
}

EffectiveType Type::stringToType(const QString & str) {

    if (str == "Zero") return EffectiveType::ZERO;
    if (str == "HighlyIneffective") return EffectiveType::HIGHLY_INEFFECTIVE;
    if (str == "Ineffective") return EffectiveType::INEFFECTIVE;
    if (str == "SlightlyIneffective") return EffectiveType::SLIGHTLY_INEFFECTIVE;
    if (str == "SlightlyEffective") return EffectiveType::SLIGHTLY_EFFECTIVE;
    if (str == "Effective") return EffectiveType::EFFECTIVE;
    if (str == "HighlyEffective") return EffectiveType::HIGHLY_EFFECTIVE;
    if (str == "MostEffective") return EffectiveType::MOST_EFFECTIVE;
    return EffectiveType::NEUTRAL;

}

const QString Type::typeToString(EffectiveType type) {

    switch (type) {
        case EffectiveType::ZERO:
            return "Zero";
        case EffectiveType::HIGHLY_INEFFECTIVE:
            return "HighlyIneffective";
        case EffectiveType::INEFFECTIVE:
            return "Ineffective";
        case EffectiveType::SLIGHTLY_INEFFECTIVE:
            return "SlightlyIneffective";
        case EffectiveType::NEUTRAL:
            return "Neutral";
        case EffectiveType::SLIGHTLY_EFFECTIVE:
            return "SlightlyEffective";
        case EffectiveType::EFFECTIVE:
            return "Effective";
        case EffectiveType::HIGHLY_EFFECTIVE:
            return "HighlyEffective";
        case EffectiveType::MOST_EFFECTIVE:
            return "MostEffective";
    }

    return "Neutral";

}

float Type::typeToFloat(EffectiveType type) {

    switch (type) {
        case EffectiveType::ZERO:
            return 0.f;
        case EffectiveType::HIGHLY_INEFFECTIVE:
            return 0.25f;
        case EffectiveType::INEFFECTIVE:
            return 0.5f;
        case EffectiveType::SLIGHTLY_INEFFECTIVE:
            return 0.75f;
        case EffectiveType::NEUTRAL:
            return 1.f;
        case EffectiveType::SLIGHTLY_EFFECTIVE:
            return 1.25f;
        case EffectiveType::EFFECTIVE:
            return 1.5f;
        case EffectiveType::HIGHLY_EFFECTIVE:
            return 2.f;
        case EffectiveType::MOST_EFFECTIVE:
            return 2.5f;
    }

    return 0.f;

}
