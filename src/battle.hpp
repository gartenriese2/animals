#ifndef _BATTLE_H
#define _BATTLE_H

#include "fight.hpp"

class Battle {
	
	public:
		
		Battle(Animal &, Animal &);
		~Battle();

		void startAIvsAIRandom(const bool);
		void startUservsAIRandom();

	private:

		Animal & m_animal1;
		Animal & m_animal2;
	
};

#endif // _BATTLE_H