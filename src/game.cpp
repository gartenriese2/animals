#include "game.hpp"

Game::Game() {
	intro();
	loop();
}

Game::~Game() {

}

void Game::intro() {

	std::cout << "Welcome to the world of Animals! ;-)" << std::endl;
	std::cout << "Do you want to play with the fire animal or the water animal?" << std::endl;
	m_world.getPlayer().getParty().addAnimal(m_io.chooseStarter());
	m_world.getPlayer().getParty().getFrontAnimal().raiseLevels(4);

}

void Game::loop() {

	printScreen();
	while(1) {
		ArrowKey key = m_io.getArrowKey();
		clearScreen(Area::getHeight());
		m_world.getPlayer().move(key);
		printScreen();
	}

}

void Game::clearScreen(unsigned int lines) {

	// jump over output line
	std::cout << "\033[1A";

	for (int i = 0; i <= lines; ++i) {
		std::cout << "\033[1A" << "\r\033[K";
	}

}

void Game::printScreen() {

	m_world.getPlayer().printArea();
	m_world.getPlayer().printOutput();

}