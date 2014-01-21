#ifndef _PLAYER_HPP
#define _PLAYER_HPP

#include "party.hpp"
#include "area.hpp"
#include "io.hpp"

class Player {

	public:

		Player(const std::tuple<std::string,Position> &);
		~Player();

		void move(Key);
		void interact();

		Party & getParty() { return m_party; }
		const Area & getArea() { return m_area; }
		const Position & getPosition() { return m_position; }

	private:

		Party m_party;

		std::tuple<std::string,Position> m_respawnPos;
		Area m_area;
		twoDimArray m_areaBase;
		Position m_position;
		Position m_view;

		void setPosition(unsigned int x, unsigned int y);
		void enterArea(const std::string &);
		void grassAction();
		void respawn();

};

#endif // _PLAYER_HPP