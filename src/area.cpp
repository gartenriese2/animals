#include "area.hpp"

#include <iostream>

Area::Area()
  : m_playerPos(std::make_tuple(1,1))
{

	m_base = {{
		{"+++++++++"},
		{"+       +"},
		{"+       +"},
		{"+       +"},
		{"+       +"},
		{"+       +"},
		{"+       +"},
		{"+       +"},
		{"+       +"},
		{"+++++++++"}
	}};

}

Area::Area(const twoDimArr<char,k_height,k_width> & base)
  : m_base(base),
  	m_playerPos(std::make_tuple(1,1))
{
}

Area::~Area() {

}

void Area::print() const {

	for (unsigned int i = 0; i < m_base.size(); ++i) {

		for (unsigned int j = 0; j < m_base[i].size(); ++j) {
			
			if (j == std::get<0>(m_playerPos) && i == std::get<1>(m_playerPos)) {
				std::cout << "P";
			} else {
				std::cout << m_base[i][j];
			}
			
		}

		std::cout << std::endl;

	}

}

void Area::setPlayerPos(unsigned int x, unsigned int y) {

	if (x < m_base[0].size() && y < m_base.size() && m_base[y][x] != AreaType::BORDER) {
		m_playerPos = std::make_tuple(x, y);
		switch (m_base[y][x]) {
			case AreaType::GRASS:
				std::cout << "you walk in grass" << std::endl;
				break;
			case AreaType::PORTAL:
				std::cout << "this is a portal to another area!" << std::endl;
				break;
			default:
				break;
		}
	}

}

void Area::addPortal(const std::tuple<unsigned int, unsigned int> coord, std::shared_ptr<Area> area) {

	m_portals.emplace(std::make_pair(coord,area));

}
