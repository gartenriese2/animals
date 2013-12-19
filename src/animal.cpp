#include "animal.hpp"

Animal::Animal(const Type & type, const unsigned int health, const std::vector<Attack> & moves) 
	: m_type(type), m_health(health)
{	
	for (auto atk : moves) {
		m_moves.emplace_back(atk);
	}
}

Animal::~Animal() {

}

void Animal::changeHealth(const int h) {

	if (static_cast<int>(m_health + h) < 0) {
		m_health = 0;
	} else {
		m_health += h;
	}

}
