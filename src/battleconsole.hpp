#ifndef _BATTLECONSOLE_HPP
#define _BATTLECONSOLE_HPP

#include <string>
#include <deque>
#include <vector>

#include "console.hpp"

class BattleConsole {

	public:

		static void print();
		static void printAttacks(const std::vector<std::string> &, unsigned int = 0);
		static void clearAttacks();
		static void printOwn(const std::string &, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
		static void printFoe(const std::string &, unsigned int, unsigned int, unsigned int);

		static void addText(const std::string &);
		static void advanceText();
		static void emptyText();
		static bool textEmpty() { return instance().m_text.empty(); }

	private:

		BattleConsole();

		void printBorders() const;
		void printText() const;

		void moveCursorToTopOfTextOutput() const;
		void moveCursorToLowerBorder() const;
		void moveCursorToOwnAnimal() const;
		void moveCursorToFoeAnimal() const;

		static BattleConsole & instance() { static BattleConsole c; return c; }

		std::deque<std::string> m_text;
		unsigned int m_textWidth;
		unsigned int m_textHeight;
		unsigned int m_attackHighlightColor;
		unsigned int m_regularHealthColor;
		unsigned int m_badHealthColor;
		unsigned int m_criticalHealthColor;
		unsigned int m_xpColor;
		unsigned int m_bars;

};

#endif // _BATTLECONSOLE_HPP