#include "game.hpp"

#include "console.hpp"

Game::Game() {
	intro();
	loop();
}

Game::~Game() {

}

void Game::intro() {

	Console::clearArea();
	Console::addText("Welcome to the world of Animals! ;-)");
	Console::addText("Do you want to play with the fire animal or the water animal?");
	Console::printText();
	m_world.getPlayer().getParty().addAnimal(m_io.chooseStarter());
	m_world.getPlayer().getParty().getFrontAnimal().raiseLevels(4);	

	Console::setAreaBase(m_world.getPlayer().getArea().getBase());
	Console::setPosition(m_world.getPlayer().getPosition());

	IO::emptyOutput();

	Console::print();

}

void Game::loop() {

	while(1) {
		
		Key key = IO::getKey();

		if (key == Key::ENTER && !Console::activeMenu()) {
			Console::advanceText();
			Console::printText();
		} else if (key == Key::MENU) {
			Console::toggleMenu();
		} else if (Console::activeMenu()) {
			if (key == Key::UP) {
				Console::goMenuUp();
			} else if(key == Key::DOWN) {
				Console::goMenuDown();
			}
		} else {
			m_world.getPlayer().move(key);
		}
		
		Console::print();
		if (Console::activeMenu()) Console::printMenu();
	}

}