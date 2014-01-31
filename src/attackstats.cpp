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



AttackStats::AttackStats(const Type & type, const std::unordered_map<std::string, double> & map)
  : m_type(type)
{
	initValues();
	for (const auto & i : map) {
		m_values[i.first] = i.second;
	}
}

AttackStats::~AttackStats() {
}

void AttackStats::initValues() {

	m_values = {
		{"Accuracy", 1.0},
		{"Power", 0.0},
		{"OwnRelToMaxHeal", 0.0},
		{"OwnRelToMaxDmg", 0.0},
		{"FoeAbsDmg", 0.0},
		{"FoeRelToMaxDmg", 0.0},
		{"OwnRelAtkPlus", 0.0},
		{"OwnRelAtkMinus", 0.0},
		{"OwnRelSpdPlus", 0.0},
		{"OwnRelSpdMinus", 0.0},
		{"OwnRelDefPlus", 0.0},
		{"OwnRelDefMinus", 0.0},
		{"FoeRelAtkPlus", 0.0},
		{"FoeRelAtkMinus", 0.0},
		{"FoeRelDefMinus", 0.0},
		{"FoeRelDefPlus", 0.0},
		{"FoeRelSpdMinus", 0.0},
		{"FoeRelSpdPlus", 0.0},
	};

}
