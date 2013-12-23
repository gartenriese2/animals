#include "attack.hpp"

const std::map<std::string, Attack> & Attack::getAttacks() {
    
    static std::map<std::string, Attack> s_attacks {
        // Fire
        std::pair<std::string, Attack>("Fire Blast", Attack("Fire Blast", Type(BaseType::Fire), 50)),
        // Water
        std::pair<std::string, Attack>("Water Blast", Attack("Water Blast", Type(BaseType::Water), 50)),
        // Plant
        std::pair<std::string, Attack>("Twine", Attack("Twine", Type(BaseType::Plant), 40)),
        // Normal
        std::pair<std::string, Attack>("Tackle", Attack("Tackle", Type(BaseType::Normal), 30)),
        // Dark
        std::pair<std::string, Attack>("Darkness", Attack("Darkness", Type(BaseType::Dark), 60)),
        // Magic
        std::pair<std::string, Attack>("Hex", Attack("Hex", Type(BaseType::Magic), 25))
        
        
    };
    return s_attacks;

}

Attack::Attack(const std::string & name, const Type & type, const unsigned int damage)
  : m_name(name), m_type(type), m_damage(damage)
{
}

Attack::~Attack() {
}

const std::shared_ptr<Attack> Attack::getAttack(const std::string s) {
    if (getAttacks().count(s) == 0) {
        std::cout << "no such attack: " << s << std::endl;
        abort();
    }
    return std::make_shared<Attack>(getAttacks().at(s));
}

const std::map<std::string, Attack> Attack::getAttacks(const Type & type) {

    std::map<std::string, Attack> map;

    for (auto i : getAttacks()) {

        if (type.isPartOf(i.second.getType())) {

            map.emplace(i);

        }

    }

    return map;

}
