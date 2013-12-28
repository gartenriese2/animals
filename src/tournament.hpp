#ifndef _TOURNAMENT_HPP
#define _TOURNAMENT_HPP

#include "battle.hpp"

class Tournament {

	public:

		Tournament();
		~Tournament();

		void startSingleBattle(Animal &, Animal &);
		void startSingleRandomBattle(Animal &);
		void startSingleRandomBattle();

		void startKOBattles();
		void startRandomBattles();

        void startWithFirestarter();
        //void startWithWaterstarter();

	private:

};

#endif // _TOURNAMENT_HPP