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
