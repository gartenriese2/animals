#include "attack.hpp"

const std::map<std::string, Attack> & Attack::getAttacks() {
	
	static std::map<std::string, Attack> s_attacks {
		// Fire
		{"Fire Spark", Attack("Fire Spark", AttackStats(Type(BaseType::Fire), 25, 0, 0.95f))},
		{"Fire Blast", Attack("Fire Blast", AttackStats(Type(BaseType::Fire), 50, 0, 0.95f))},
		{"Flamethrower", Attack("Flamethrower", AttackStats(Type(BaseType::Fire), 100, 0, 1.f))},
		{"Fire Ball", Attack("Fire Ball", AttackStats(Type(BaseType::Fire), 40, 0, 0.80f))},
		{"Hellfire", Attack("Hellfire", AttackStats(Type(BaseType::Fire), 120, -50, 0.6f))},
		{"Flamebullet", Attack("Flamebullet", AttackStats(Type(BaseType::Fire), 75, 0, 0.95f))},
		{"Glow", Attack("Glow", AttackStats(Type(BaseType::Fire), 0, 0, 1.f, 0.8f))},
		// Water
		{"Water Splash", Attack("Water Splash", AttackStats(Type(BaseType::Water), 25, 0, 0.95f))},
		{"Water Blast", Attack("Water Blast", AttackStats(Type(BaseType::Water), 50, 0, 0.95f))},
		{"Water Wave", Attack("Water Wave", AttackStats(Type(BaseType::Water), 70, 0, 1.f))},
		{"Rainstorm", Attack("Rainstorm", AttackStats(Type(BaseType::Water), 80, 0, 0.9f))},
		{"Tsunami", Attack("Tsunami", AttackStats(Type(BaseType::Water), 100, 0, 1.f))},
		{"Fin Attack", Attack("Fin Attack", AttackStats(Type(BaseType::Water), 30, 0, 0.9f))},
		// Ice
		{"Ice Blow", Attack("Ice Blow", AttackStats(Type(BaseType::Ice), 35, 0, 0.9f))},
		{"Icerain", Attack("Icerain", AttackStats(Type(BaseType::Ice), 50, 0, 0.95f))},
		// Snow
		{"Snowball", Attack("Snowball", AttackStats(Type(BaseType::Snow), 30, 0, 0.8f))},
		{"Snowstorm", Attack("Snowstorm", AttackStats(Type(BaseType::Snow), 85, 0, 0.9f))},
		{"Avalanche", Attack("Avalanche", AttackStats(Type(BaseType::Snow), 120, 0, 0.75f))},
		// Electro
		{"Short Circuit", Attack("Short Circuit", AttackStats(Type(BaseType::Electro), 60, 0, 1.f))},
		// Stone
		// Earth
		// Air
		{"Claw", Attack("Claw", AttackStats(Type(BaseType::Air), 35, 0.9f))},
		// Plant
		{"Twine", Attack("Twine", AttackStats(Type(BaseType::Plant), 40, 0.95f))},
		{"Leaf Wrap", Attack("Leaf Wrap", AttackStats(Type(BaseType::Plant), 30, 0.95f))},
		// Normal
		{"Tackle", Attack("Tackle", AttackStats(Type(BaseType::Normal), 30, 0.95f))},
		{"Shove", Attack("Shove", AttackStats(Type(BaseType::Normal), 20, 0.95f))},
		{"Nudge", Attack("Nudge", AttackStats(Type(BaseType::Normal), 10, 0.95f))},
		{"Stomp", Attack("Stomp", AttackStats(Type(BaseType::Normal), 50, 0.95f))},
		{"Heal", Attack("Heal", AttackStats({{"OwnHPMod",Data(0.5f)}}))},
		{"Sting", Attack("Sting", AttackStats(Type(BaseType::Normal), 30, 0, 0.95f))},
		{"Intimidate", Attack("Intimidate", AttackStats({{"Prob",Data(0.95f)},{"AtkMod",0.8f}}))},
		// Ghost
		{"Spook", Attack("Spook", AttackStats(Type(BaseType::Ghost), 25, 0, 1.f))},
		{"Haunt", Attack("Haunt", AttackStats(Type(BaseType::Ghost), 45, 0, 0.95f))},
		{"Nightmare", Attack("Nightmare", AttackStats(Type(BaseType::Ghost), 65, 0, 0.9f))},
		// Psycho
		// Steel
		{"Steel Blow", Attack("Steel Blow", AttackStats(Type(BaseType::Steel), 35, 0, 0.9f))},
		{"Steel Edge", Attack("Steel Edge", AttackStats(Type(BaseType::Steel), 45, 0, 0.85f))},
		// Fighting
		// Dark
		{"Dark Shadow", Attack("Dark Shadow", AttackStats(Type(BaseType::Dark), 60, 0, 1.f))},
		{"Dark Eye", Attack("Dark Eye", AttackStats(Type(BaseType::Dark), 20, 0, 1.f, 0.8f))},
		// Light
		// Magma
		// Magnet
		// Underground
		{"Sonar", Attack("Sonar", AttackStats(Type(BaseType::Underground), 20, 0, 1.f))},
		{"Subduct", Attack("Subduct", AttackStats(Type(BaseType::Underground), 60, 0, 0.95f))},
		{"Earthquake", Attack("Earthquake", AttackStats(Type(BaseType::Underground), 120, 0, 1.f))},
		// Poison
		{"Poison Sting", Attack("Poison Sting", AttackStats(Type(BaseType::Poison), 45, 0, 0.8f, 0.9f, 0.9f, 0.9f))},
		// Radiation
		// Antic
		// Technology
		{"Disc Throw", Attack("Disc Throw", AttackStats(Type(BaseType::Technology), 25, 0, 0.85f))},
		{"Disc Cannon", Attack("Disc Cannon", AttackStats(Type(BaseType::Technology), 50, 0, 1.f))},
		{"Modern Shock", Attack("Modern Shock", AttackStats(Type(BaseType::Technology), 10, 0, 1.f, 0.9f, 1.f, 0.9f))},
		// Magic
		{"Hex", Attack("Hex", AttackStats(Type(BaseType::Magic), 25, 0, 0.95f))},
		{"Curse", Attack("Curse", AttackStats(Type(BaseType::Magic), 50, 0, 0.85f))},
		
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
