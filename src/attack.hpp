#ifndef _ATTACK_H
#define _ATTACK_H

#include "attackstats.hpp"

class Attack {
	
	public:
		
		Attack(const std::string &, const AttackStats &);
		~Attack();

		const int getFoeDamage() const { return m_stats.getFoeDamage(); }
		const int getOwnDamage() const { return m_stats.getOwnDamage(); }
		const std::string getName() const { return m_name; }
		const Type & getType() const { return m_stats.getType(); }

		const float getFoeAttackModifier() const { return m_stats.getFoeAttackModifier(); }
		const float getFoeDefenseModifier() const { return m_stats.getFoeDefenseModifier(); }
		const float getFoeSpeedModifier() const { return m_stats.getFoeSpeedModifier(); }
		const float getOwnAttackModifier() const { return m_stats.getOwnAttackModifier(); }
		const float getOwnDefenseModifier() const { return m_stats.getOwnDefenseModifier(); }
		const float getOwnSpeedModifier() const { return m_stats.getOwnSpeedModifier(); }

		static const std::map<std::string, Attack> & getAttacks();
		static const std::map<std::string, Attack> getAttacks(const Type &);
		static const std::shared_ptr<Attack> getAttack(const std::string);

	private:

		std::string m_name;
		AttackStats m_stats;

};

#endif // _ATTACK_H