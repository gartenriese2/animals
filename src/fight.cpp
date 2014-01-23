#include "fight.hpp"

#include <iostream>
#include <math.h>
#include <chrono>
#include <thread>

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
	
	std::cout << m_animal1.getName() << " (lvl." << m_animal1.getLevel() << "): " << std::endl;
	m_animal1.printHealth();
	std::cout << m_animal2.getName() << " (lvl." << m_animal2.getLevel() << "): " << std::endl;
	m_animal2.printHealth();

	std::cout << "\033[4B";

}

void Fight::refreshHealth(float oldRatio, float newRatio) const {

	if (oldRatio < newRatio) {
			for (float old = oldRatio; old < newRatio; old += 0.02f) {

				std::cout << "\r\033[K";
				unsigned int bars = round(old * 50);
				std::cout << "Health: [";
				for (unsigned int i = 0; i < 50; ++i) {
					if (i < bars) std::cout << "|";
					else std::cout << ".";
				}
				std::cout << "]" << std::flush;
				std::this_thread::sleep_for(std::chrono::milliseconds(100));

			}
		} else {
			for (float old = oldRatio; old > newRatio; old -= 0.02f) {

				std::cout << "\r\033[K";
				unsigned int bars = round(old * 50);
				std::cout << "Health: [";
				for (unsigned int i = 0; i < 50; ++i) {
					if (i < bars) std::cout << "|";
					else std::cout << ".";
				}
				std::cout << "]" << std::flush;
				std::this_thread::sleep_for(std::chrono::milliseconds(100));

			}
		}

}

void Fight::refreshAnimal1HealthOutput(unsigned int oldHealth, unsigned int newHealth) const {
	if (oldHealth != newHealth) {

		std::cout << "\r\033[7A";

		unsigned int maxHealth = m_animal1.getMaxHealth();
		float oldRatio = static_cast<float>(oldHealth) / static_cast<float>(maxHealth);
		float newRatio = static_cast<float>(newHealth) / static_cast<float>(maxHealth);
		refreshHealth(oldRatio, newRatio);
		
		std::cout << "\033[7B";

	}
}

void Fight::refreshAnimal2HealthOutput(unsigned int oldHealth, unsigned int newHealth) const {
	if (oldHealth != newHealth) {

		std::cout << "\033[5A";

		unsigned int maxHealth = m_animal2.getMaxHealth();
		float oldRatio = static_cast<float>(oldHealth) / static_cast<float>(maxHealth);
		float newRatio = static_cast<float>(newHealth) / static_cast<float>(maxHealth);
		refreshHealth(oldRatio, newRatio);

		std::cout << "\033[5B";

	}
}

void Fight::oneAttacks(const std::shared_ptr<Attack> atk) {

	// Console::addText(m_animal1.getName() + " uses " + atk->getName() + ".");
	// Console::printText();

	unsigned int oldHP1 = m_animal1.getActualHealth();
	unsigned int oldHP2 = m_animal2.getActualHealth();
	m_animal1.useAttack(atk, m_animal2);
	unsigned int newHP1 = m_animal1.getActualHealth();
	unsigned int newHP2 = m_animal2.getActualHealth();
	//refreshAnimal1HealthOutput(oldHP1, newHP1);
	//refreshAnimal2HealthOutput(oldHP2, newHP2);
	//printStatus();

	if (atk->getType().getBaseTypes().at(0) != BaseType::None) {
		const EffectiveType eff = atk->getType().getEffectTypeAgainst(m_animal2.getType());
		if (m_logging) printAttack(m_animal1.getName(), atk->getName(), eff);
	}

}

void Fight::oneAttacksRandom() {

	const std::shared_ptr<Attack> atk = m_animal1.getRandomAttack();

	// Console::addText(m_animal1.getName() + " uses " + atk->getName() + ".");
	
	unsigned int oldHP1 = m_animal1.getActualHealth();
	unsigned int oldHP2 = m_animal2.getActualHealth();
	m_animal1.useAttack(atk, m_animal2);
	unsigned int newHP1 = m_animal1.getActualHealth();
	unsigned int newHP2 = m_animal2.getActualHealth();
	//refreshAnimal1HealthOutput(oldHP1, newHP1);
	//refreshAnimal2HealthOutput(oldHP2, newHP2);
	//	printStatus();
	
	if (atk->getType().getBaseTypes().at(0) != BaseType::None) {
		const EffectiveType eff = atk->getType().getEffectTypeAgainst(m_animal2.getType());
		if (m_logging) printAttack(m_animal1.getName(), atk->getName(), eff);
	}

}

void Fight::twoAttacks(const std::shared_ptr<Attack> atk) {

	// Console::addText(m_animal2.getName() + " uses " + atk->getName() + ".");
	
	unsigned int oldHP1 = m_animal1.getActualHealth();
	unsigned int oldHP2 = m_animal2.getActualHealth();
	m_animal2.useAttack(atk, m_animal1);
	unsigned int newHP1 = m_animal1.getActualHealth();
	unsigned int newHP2 = m_animal2.getActualHealth();
	//refreshAnimal1HealthOutput(oldHP1, newHP1);
	//refreshAnimal2HealthOutput(oldHP2, newHP2);
	//printStatus();

	if (atk->getType().getBaseTypes().at(0) != BaseType::None) {
		const EffectiveType eff = atk->getType().getEffectTypeAgainst(m_animal1.getType());
		if (m_logging) printAttack(m_animal2.getName(), atk->getName(), eff);
	}

}

void Fight::twoAttacksRandom() {

	const std::shared_ptr<Attack> atk = m_animal2.getRandomAttack();
	
	// Console::addText(m_animal2.getName() + " uses " + atk->getName() + ".");
	// Console::printText();
	
	unsigned int oldHP1 = m_animal1.getActualHealth();
	unsigned int oldHP2 = m_animal2.getActualHealth();
	m_animal2.useAttack(atk, m_animal1);
	unsigned int newHP1 = m_animal1.getActualHealth();
	unsigned int newHP2 = m_animal2.getActualHealth();
	//refreshAnimal1HealthOutput(oldHP1, newHP1);
	//refreshAnimal2HealthOutput(oldHP2, newHP2);
	//printStatus();

	if (atk->getType().getBaseTypes().at(0) != BaseType::None) {
		const EffectiveType eff = atk->getType().getEffectTypeAgainst(m_animal1.getType());
		if (m_logging) printAttack(m_animal2.getName(), atk->getName(), eff);
	}

}

void Fight::printAttack(const std::string & animalName, const std::string & atkName, const EffectiveType & eff) const {

	if (eff != EffectiveType::Neutral && eff != EffectiveType::Zero) {
		// Console::addText("It is " + Database::getStringFromEffectivenessType(eff) + "!");
	} else if (eff == EffectiveType::Zero) {
		// Console::addText("It has no effect!");
	}

}
