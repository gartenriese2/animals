#include "animal.hpp"

#include <stdlib.h>
#include <math.h>

static constexpr unsigned int k_healthBars = 50;

Animal::Animal(const std::string & name, const Type & type, const Stats & stats, const std::vector<Attack> & moves)
  : m_name(name), m_type(type), m_baseStats(stats), m_level(1), m_actualHealth(getMaxHealth())
{	
	for (auto atk : moves) {
		m_moves.emplace_back(atk);
	}
}

Animal::~Animal() {
}

void Animal::printHealth() const {
	
	float factor = static_cast<float>(m_actualHealth) / static_cast<float>(getMaxHealth());
	factor *= k_healthBars;
	unsigned int bars = round(factor);
	std::cout << "Health: [";
	for (unsigned int i = 0; i < k_healthBars; ++i) {
		if (i < bars) std::cout << "|";
		else std::cout << ".";
	}
	std::cout << "]" << std::endl;

}

void Animal::printInfo() const {

	std::cout << "----------INFO----------" << std::endl;
	std::cout << "Name:    " << m_name << std::endl;
	std::cout << "Type:    " << m_type << std::endl;
	std::cout << "Level:   " << m_level << std::endl;
	std::cout << "Health:  " << m_actualHealth << "/" << getMaxHealth() << std::endl;
	std::cout << "Attack:  " << getAttack() << std::endl;
	std::cout << "Defense: " << getDefense() << std::endl;
	std::cout << "Moves:" << std::endl;
	for (auto i : m_moves) {
		std::cout << "---- " << i.getName() << " (" << i.getDamage() << ") ["
			<< i.getType() << "]" << std::endl;
	}
	std::cout << "------------------------" << std::endl;

}

void Animal::changeHealth(const int h) {

	if (static_cast<int>(m_actualHealth + h) < 0) {
		m_actualHealth = 0;
	} else {
		m_actualHealth += h;
	}

}

const unsigned int Animal::getMaxHealth() const {

	return m_baseStats.getHealth() + m_baseStats.getMultiplier() * m_level;

}

const unsigned int Animal::getAttack() const {

	return m_baseStats.getAttack() + m_baseStats.getMultiplier() * m_level;

}

const unsigned int Animal::getDefense() const {

	return m_baseStats.getDefense() + m_baseStats.getMultiplier() * m_level;

}

const Attack & Animal::getRandomAttack() const {

	int choice = rand() % m_moves.size();
	return m_moves[choice];

}
