#ifndef _PLAYER_HPP
#define _PLAYER_HPP

#include "area.hpp"
#include "io.hpp"

class Player {

	public:

		Player(std::shared_ptr<Area>);
		~Player();

		void printArea() const { m_area->print(); }

		void move(ArrowKey);

	private:

		std::shared_ptr<Area> m_area;

};

#endif // _PLAYER_HPP