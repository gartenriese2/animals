#include "attack.hpp"

const std::map<std::string, Attack> & Attack::getAttacks() {
    
    static std::map<std::string, Attack> s_attacks {
        // Fire
        {"Fire Spark", Attack("Fire Spark", AttackStats(Type(BaseType::Fire), 25))},
        {"Fire Blast", Attack("Fire Blast", AttackStats(Type(BaseType::Fire), 50))},
        {"Flamethrower", Attack("Flamethrower", AttackStats(Type(BaseType::Fire), 100))},
        {"Fire Ball", Attack("Fire Ball", AttackStats(Type(BaseType::Fire), 40))},
        {"Hellfire", Attack("Hellfire", AttackStats(Type(BaseType::Fire), 120))},
        {"Flamebullet", Attack("Flamebullet", AttackStats(Type(BaseType::Fire), 75))},
        // Water
        {"Water Splash", Attack("Water Splash", AttackStats(Type(BaseType::Water), 25))},
        {"Water Blast", Attack("Water Blast", AttackStats(Type(BaseType::Water), 50))},
        {"Water Wave", Attack("Water Wave", AttackStats(Type(BaseType::Water), 70))},
        {"Rainstorm", Attack("Rainstorm", AttackStats(Type(BaseType::Water), 80))},
        {"Tsunami", Attack("Tsunami", AttackStats(Type(BaseType::Water), 100))},
        {"Fin Attack", Attack("Fin Attack", AttackStats(Type(BaseType::Water), 30))},
        // Ice
        {"Ice Blow", Attack("Ice Blow", AttackStats(Type(BaseType::Ice), 35))},
        {"Icerain", Attack("Icerain", AttackStats(Type(BaseType::Ice), 50))},
        // Snow
        {"Snowball", Attack("Snowball", AttackStats(Type(BaseType::Snow), 30))},
        {"Snowstorm", Attack("Snowstorm", AttackStats(Type(BaseType::Snow), 85))},
        {"Avalanche", Attack("Avalanche", AttackStats(Type(BaseType::Snow), 120))},
        // Electro
        // Stone
        // Earth
        // Air
        {"Claw", Attack("Claw", AttackStats(Type(BaseType::Air), 35))},
        // Plant
        {"Twine", Attack("Twine", AttackStats(Type(BaseType::Plant), 40))},
        {"Leaf Wrap", Attack("Leaf Wrap", AttackStats(Type(BaseType::Plant), 30))},
        // Normal
        {"Tackle", Attack("Tackle", AttackStats(Type(BaseType::Normal), 30))},
        {"Shove", Attack("Shove", AttackStats(Type(BaseType::Normal), 20))},
        {"Nudge", Attack("Nudge", AttackStats(Type(BaseType::Normal), 10))},
        {"Stomp", Attack("Stomp", AttackStats(Type(BaseType::Normal), 50))},
        // Ghost
        {"Spook", Attack("Spook", AttackStats(Type(BaseType::Ghost), 25))},
        {"Haunt", Attack("Haunt", AttackStats(Type(BaseType::Ghost), 45))},
        {"Nightmare", Attack("Nightmare", AttackStats(Type(BaseType::Ghost), 65))},
        // Psycho
        // Steel
        {"Steel Blow", Attack("Steel Blow", AttackStats(Type(BaseType::Steel), 35))},
        // Fighting
        // Dark
        {"Dark Shadow", Attack("Dark Shadow", AttackStats(Type(BaseType::Dark), 60))},
        // Light
        // Magma
        // Magnet
        // Underground
        {"Sonar", Attack("Sonar", AttackStats(Type(BaseType::Underground), 20))},
        {"Subduct", Attack("Subduct", AttackStats(Type(BaseType::Underground), 60))},
        {"Earthquake", Attack("Earthquake", AttackStats(Type(BaseType::Underground), 120))},
        // Poison
        // Radiation
        // Antic
        // Technology
        // Magic
        {"Hex", Attack("Hex", AttackStats(Type(BaseType::Magic), 25))},
        
        
    };
    return s_attacks;

}

Attack::Attack(const std::string & name, const AttackStats & stats)
  : m_name(name), m_stats(stats)
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
