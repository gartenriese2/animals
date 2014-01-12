#ifndef _PLAYER_HPP
#define _PLAYER_HPP

#include "party.hpp"
#include "area.hpp"
#include "io.hpp"

class Player {

	public:

		Player(Area);
		~Player();

		void printArea() const;
		void printOutput() const { std::cout << m_output << std::endl; }

		void move(ArrowKey);

		Party & getParty() { return m_party; }

	private:

		Party m_party;

		Area m_area;
		Position m_position;

		std::string m_output;

		void setPosition(unsigned int x, unsigned int y);
		void enterArea(const std::string &);
		void grassAction();

};

#endif // _PLAYER_HPP