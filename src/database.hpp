#ifndef _DATABASE_H
#define _DATABASE_H

#include <map>
#include <vector>
#include <string>
#include "enums.hpp"

class Database {

    public:
        
        static const std::string getStringFromBaseType(const BaseType);
        static const std::string getStringFromEffectivenessType(const EffectiveType);
        static const EffectiveType getEffectiveness(const BaseType, const BaseType);
        static const float getEffectivenessValue(const EffectiveType);

    private:
        
        Database();

        std::map<BaseType, std::map<BaseType, EffectiveType>> m_effectivenesses;
        std::map<BaseType, std::string> m_baseTypeNames;
        std::map<EffectiveType, std::string> m_effectivenessTypeNames;

        static const Database & instance();

        void addNames();
        const std::string getName(const BaseType) const;
        const std::string getName(const EffectiveType) const;
        void addEffectivenesses();
        const EffectiveType getEffect(const BaseType, const BaseType) const;

        const std::map<BaseType, EffectiveType> createEffectivenessMap(const std::vector<float> &);
        const EffectiveType getEffectivenessType(const float);

};

#endif // _DATABASE_H
