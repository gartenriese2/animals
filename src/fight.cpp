#include "fight.hpp"

#include <iostream>
#include <math.h>

Fight::Fight(Animal & animal1, Animal & animal2, const bool logging)
  : m_animal1(animal1), m_animal2(animal2), m_logging(logging)
{
	std::cout << std::endl << "Fight begins!" << std::endl << std::endl;
}

Fight::~Fight() {
}

void Fight::printStatus() const {

	std::cout << m_animal1.getName() << ": " << std::endl;
	m_animal1.printHealth();
	std::cout << m_animal2.getName() << ": " << std::endl;
	m_animal2.printHealth();

}

void Fight::oneAttacks(const std::shared_ptr<Attack> atk) {

	const EffectiveType eff = atk->getType().getEffectTypeAgainst(m_animal2.getType());
	if (m_logging) printAttack(m_animal1.getName(), atk->getName(), eff);

	m_animal1.useAttack(atk, m_animal2);

}

void Fight::oneAttacksRandom() {

	const std::shared_ptr<Attack> atk = m_animal1.getRandomAttack();
	
	const EffectiveType eff = atk->getType().getEffectTypeAgainst(m_animal2.getType());
	if (m_logging) printAttack(m_animal1.getName(), atk->getName(), eff);

	m_animal1.useAttack(atk, m_animal2);

}

void Fight::twoAttacks(const std::shared_ptr<Attack> atk) {

	const EffectiveType eff = atk->getType().getEffectTypeAgainst(m_animal1.getType());
	if (m_logging) printAttack(m_animal2.getName(), atk->getName(), eff);

	m_animal2.useAttack(atk, m_animal1);

}

void Fight::twoAttacksRandom() {

	const std::shared_ptr<Attack> atk = m_animal2.getRandomAttack();
	
	const EffectiveType eff = atk->getType().getEffectTypeAgainst(m_animal1.getType());
	if (m_logging) printAttack(m_animal2.getName(), atk->getName(), eff);

	m_animal2.useAttack(atk, m_animal1);

}

void Fight::printAttack(const std::string & animalName, const std::string & atkName, const EffectiveType & eff) const {

	std::cout << animalName << " uses " << atkName << "!" << std::endl;
	if (eff != EffectiveType::Neutral && eff != EffectiveType::Zero) {
		std::cout << "It is " << Database::getStringFromEffectivenessType(eff) << "!" << std::endl;
	} else if (eff == EffectiveType::Zero) {
		std::cout << "It has no effect!" << std::endl;
	}

}
