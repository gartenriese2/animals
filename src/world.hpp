#ifndef _WORLD_HPP
#define _WORLD_HPP

#include "area.hpp"
#include "player.hpp"

#include <map>

class World {

	public:

		World();
		~World();

		Player & getPlayer() { return m_player; }

	private:

		Player m_player;

};

#endif // _WORLD_HPP