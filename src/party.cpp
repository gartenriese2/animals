#include "party.hpp"

#include <iostream>
#include "areaconsole.hpp"
#include "io.hpp"

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

Animal & Party::getFirstHealthyAnimal() {

	if (getSize() == 0) {
		std::cout << "You don't have any animals!" << std::endl;
		abort();
	}

	for (auto & i : m_animals) {
		if (i.getActualHealth() > 0) return i;
	}

	DEB("No healthy animals!");
	throw "";

}

void Party::heal(){

	for (auto & i : m_animals) {
		i.heal();
	}
	AreaConsole::addText("Your animals were healed!");
	AreaConsole::print();
	AreaConsole::emptyText();

}

bool Party::isHealthy() const {

	for (const auto & i : m_animals) {
		if (i.getActualHealth() > 0) return true;
	}

	return false;

}
