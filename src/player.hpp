#ifndef _PLAYER_HPP
#define _PLAYER_HPP

#include "party.hpp"
#include "area.hpp"
#include "io.hpp"

class Player {

	public:

		Player(const std::tuple<std::string,Position> &);
		~Player();

		void printArea() const;
		void printOutput() const { std::cout << m_output << std::endl; }

		void move(Key);

		Party & getParty() { return m_party; }
		const Area & getArea() { return m_area; }
		const Position & getPosition() { return m_position; }

	private:

		Party m_party;

		std::tuple<std::string,Position> m_respawnPos;
		Area m_area;
		Position m_position;
		

		std::string m_output;

		void setPosition(unsigned int x, unsigned int y);
		void enterArea(const std::string &);
		void grassAction();
		void respawn();

};

#endif // _PLAYER_HPP