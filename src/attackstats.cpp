#include "attackstats.hpp"

#include "math.h"

static const Type k_defaultType = Type(BaseType::None);
static constexpr int k_defaultFoeDmg = 0;
static constexpr int k_defaultOwnDmg = 0;
static constexpr float k_defaultProbability = 1.f;
static constexpr float k_defaultFoeAttackModifier = 1.f;
static constexpr float k_defaultFoeDefenseModifier = 1.f;
static constexpr float k_defaultFoeSpeedModifier = 1.f;
static constexpr float k_defaultOwnAttackModifier = 1.f;
static constexpr float k_defaultOwnDefenseModifier = 1.f;
static constexpr float k_defaultOwnSpeedModifier = 1.f;
static constexpr float k_defaultOwnHealthModifier = 0.f;

AttackStats::AttackStats(const Type & type, int fdmg, int odmg,
	float p, float fam, float fdm, float fsm,
	float oam, float odm, float osm, float ohm)
  : m_type(type),
	m_foeDamage(fdmg),
	m_ownDamage(odmg),
	m_probability(p),
	m_foeAttackModifier(fam),
	m_foeDefenseModifier(fdm),
	m_foeSpeedModifier(fsm),
	m_ownAttackModifier(oam),
	m_ownDefenseModifier(odm),
	m_ownSpeedModifier(osm),
	m_ownHealthModifier(ohm)
{
}

AttackStats::AttackStats(const std::unordered_map<std::string, Data> & map) {
	m_type = (map.count("Type") == 1) ? map.at("Type").getType() : k_defaultType;
	m_foeDamage = (map.count("Dmg") == 1) ? map.at("Dmg").getInt() : k_defaultFoeDmg;
	m_ownDamage = (map.count("OwnDmg") == 1) ? map.at("OwnDmg").getInt() : k_defaultOwnDmg;
	m_probability = (map.count("Prob") == 1) ? map.at("Prob").getFloat() : k_defaultProbability;
	m_foeAttackModifier = (map.count("AtkMod") == 1) ? map.at("AtkMod").getFloat() : k_defaultFoeAttackModifier;
	m_foeDefenseModifier = (map.count("DefMod") == 1) ? map.at("DefMod").getFloat() : k_defaultFoeDefenseModifier;
	m_foeSpeedModifier = (map.count("SpdMod") == 1) ? map.at("SpdMod").getFloat() : k_defaultFoeSpeedModifier;
	m_ownAttackModifier = (map.count("OwnAtkMod") == 1) ? map.at("OwnAtkMod").getFloat() : k_defaultOwnAttackModifier;
	m_ownDefenseModifier = (map.count("OwnDefMod") == 1) ? map.at("OwnDefMod").getFloat() : k_defaultOwnDefenseModifier;
	m_ownSpeedModifier = (map.count("OwnSpdMod") == 1) ? map.at("OwnSpdMod").getFloat() : k_defaultOwnSpeedModifier;
	m_ownHealthModifier = (map.count("OwnHPMod") == 1) ? map.at("OwnHPMod").getFloat() : k_defaultOwnHealthModifier;
}

AttackStats::AttackStats(const Type & type, int dmg, float prob)
  : m_type(type),
  	m_foeDamage(dmg),
  	m_ownDamage(k_defaultOwnDmg),
  	m_probability(prob),
  	m_foeAttackModifier(k_defaultFoeAttackModifier),
	m_foeDefenseModifier(k_defaultFoeDefenseModifier),
	m_foeSpeedModifier(k_defaultFoeSpeedModifier),
	m_ownAttackModifier(k_defaultOwnAttackModifier),
	m_ownDefenseModifier(k_defaultOwnDefenseModifier),
	m_ownSpeedModifier(k_defaultOwnSpeedModifier),
	m_ownHealthModifier(k_defaultOwnHealthModifier)
{
}

AttackStats::~AttackStats() {
}

void AttackStats::handleArg(std::pair<std::string,int> &) {

}

void AttackStats::handleArg(std::pair<std::string,float> &) {

}

void AttackStats::handleArg(const Type &) {

}
