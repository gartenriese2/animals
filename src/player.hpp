#ifndef _PLAYER_HPP
#define _PLAYER_HPP

#include "area.hpp"
#include "io.hpp"

class Player {

	public:

		Player(Area &);
		~Player();

		void print() const;

		void move(ArrowKey);

	private:

		Area & m_area;
		Position m_position;

		void setPosition(unsigned int x, unsigned int y);
		void enterArea(const std::string &);

};

#endif // _PLAYER_HPP