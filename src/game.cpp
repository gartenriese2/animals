#include "game.hpp"

#include "gui/areaconsole.hpp"
#include "gui/textconsole.hpp"
#include "gui/io.hpp"

Game::Game() {

	intro();
	loop();

}

Game::~Game() {

}

void Game::intro() {

	TextConsole::addText("Welcome to the world of Animals! ;-)");
	TextConsole::print();
	TextConsole::emptyText();

	m_world.getPlayer().getParty().addAnimal(IO::chooseStarter());
	m_world.getPlayer().getParty().getFrontAnimal().raiseLevels(4);

	TextConsole::addText("You choose " + m_world.getPlayer().getParty().getFrontAnimal().getName() + ", the "
		+ m_world.getPlayer().getParty().getFrontAnimal().getType().getString() + " animal.");
	TextConsole::print();
	TextConsole::emptyText();

	AreaConsole::print();

}

void Game::loop() {

	while(1) {

		Key key = IO::getKey();

		if (key == Key::ENTER && !AreaConsole::textEmpty()) {
			AreaConsole::advanceText();
			AreaConsole::print();
		} else if (key == Key::ENTER) {
			m_world.getPlayer().interact();
		} else if (key == Key::ESCAPE) {
			break;
		} else {
			m_world.getPlayer().move(key);
		}

		AreaConsole::print();

	}

}
