#ifndef _FIGHT_H
#define _FIGHT_H

#include "animal.hpp"

class Fight {
	
	public:
		
		Fight(Animal &, Animal &, const bool);
		~Fight();

		void printStatus() const;

		void oneAttacks(const std::shared_ptr<Attack>);
		void oneAttacksRandom();
		void twoAttacks(const std::shared_ptr<Attack>);
		void twoAttacksRandom();

	private:

		const int calculateDamageAgainst(const Animal &, const std::shared_ptr<Attack>, const Animal &) const;
		void printAttack(const std::string &, const std::string &, const int, const EffectiveType &) const;

		Animal & m_animal1;
		Animal & m_animal2;
		bool m_logging;
	
};

#endif // _FIGHT_H