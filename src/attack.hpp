#ifndef _ATTACK_H
#define _ATTACK_H

#include "attackstats.hpp"

class Attack {
	
	public:
		
		Attack(const std::string &, const AttackStats &);
		~Attack();

		double operator()(std::string str) const { return m_stats.getMap().at(str); }
		const std::string getName() const { return m_name; }
		const Type & getType() const { return m_stats.getType(); }

		static const std::map<std::string, Attack> getAttacks(const Type &);
		static const std::shared_ptr<Attack> getAttack(const std::string &);

	private:

		std::string m_name;
		AttackStats m_stats;

};

#endif // _ATTACK_H