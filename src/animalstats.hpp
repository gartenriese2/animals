#ifndef _ANIMALSTATS_H
#define _ANIMALSTATS_H

class AnimalStats {

	public:

		AnimalStats(const unsigned int, const unsigned int, const unsigned int, const unsigned int,
			const float, const float, const float, const float, const float);
		~AnimalStats();

		unsigned int getHealth() const { return m_health; }
		void setHealth(const unsigned int h) { m_health = h; }
		unsigned int getActualHealth() const { return m_healthActual; }
		void setActualHealth(const unsigned int h) { m_healthActual = h; }
		unsigned int getAttack() const { return m_attack; }
		void setAttack(const unsigned int a) { m_attack = a; }
		unsigned int getActualAttack() const { return m_attackActual; }
		void setActualAttack(const unsigned int a) { m_attackActual = a; }
		unsigned int getDefense() const { return m_defense; }
		void setDefense(const unsigned int d) { m_defense = d; }
		unsigned int getActualDefense() const { return m_defenseActual; }
		void setActualDefense(const unsigned int d) { m_defenseActual = d; }
		unsigned int getSpeed() const { return m_speed; }
		void setSpeed(const unsigned int s) { m_speed = s; }
		unsigned int getActualSpeed() const { return m_speedActual; }
		void setActualSpeed(const unsigned int s) { m_speedActual = s; }
		float getHealthMultiplier() const { return m_healthMultiplier; }
		float getAttackMultiplier() const { return m_attackMultiplier; }
		float getDefenseMultiplier() const { return m_defenseMultiplier; }
		float getSpeedMultiplier() const { return m_speedMultiplier; }
		float getExpMultiplier() const { return m_expMultiplier; }

	private:

		unsigned int m_health;
		unsigned int m_healthActual;
		unsigned int m_attack;
		unsigned int m_attackActual;
		unsigned int m_defense;
		unsigned int m_defenseActual;
		unsigned int m_speed;
		unsigned int m_speedActual;

		float m_healthMultiplier;
		float m_attackMultiplier;
		float m_defenseMultiplier;
		float m_speedMultiplier;
		float m_expMultiplier;

};

#endif // _ANIMALSTATS_H
