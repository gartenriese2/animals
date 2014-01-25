#ifndef _FIGHT_H
#define _FIGHT_H

#include "animal.hpp"

class Fight {
	
	public:
		
		Fight(Animal &, Animal &, bool);
		~Fight();

		void ownAttacks(const std::shared_ptr<Attack>);
		void ownAttacksRandom();
		void foeAttacks(const std::shared_ptr<Attack>);
		void foeAttacksRandom();

	private:

		void printAttack(const std::string &, const std::string &, const EffectiveType &) const;
		bool refreshOwnHealth(unsigned int, unsigned int) const;
		bool refreshFoeHealth(unsigned int, unsigned int) const;

		Animal & m_own;
		Animal & m_foe;
		bool m_logging;
	
};

#endif // _FIGHT_H