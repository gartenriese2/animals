#include "fight.hpp"

#include <iostream>
#include <math.h>

#include "console.hpp"

Fight::Fight(Animal & animal1, Animal & animal2, bool logging)
  : m_animal1(animal1), m_animal2(animal2), m_logging(logging)
{
}

Fight::~Fight() {
}

void Fight::printStatus() const {

	std::cout << "\033[4A";

	for (unsigned int i = 0; i < 4; ++i) {
		std::cout << "\033[1A" << "\r\033[K";
	}
	
	std::cout << m_animal1.getName() << ": " << std::endl;
	m_animal1.printHealth();
	std::cout << m_animal2.getName() << ": " << std::endl;
	m_animal2.printHealth();

	std::cout << "\033[4B";

}

void Fight::oneAttacks(const std::shared_ptr<Attack> atk) {

	Console::addText(m_animal1.getName() + " uses " + atk->getName() + ".");


	m_animal1.useAttack(atk, m_animal2);
	printStatus();

	if (atk->getType().getBaseTypes().at(0) != BaseType::None) {
		const EffectiveType eff = atk->getType().getEffectTypeAgainst(m_animal2.getType());
		if (m_logging) printAttack(m_animal1.getName(), atk->getName(), eff);
	}

}

void Fight::oneAttacksRandom() {

	const std::shared_ptr<Attack> atk = m_animal1.getRandomAttack();

	Console::addText(m_animal1.getName() + " uses " + atk->getName() + ".");
	

	m_animal1.useAttack(atk, m_animal2);
	printStatus();
	
	if (atk->getType().getBaseTypes().at(0) != BaseType::None) {
		const EffectiveType eff = atk->getType().getEffectTypeAgainst(m_animal2.getType());
		if (m_logging) printAttack(m_animal1.getName(), atk->getName(), eff);
	}

}

void Fight::twoAttacks(const std::shared_ptr<Attack> atk) {

	Console::addText(m_animal2.getName() + " uses " + atk->getName() + ".");
	

	m_animal2.useAttack(atk, m_animal1);
	printStatus();

	if (atk->getType().getBaseTypes().at(0) != BaseType::None) {
		const EffectiveType eff = atk->getType().getEffectTypeAgainst(m_animal1.getType());
		if (m_logging) printAttack(m_animal2.getName(), atk->getName(), eff);
	}

}

void Fight::twoAttacksRandom() {

	const std::shared_ptr<Attack> atk = m_animal2.getRandomAttack();
	
	Console::addText(m_animal2.getName() + " uses " + atk->getName() + ".");

	
	m_animal2.useAttack(atk, m_animal1);
	printStatus();

	if (atk->getType().getBaseTypes().at(0) != BaseType::None) {
		const EffectiveType eff = atk->getType().getEffectTypeAgainst(m_animal1.getType());
		if (m_logging) printAttack(m_animal2.getName(), atk->getName(), eff);
	}

}

void Fight::printAttack(const std::string & animalName, const std::string & atkName, const EffectiveType & eff) const {

	if (eff != EffectiveType::Neutral && eff != EffectiveType::Zero) {
		Console::addText("It is " + Database::getStringFromEffectivenessType(eff) + "!");
	} else if (eff == EffectiveType::Zero) {
		Console::addText("It has no effect!");
	}

}
