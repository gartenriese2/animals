#include "game.hpp"

Game::Game() {
	loop();
}

Game::~Game() {

}

void Game::loop() {

	while(1) {
		m_world.getPlayer().move(m_io.getArrowKey());
		m_world.getPlayer().printArea();
	}

}