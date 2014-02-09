#include "attackstats.hpp"

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
		{"Priority", 0.0},
		{"Accuracy", 1.0},
		{"Power", 0.0},
		{"OwnRelToMaxHeal", 0.0},
		{"OwnRelToMaxDmg", 0.0},
		{"FoeAbsDmg", 0.0},
		{"FoeRelToMaxDmg", 0.0},
		{"OwnRelAtk", 1.0},
		{"OwnRelSpd", 1.0},
		{"OwnRelDef", 1.0},
		{"FoeRelAtk", 1.0},
		{"FoeRelDef", 1.0},
		{"FoeRelSpd", 1.0},
	};

}
