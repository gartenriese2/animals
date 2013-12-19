#ifndef _FIGHT_H
#define _FIGHT_H

#include "animal.hpp"

class Fight {
	
	public:
		
		Fight(Animal &, Animal &);
		~Fight();

		void printStatus() const;

		void oneAttacks(const Attack &);
		void twoAttacks(const Attack &);

	private:

		Animal & m_animal1;
		Animal & m_animal2;

	
};

#endif // _FIGHT_H