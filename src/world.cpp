#include "world.hpp"

World::World()
  : m_player(std::make_tuple("Home",Position(18,9)))
{
}

World::~World() {
}
