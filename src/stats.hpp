#ifndef _STATS_H
#define _STATS_H

class Stats {
	
	public:
		
		Stats(const unsigned int, const unsigned int, const unsigned int, const float);
		~Stats();

		const unsigned int getHealth() const { return m_health; }
		const unsigned int getAttack() const { return m_attack; }
		const unsigned int getDefense() const { return m_defense; }
		const float getMultiplier() const { return m_multiplier; }

	private:

		unsigned int m_health;
		unsigned int m_attack;
		unsigned int m_defense;
		float m_multiplier;

};

#endif // _STATS_H