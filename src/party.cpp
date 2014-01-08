#include "party.hpp"

#include <iostream>

static constexpr unsigned int k_maxAnimals = 5;

Party::Party() {
}

Party::~Party() {
}

void Party::addAnimal(const std::string & name) {

	if (getSize() < k_maxAnimals) {
		m_animals.emplace_back(Animal::getAnimal(name));
	} else {
		std::cout << "You can't carry more animals!" << std::endl;
	}

}

Animal & Party::getFrontAnimal() {
	
	if (getSize() == 0) {
		std::cout << "You don't have any animals!" << std::endl;
		abort();
	} else {
		return m_animals.at(0);
	}
	
}

void Party::heal(){

	for (auto & i : m_animals) {
		i.heal();
	}
	std::cout << "Your animals were healed!" << std::endl;

}
