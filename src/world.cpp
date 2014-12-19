#include "world.hpp"

World::World()
  : m_player(std::make_tuple("Home", Position_unsigned(3,1)))
{
}

World::~World() {
}
