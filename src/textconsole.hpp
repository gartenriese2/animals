#ifndef _TEXTCONSOLE_HPP
#define _TEXTCONSOLE_HPP

#include <string>
#include <deque>

#include "console.hpp"

class TextConsole : public Console {

	public:

		static void print();

		static void addText(const std::string &);
		static void advanceText();
		static void emptyText();
		static bool textEmpty() { return instance().m_text.empty(); }

	private:

		TextConsole();

		void printText() const;
		void moveCursorToTopOfTextOutput() const;

		static TextConsole & instance() { static TextConsole c; return c; }

		std::deque<std::string> m_text;
		unsigned int m_textWidth;
		unsigned int m_textHeight;

};

#endif // _TEXTCONSOLE_HPP