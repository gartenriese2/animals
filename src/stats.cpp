#include "stats.hpp"

Stats::Stats(const unsigned int health, const unsigned int attack, const unsigned int defense,
		const unsigned int speed, const float hmul, const float amul, const float dmul, const float smul,
        const float emul)
  : m_health(health),
    m_healthActual(health),
	m_attack(attack),
    m_attackActual(attack),
	m_defense(defense),
    m_defenseActual(defense),
    m_speed(speed),
    m_speedActual(speed),
	m_healthMultiplier(hmul),
    m_attackMultiplier(amul),
    m_defenseMultiplier(dmul),
    m_speedMultiplier(smul),
	m_expMultiplier(emul)
{
}

Stats::~Stats() {
}
