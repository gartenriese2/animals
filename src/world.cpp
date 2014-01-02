#include "world.hpp"

#include <iostream>

World::World()
  : m_player(std::make_shared<Area>(World::getArea("Test")))
{
}

World::~World() {
}

const Area & World::getArea(const std::string & s) {

	if (getAreas().count(s) == 0) {
		std::cout << "no such area: " << s << std::endl;
		abort();
	}

	return getAreas().at(s);

}

const std::map<std::string, Area> & World::getAreas() {
	
	static std::map<std::string, Area> s_areas {
		{"Test",Area({{
				{"+++++++++"},
				{"+       +"},
				{"+       +"},
				{"+       +"},
				{"+       +"},
				{"+       +"},
				{"+       +"},
				{"+     ##+"},
				{"+     ##+"},
				{"+++++++++"}
				}})
		},
	};

	return s_areas;

}
