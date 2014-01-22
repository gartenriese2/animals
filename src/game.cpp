#include "game.hpp"

#include "areaconsole.hpp"
#include "textconsole.hpp"

Game::Game() {

	intro();
	// loop();

}

Game::~Game() {

}

void Game::intro() {

	TextConsole::addText("Welcome to the world of Animals! ;-)");
	TextConsole::print();
	TextConsole::emptyText();

	m_world.getPlayer().getParty().addAnimal(m_io.chooseStarter());
	// m_world.getPlayer().getParty().getFrontAnimal().raiseLevels(4);	

	// Console::setAreaBase(m_world.getPlayer().getArea().getBase());
	// Console::setPosition(m_world.getPlayer().getPosition());

	

	// AreaConsole::print();

}

void Game::loop() {

	while(1) {
		
		Key key = IO::getKey();

		if (key == Key::ENTER && /*!Console::activeMenu() &&*/ !AreaConsole::textEmpty()) {
			AreaConsole::advanceText();
			AreaConsole::print();
		} else if (key == Key::ENTER /*&& !Console::activeMenu()*/) {
			m_world.getPlayer().interact();
		} else if (key == Key::MENU) {
			// Console::toggleMenu();
		// } else if (Console::activeMenu()) {
			// if (key == Key::UP) {
			// 	Console::goMenuUp();
			// } else if(key == Key::DOWN) {
			// 	Console::goMenuDown();
			// }
		} else {
			m_world.getPlayer().move(key);
		}
		
		AreaConsole::print();
		// if (Console::activeMenu()) Console::printMenu();
	}

}