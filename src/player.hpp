#ifndef _PLAYER_HPP
#define _PLAYER_HPP

#include <memory>

#include "party.hpp"
#include "area.hpp"
#include "gui/io.hpp"

class Player {

	public:

		Player(const locationTuple &);
		~Player();

		void move(Key);
		void interact();

		Party & getParty() { return m_party; }
		const Area & getArea() { return m_area; }
		const Position_unsigned & getPosition() { return * m_position; }

	private:

		Party m_party;

		std::tuple<std::string,Position_unsigned> m_respawnPos;
		Area m_area;
		// std::shared_ptr<twoDimArray> m_areaBase;
		std::shared_ptr<std::vector<std::string>> m_areaBase;
		std::shared_ptr<Position_unsigned> m_position;
		Position m_view;

		void setPosition(unsigned int x, unsigned int y);
		void enterArea(const std::string &);
		void grassAction();
		void respawn();

};

#endif // _PLAYER_HPP
