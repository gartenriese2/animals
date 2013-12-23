#ifndef _STATS_H
#define _STATS_H

class Stats {
	
	public:
		
		Stats(const unsigned int, const unsigned int, const unsigned int, const float, const float);
		~Stats();

		const unsigned int getHealth() const { return m_health; }
		const unsigned int getAttack() const { return m_attack; }
		const unsigned int getDefense() const { return m_defense; }
		const float getMultiplier() const { return m_multiplier; }
		const float getExpMultiplier() const { return m_expMultiplier; }

	private:

		unsigned int m_health;
		unsigned int m_attack;
		unsigned int m_defense;
		float m_multiplier;
		float m_expMultiplier;

};

#endif // _STATS_H