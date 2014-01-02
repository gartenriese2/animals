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

		static const Area & getArea(const std::string &);

	private:

		static const std::map<std::string, Area> & getAreas();

		Player m_player;

};

#endif // _WORLD_HPP