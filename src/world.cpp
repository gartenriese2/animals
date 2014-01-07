#include "world.hpp"

#include <iostream>

World::World()
  : m_player(Area::getArea("Test"))
{
}

World::~World() {
}
