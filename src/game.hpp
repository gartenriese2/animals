#ifndef _GAME_HPP
#define _GAME_HPP

#include "world.hpp"

class Game {

	public:

		Game();
		~Game();

	private:

		World m_world;

		void intro();
		void loop();

};

#endif // _GAME_HPP
