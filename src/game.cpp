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

	m_world.getPlayer().print();
	while(1) {
		m_world.getPlayer().move(m_io.getArrowKey());
		m_world.getPlayer().print();
	}

}