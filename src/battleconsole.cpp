#include "battleconsole.hpp"

#include <algorithm>
#include <cmath>

#include "io.hpp"

static constexpr float k_badHealth = 0.4f;
static constexpr float k_criticalHealth = 0.15f;

//
// STATIC
//

void BattleConsole::print() {

	instance().printBorders();
	instance().printText();

	Console::refresh();

}

void BattleConsole::printAttacks(const std::vector<std::string> & vec, unsigned int highlight) {

	instance().printBorders();
	instance().printText();

	instance().moveCursorToTopOfTextOutput();
	Console::moveCursorDown(2);
	Console::moveCursorToCol(Console::getWidth() / 3 - vec[0].size() / 2);
	if (highlight == 0) Console::useColor(instance().m_attackHighlightColor);
	wprintw(Console::win(), vec[0].c_str());
	if (highlight == 0) Console::unsetColor(instance().m_attackHighlightColor);

	if (vec.size() > 1) {
		Console::moveCursorToCol(Console::getWidth() * 2 / 3 - vec[1].size() / 2);
		if (highlight == 1) Console::useColor(instance().m_attackHighlightColor);
		wprintw(Console::win(), vec[1].c_str());
		if (highlight == 1) Console::unsetColor(instance().m_attackHighlightColor);
	}

	if (vec.size() > 2) {
		Console::moveCursorDown(2);
		Console::moveCursorToCol(Console::getWidth() / 3 - vec[2].size() / 2);
		if (highlight == 2) Console::useColor(instance().m_attackHighlightColor);
		wprintw(Console::win(), vec[2].c_str());
		if (highlight == 2) Console::unsetColor(instance().m_attackHighlightColor);
	}

	if (vec.size() > 3) {
		Console::moveCursorToCol(Console::getWidth() * 2 / 3 - vec[3].size() / 2);
		if (highlight == 3) Console::useColor(instance().m_attackHighlightColor);
		wprintw(Console::win(), vec[3].c_str());
		if (highlight == 3) Console::unsetColor(instance().m_attackHighlightColor);
	}
	
	Console::refresh();

}

void BattleConsole::clearAttacks() {

	instance().moveCursorToTopOfTextOutput();
	Console::moveCursorDown(2);
	Console::clearLine();
	Console::moveCursorDown(2);
	Console::clearLine();

	Console::refresh();

}

void BattleConsole::printOwn(const std::string & name, unsigned int level, unsigned int health,
	unsigned int maxHealth, unsigned int XP, unsigned int maxXP) {

	instance().moveCursorToOwnAnimal();
	Console::moveCursorRight(2);

	// first line
	Console::clearLine();

	std::string line(name + " (Level " + std::to_string(level) + ")");
	wprintw(Console::win(), line.c_str());

	instance().moveCursorToOwnAnimal();
	Console::moveCursorDown();
	Console::moveCursorToCol(2);

	// second line
	Console::clearLine();

	line = "HP: [";
	std::string lineEnd("] " + std::to_string(health) + "/" + std::to_string(maxHealth));
	waddstr(Console::win(), line.c_str());

	int num1 = Console::getWidth() * 2 / 3 - 4 - line.size() - lineEnd.size();
	int num2 = Console::getMinWidth() - 4 - line.size() - lineEnd.size();
	instance().m_bars = std::max(num1, num2);
	unsigned int healthBars = std::ceil(static_cast<float>(health) / static_cast<float>(maxHealth) * static_cast<float>(instance().m_bars));

	if (static_cast<float>(health) / static_cast<float>(maxHealth) < k_criticalHealth) {
		Console::useColor(instance().m_criticalHealthColor);
	} else if (static_cast<float>(health) / static_cast<float>(maxHealth) < k_badHealth) {
		Console::useColor(instance().m_badHealthColor);
	} else {
		Console::useColor(instance().m_regularHealthColor);
	}
	
	for (unsigned int i = 0; i < healthBars; ++i) {
		waddstr(Console::win(), "|");
	}

	if (static_cast<float>(health) / static_cast<float>(maxHealth) < k_criticalHealth) {
		Console::unsetColor(instance().m_criticalHealthColor);
	} else if (static_cast<float>(health) / static_cast<float>(maxHealth) < k_badHealth) {
		Console::unsetColor(instance().m_badHealthColor);
	} else {
		Console::unsetColor(instance().m_regularHealthColor);
	}

	for (unsigned int i = healthBars; i < instance().m_bars; ++i) {
		waddstr(Console::win(), " ");
	}

	waddstr(Console::win(), lineEnd.c_str());

	instance().moveCursorToOwnAnimal();
	Console::moveCursorDown(2);
	Console::moveCursorToCol(2);

	// third line
	Console::clearLine();

	line = "XP: [";
	waddstr(Console::win(), line.c_str());

	unsigned int bars = instance().m_bars / 2;
	healthBars = std::floor(static_cast<float>(XP) / static_cast<float>(maxXP) * static_cast<float>(bars));

	Console::useColor(instance().m_xpColor);

	for (unsigned int i = 0; i < healthBars; ++i) {
		waddstr(Console::win(), "=");
	}

	Console::unsetColor(instance().m_xpColor);

	for (unsigned int i = healthBars; i < bars; ++i) {
		waddstr(Console::win(), " ");
	}

	waddstr(Console::win(), "]");

	instance().printBorders();
	instance().printText();

	Console::refresh();

}

void BattleConsole::printFoe(const std::string & name, unsigned int level, unsigned int health, unsigned int maxHealth) {

	// first line
	instance().moveCursorToFoeAnimal();
	Console::clearLine();

	std::string line(name + " (Level " + std::to_string(level) + ")");
	Console::moveCursorToCol(Console::getWidth() - line.size() - 2);
	wprintw(Console::win(), line.c_str());

	// second line
	instance().moveCursorToFoeAnimal();
	Console::moveCursorDown();
	Console::clearLine();

	line = "HP: [";
	std::string lineEnd("]");

	unsigned int healthBars = std::ceil(static_cast<float>(health) / static_cast<float>(maxHealth) * static_cast<float>(instance().m_bars));
DEB(std::to_string(healthBars));
	Console::moveCursorToCol(Console::getWidth() - line.size() - lineEnd.size() - instance().m_bars - 2);
	waddstr(Console::win(), line.c_str());

	for (unsigned int i = 0; i < instance().m_bars - healthBars; ++i) {
		waddstr(Console::win(), " ");
	}

	if (static_cast<float>(health) / static_cast<float>(maxHealth) < k_criticalHealth) {
		Console::useColor(instance().m_criticalHealthColor);
	} else if (static_cast<float>(health) / static_cast<float>(maxHealth) < k_badHealth) {
		Console::useColor(instance().m_badHealthColor);
	} else {
		Console::useColor(instance().m_regularHealthColor);
	}
	
	for (unsigned int i = instance().m_bars - healthBars; i < instance().m_bars; ++i) {
		waddstr(Console::win(), "|");
	}

	if (static_cast<float>(health) / static_cast<float>(maxHealth) < k_criticalHealth) {
		Console::unsetColor(instance().m_criticalHealthColor);
	} else if (static_cast<float>(health) / static_cast<float>(maxHealth) < k_badHealth) {
		Console::unsetColor(instance().m_badHealthColor);
	} else {
		Console::unsetColor(instance().m_regularHealthColor);
	}

	waddstr(Console::win(), lineEnd.c_str());

	instance().printBorders();
	instance().printText();

	Console::refresh();

}

void BattleConsole::addText(const std::string & str) {
	
	std::vector<std::string> vec = Console::splitString(str, instance().m_textWidth);

	for (const auto i : vec) {
		instance().m_text.emplace_back(i);
	}

}

void BattleConsole::advanceText() {
	if (instance().m_text.size() > 0) {
		instance().m_text.pop_front();
	}
}

void BattleConsole::emptyText() {

	while (!textEmpty()) {
		
		Key key = IO::getKey();

		if (key == Key::ENTER) {
			advanceText();
			print();
		}

	}

}

//
// MEMBER
//

BattleConsole::BattleConsole() {

	m_textHeight = 1;
	m_textWidth = Console::getWidth() - 10;
	m_attackHighlightColor = Console::setColor(0.f, 1.f, 0.f);
	m_regularHealthColor = Console::setColor(0.f, 1.f, 0.f);
	m_badHealthColor = Console::setColor(1.f, 0.5f, 0.f);
	m_criticalHealthColor = Console::setColor(1.f, 0.f, 0.f);
	m_xpColor = Console::setColor(0.f, 0.f, 1.f);

}

void BattleConsole::printBorders() const {

	Console::printBorders();
	moveCursorToLowerBorder();

	waddstr(Console::win(), "\u251C");
	for (unsigned int i = 0; i < Console::getWidth() - 2; ++i) {
		waddstr(Console::win(), "\u2500");
	}
	waddstr(Console::win(), "\u2524");

}

void BattleConsole::printText() const {

	for (unsigned int i = 0; i < m_textHeight; ++i) {
		
		moveCursorToTopOfTextOutput();
		Console::moveCursorDown(i);
		Console::moveCursorRight();

		Console::clearLine();

		if (m_text.size() > i) {
			Console::moveCursorRight((Console::getWidth() - 2 - m_text[i].size()) / 2);
			wprintw(Console::win(),m_text[i].c_str());
		}

	}

}

void BattleConsole::moveCursorToTopOfTextOutput() const {
	moveCursorToLowerBorder();
	Console::moveCursorDown(1);
}

void BattleConsole::moveCursorToLowerBorder() const {
	Console::moveCursorToRow(7);
	Console::moveCursorToCol();
}

void BattleConsole::moveCursorToOwnAnimal() const {
	moveCursorToLowerBorder();
	Console::moveCursorUp(3);
}

void BattleConsole::moveCursorToFoeAnimal() const {
	Console::moveCursorTo(1,1);
}
