#ifndef _TOURNAMENT_HPP
#define _TOURNAMENT_HPP

#include "battle.hpp"
#include "party.hpp"

class Tournament {

	public:

		Tournament();
		~Tournament();

		void startSingleBattle(Animal &, Animal &);
		void startSingleRandomBattle(Animal &);
		void startSingleRandomBattle();

		void startKOBattles();
		void startRandomBattles(unsigned int, unsigned int);

        void startWithFirestarter();
        void startWithWaterstarter();

        void startTrainerBattles(Party &, Party &);

	private:

};

#endif // _TOURNAMENT_HPP