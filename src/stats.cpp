#include "stats.hpp"

Stats::Stats(const unsigned int health, const unsigned int attack, const unsigned int defense, const float m)
  : m_health(health), m_attack(attack), m_defense(defense), m_multiplier(m)
{
}

Stats::~Stats() {
}
