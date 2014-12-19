#include "areaconsole.hpp"

#include "io.hpp"
#include "console.hpp"

#include <cassert>

static constexpr unsigned int k_textHeight = 2;

//
// STATIC
//

void AreaConsole::print() {

	Console::clear();

	instance().printBorders();
	instance().printArea();
	instance().printText();

	Console::refresh();

}

void AreaConsole::setAreaBase(std::shared_ptr<std::vector<std::string>> ptr) {

	instance().m_area = ptr;

}

void AreaConsole::setPosition(std::shared_ptr<Position_unsigned> ptr) {

	instance().m_pos = ptr;

}

void AreaConsole::addText(const std::vector<std::string> & vec) {

	for (const auto & line : vec) {
		addText(line);
	}

}

void AreaConsole::addText(const std::string & str) {

	for (const auto & i : Console::splitString(str)) {
		instance().m_text.emplace_back(i);
	}

}

void AreaConsole::advanceText() {

	if (instance().m_text.size() > 0) {
		instance().m_text.pop_front();
	}

}

void AreaConsole::emptyText() {

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

AreaConsole::AreaConsole() {

	m_areaHeight = Console::getHeight() - 3 - k_textHeight;
	m_areaWidth = Console::getWidth() - 2;
	m_grassColor = Console::setColor(0.f, 0.7f, 0.f);

}

void AreaConsole::printBorders() const {

	Console::printBorders();
	moveCursorToLowerBorder();

	waddstr(Console::win(), "\u251C");
	for (unsigned int i = 0; i < Console::getWidth() - 2; ++i) {

		waddstr(Console::win(), "\u2500");

	}
	waddstr(Console::win(), "\u2524");

}

void AreaConsole::printArea() const {

	moveCursorToTopOfArea();

	const int fromY = static_cast<int>(m_pos->getY()) - static_cast<int>(m_areaHeight) / 2;
	const int toY = fromY + static_cast<int>(m_areaHeight);
	const int fromX = static_cast<int>(m_pos->getX()) - static_cast<int>(m_areaWidth) / 2;
	const int toX = fromX + static_cast<int>(m_areaWidth);

	for (int i = fromY; i < toY; ++i) {

		Console::clearLine();
		Console::moveCursorToCol(1);

		if (i >= 0 && i < static_cast<int>(m_area->size())) {

			for (int j = fromX; j < toX; ++j) {

				if (j < 0 || j >= static_cast<int>((* m_area)[static_cast<size_t>(i)].size())) {

					wprintw(Console::win(), " ");

				} else if (i == static_cast<int>(m_pos->getY()) && j == static_cast<int>(m_pos->getX())) {

					wprintw(Console::win(), "P");

				} else {

					const auto area = * m_area;
					assert(i >= 0 && j >= 0);
					const char c = (* m_area)[static_cast<size_t>(i)][static_cast<size_t>(j)];
					if (c == '#') Console::useColor(m_grassColor);

					const std::string s(1, c);
					wprintw(Console::win(), s.c_str());

					Console::unsetColor(m_grassColor);

				}

			}

		}

		Console::moveCursorToNextLine();

	}

}

void AreaConsole::printText() const {

	for (unsigned int i = 0; i < k_textHeight; ++i) {

		moveCursorToTopOfTextOutput();
		Console::moveCursorDown(static_cast<int>(i));
		Console::moveCursorRight();

		Console::clearLine();

		if (m_text.size() > i) {

			Console::moveCursorRight((Console::getWidth() - 2 - static_cast<unsigned int>(m_text[i].size())) / 2);
			wprintw(Console::win(), m_text[i].c_str());

		}

	}

}

void AreaConsole::moveCursorToTopOfTextOutput() const {

	Console::moveCursorToRow(k_textHeight);
	Console::moveCursorToCol();

}

void AreaConsole::moveCursorToLowerBorder() const {

	Console::moveCursorToRow(k_textHeight + 1);
	Console::moveCursorToCol();

}

void AreaConsole::moveCursorToTopOfArea() const {

	Console::moveCursorToRow(static_cast<int>(k_textHeight + m_areaHeight + 1));
	Console::moveCursorToCol();

}

void AreaConsole::moveCursorToUpperBorder() const {

	Console::moveCursorToRow(static_cast<int>(k_textHeight + m_areaHeight + 2));
	Console::moveCursorToCol();

}
