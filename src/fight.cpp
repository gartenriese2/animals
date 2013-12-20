#include "fight.hpp"

#include <iostream>

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

void Fight::oneAttacks(const Attack & atk) {

	const int dmg = calculateDamageAgainst(m_animal1, atk, m_animal2);
	const EffectiveType eff = atk.getType().getEffectTypeAgainst(m_animal2.getType());
	if (m_logging) printAttack(m_animal1.getName(), atk.getName(), dmg, eff);
	m_animal2.changeHealth(-dmg);

}

void Fight::oneAttacksRandom() {

	const Attack & atk = m_animal1.getRandomAttack();
	const int dmg = calculateDamageAgainst(m_animal1, atk, m_animal2);
	const EffectiveType eff = atk.getType().getEffectTypeAgainst(m_animal2.getType());
	if (m_logging) printAttack(m_animal1.getName(), atk.getName(), dmg, eff);
	m_animal2.changeHealth(-dmg);

}

void Fight::twoAttacks(const Attack & atk) {

	const int dmg = calculateDamageAgainst(m_animal2, atk, m_animal1);
	const EffectiveType eff = atk.getType().getEffectTypeAgainst(m_animal1.getType());
	if (m_logging) printAttack(m_animal2.getName(), atk.getName(), dmg, eff);
	m_animal1.changeHealth(-dmg);

}

void Fight::twoAttacksRandom() {

	const Attack & atk = m_animal2.getRandomAttack();
	const int dmg = calculateDamageAgainst(m_animal2, atk, m_animal1);
	const EffectiveType eff = atk.getType().getEffectTypeAgainst(m_animal1.getType());
	if (m_logging) printAttack(m_animal2.getName(), atk.getName(), dmg, eff);
	m_animal1.changeHealth(-dmg);

}

void Fight::printAttack(const std::string & animalName, const std::string & atkName, const int dmg, const EffectiveType & eff) const {

	std::cout << animalName << " uses " << atkName << "! (" << dmg << " dmg)" << std::endl;
	if (eff != EffectiveType::Neutral) {
		std::cout << "It is " << Database::getStringFromEffectivenessType(eff) << "!" << std::endl;
	}

}

const int Fight::calculateDamageAgainst(const Animal & a1, const Attack & atk, const Animal & a2) const {

	float factor = static_cast<float>(a1.getAttack()) / static_cast<float>(a2.getDefense());
	factor *= static_cast<float>(a1.getAttack()) / 100.f;
	float effect = atk.getType().getEffectValueAgainst(a2.getType());
	float boost = a1.getType().isPartOf(atk.getType()) ? 1.f : 0.75f;
	return static_cast<int>(static_cast<float>(atk.getDamage()) * factor * effect * boost);

}
