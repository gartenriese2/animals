#include "attackstats.hpp"

#include "math.h"

AttackStats::AttackStats(const Type & type, int fdmg,
	int odmg, float fam, float fdm, float fsm,
	float oam, float odm, float osm, float p)
  : m_type(type),
  	m_foeDamage(fdmg),
  	m_ownDamage(odmg),
  	m_foeAttackModifier(fam),
  	m_foeDefenseModifier(fdm),
  	m_foeSpeedModifier(fsm),
  	m_ownAttackModifier(oam),
  	m_ownDefenseModifier(odm),
  	m_ownSpeedModifier(osm),
  	m_probability(p)
{
}

AttackStats::~AttackStats() {

}
