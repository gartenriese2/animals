#include "world.hpp"

#include <iostream>

World::World()
  : m_player(Area::getArea("Home"))
{
}

World::~World() {
}
