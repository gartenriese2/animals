#include "fight.hpp"

#include <iostream>

Fight::Fight(Animal & animal1, Animal & animal2)
 : m_animal1(animal1), m_animal2(animal2)
{

}

Fight::~Fight() {

}

void Fight::printStatus() const {

	std::cout << "Animal One: " << m_animal1.getHealth() << "hp." << std::endl;
	std::cout << "Animal Two: " << m_animal2.getHealth() << "hp." << std::endl;

}

void Fight::oneAttacks(const Attack & atk) {

	m_animal2.changeHealth(static_cast<float>(atk.getDamage()) * -m_animal1.getType().getEffectValueAgainst(m_animal2.getType()));

}

void Fight::twoAttacks(const Attack & atk) {

	m_animal1.changeHealth(static_cast<float>(atk.getDamage()) * -m_animal2.getType().getEffectValueAgainst(m_animal1.getType()));

}
