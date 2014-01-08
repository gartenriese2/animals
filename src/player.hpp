#ifndef _PLAYER_HPP
#define _PLAYER_HPP

#include "party.hpp"
#include "area.hpp"
#include "io.hpp"

class Player {

	public:

		Player(Area &);
		~Player();

		void print() const;

		void move(ArrowKey);

		Party & getParty() { return m_party; }

	private:

		Party m_party;

		Area m_area;
		Position m_position;

		void setPosition(unsigned int x, unsigned int y);
		void enterArea(const std::string &);
		void grassAction();

};

#endif // _PLAYER_HPP