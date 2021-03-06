#ifndef _DATABASE_HPP
#define _DATABASE_HPP

#include <map>
#include <vector>
#include <string>
#include "enums.hpp"

class Database {

    public:

        static const std::string getStringFromBaseType(const BaseType);
        static BaseType getBaseTypeFromString(const std::string &);
        static const std::string getStringFromEffectivenessType(const EffectiveType);
        static EffectiveType getEffectiveness(const BaseType, const BaseType);
        static float getEffectivenessValue(const EffectiveType);

    private:

        Database();

        std::map<BaseType, std::map<BaseType, EffectiveType>> m_effectivenesses;
        std::map<BaseType, std::string> m_baseTypeNames;
        std::map<EffectiveType, std::string> m_effectivenessTypeNames;

        static const Database & instance();

        void addNames();
        const std::string getName(const BaseType) const;
        BaseType getBaseType(const std::string &) const;
        const std::string getName(const EffectiveType) const;
        void addEffectivenesses();
        EffectiveType getEffect(const BaseType, const BaseType) const;

        const std::map<BaseType, EffectiveType> createEffectivenessMap(const std::vector<float> &);
        EffectiveType getEffectivenessType(const float);

};

#endif // _DATABASE_HPP
