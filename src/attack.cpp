#include "attack.hpp"

static std::map<std::string, Attack> s_attacks {
    // Fire
    std::pair<std::string, Attack>("Fire Blast", Attack("Fire Blast", Type(BaseType::Fire), 50)),
    // Water
    std::pair<std::string, Attack>("Water Blast", Attack("Water Blast", Type(BaseType::Water), 50)),
    // Plant
    std::pair<std::string, Attack>("Twine", Attack("Twine", Type(BaseType::Plant), 40)),
    // Normal
    std::pair<std::string, Attack>("Tackle", Attack("Tackle", Type(BaseType::Normal), 30))
    
};

Attack::Attack(const std::string & name, const Type & type, const unsigned int damage)
  : m_name(name), m_type(type), m_damage(damage)
{
}

Attack::~Attack() {
}

const std::shared_ptr<Attack> Attack::getAttack(const std::string s) {
    return std::make_shared<Attack>(s_attacks.at(s));
}

const std::map<std::string, Attack> & Attack::getAttacks() {
    return s_attacks;
}

const std::map<std::string, Attack> Attack::getAttacks(const Type & type) {

    std::map<std::string, Attack> map;

    for (auto i : s_attacks) {

        if (type.isPartOf(i.second.getType())) {

            map.emplace(i);

        }

    }

    return map;

}
