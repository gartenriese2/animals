#ifndef _FIGHT_H
#define _FIGHT_H

#include "animal.hpp"

class Fight {
	
	public:
		
		Fight(Animal &, Animal &, bool);
		~Fight();

		void printStatus() const;

		void oneAttacks(const std::shared_ptr<Attack>);
		void oneAttacksRandom();
		void twoAttacks(const std::shared_ptr<Attack>);
		void twoAttacksRandom();

	private:

		void printAttack(const std::string &, const std::string &, const EffectiveType &) const;
		void refreshAnimal1HealthOutput(unsigned int, unsigned int) const;
		void refreshAnimal2HealthOutput(unsigned int, unsigned int) const;

		Animal & m_animal1;
		Animal & m_animal2;
		bool m_logging;
	
};

#endif // _FIGHT_H