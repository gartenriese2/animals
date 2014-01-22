#include "textconsole.hpp"

#include "io.hpp"

//
// STATIC
//

void TextConsole::print() {

	instance().printText();
	printBorders();
	wrefresh(win());

}

void TextConsole::addText(const std::string & str) {
	
	unsigned int pos = instance().m_textWidth;
	while (pos < str.size()) {
		instance().m_text.emplace_back(str.substr(pos - instance().m_textWidth, instance().m_textWidth));
		pos += instance().m_textWidth;
	}
	instance().m_text.emplace_back(str.substr(pos - instance().m_textWidth));

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
	m_textWidth = getConsoleWidth() - 10;

}

void TextConsole::printText() const {

	for (unsigned int i = 0; i < m_textHeight; ++i) {
		
		moveCursorToTopOfTextOutput();
		moveCursorDown(i);

		clearLine();

		if (m_text.size() > i) {
			moveCursorRight((m_textWidth - m_text[i].size()) / 2);
			wprintw(win(),m_text[i].c_str());
		}

	}

}

void TextConsole::moveCursorToTopOfTextOutput() const {
	moveCursorToRow((getConsoleHeight() + m_textHeight) / 2);
	moveCursorToCol((getConsoleWidth() - m_textWidth) / 2);
}
