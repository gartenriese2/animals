#ifndef _GAME_HPP
#define _GAME_HPP

#include "world.hpp"
#include "io.hpp"

class Game {

	public:

		Game();
		~Game();

	private:

		World m_world;
		IO m_io;

		void intro();
		void loop();
		void clearScreen(unsigned int);
		void printScreen();

};

#endif // _GAME_HPP