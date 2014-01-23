#include "textconsole.hpp"

#include "io.hpp"

//
// STATIC
//

void TextConsole::print() {

	Console::clear();

	instance().printText();
	Console::printBorders();
	
	Console::refresh();

}

void TextConsole::addText(const std::string & str) {
	
	std::vector<std::string> vec = Console::splitString(str, instance().m_textWidth);

	for (const auto i : vec) {
		instance().m_text.emplace_back(i);
	}

}

void TextConsole::advanceText() {
	if (instance().m_text.size() > 0) {
		instance().m_text.pop_front();
	}
}

void TextConsole::emptyText() {

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

TextConsole::TextConsole() {

	m_textHeight = 5;
	m_textWidth = Console::getWidth() - 10;

}

void TextConsole::printText() const {

	for (unsigned int i = 0; i < m_textHeight; ++i) {
		
		moveCursorToTopOfTextOutput();
		Console::moveCursorDown(i);

		Console::clearLine();

		if (m_text.size() > i) {
			Console::moveCursorRight((m_textWidth - m_text[i].size()) / 2);
			wprintw(Console::win(), m_text[i].c_str());
		}

	}

}

void TextConsole::moveCursorToTopOfTextOutput() const {
	Console::moveCursorToRow((Console::getHeight() + m_textHeight) / 2);
	Console::moveCursorToCol((Console::getWidth() - m_textWidth) / 2);
}
