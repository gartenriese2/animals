#include "fight.hpp"

#include <math.h>
#include <chrono>
#include <thread>

#include "battleconsole.hpp"

Fight::Fight(Animal & animal1, Animal & animal2, bool logging)
  : m_animal1(animal1), m_animal2(animal2), m_logging(logging)
{
}

Fight::~Fight() {
}

void Fight::refreshOwnHealth(unsigned int oldHealth, unsigned int newHealth) const {
	
	if (oldHealth != newHealth) {

		unsigned int maxHealth = m_animal1.getMaxHealth();
		float oldRatio = static_cast<float>(oldHealth) / static_cast<float>(maxHealth);
		float newRatio = static_cast<float>(newHealth) / static_cast<float>(maxHealth);
		if (oldRatio < newRatio) {
			for (float old = oldRatio; old < newRatio; old += 0.02f) {
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				BattleConsole::printOwn(m_animal1.getName(), m_animal1.getLevel(),
					static_cast<unsigned int>(old * static_cast<float>(maxHealth)),
					m_animal1.getMaxHealth(), m_animal1.getExp(), m_animal1.getNeededExp());
			}
		} else {
			for (float old = oldRatio; old > newRatio; old -= 0.02f) {
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				BattleConsole::printOwn(m_animal1.getName(), m_animal1.getLevel(),
					static_cast<unsigned int>(old * static_cast<float>(maxHealth)),
					m_animal1.getMaxHealth(), m_animal1.getExp(), m_animal1.getNeededExp());
			}
		}
		
	}

}

void Fight::refreshFoeHealth(unsigned int oldHealth, unsigned int newHealth) const {
	
	if (oldHealth != newHealth) {

		unsigned int maxHealth = m_animal2.getMaxHealth();
		float oldRatio = static_cast<float>(oldHealth) / static_cast<float>(maxHealth);
		float newRatio = static_cast<float>(newHealth) / static_cast<float>(maxHealth);
		if (oldRatio < newRatio) {
			for (float old = oldRatio; old < newRatio; old += 0.02f) {
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				BattleConsole::printFoe(m_animal2.getName(), m_animal2.getLevel(),
					static_cast<unsigned int>(old * static_cast<float>(maxHealth)),
					m_animal2.getMaxHealth());
			}
		} else {
			for (float old = oldRatio; old > newRatio; old -= 0.02f) {
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				BattleConsole::printFoe(m_animal2.getName(), m_animal2.getLevel(),
					static_cast<unsigned int>(old * static_cast<float>(maxHealth)),
					m_animal2.getMaxHealth());
			}
		}
		
	}

}

void Fight::oneAttacks(const std::shared_ptr<Attack> atk) {

	BattleConsole::addText(m_animal1.getName() + " uses " + atk->getName() + ".");
	BattleConsole::print();

	unsigned int oldHP1 = m_animal1.getActualHealth();
	unsigned int oldHP2 = m_animal2.getActualHealth();
	bool hit = m_animal1.useAttack(atk, m_animal2);
	unsigned int newHP1 = m_animal1.getActualHealth();
	unsigned int newHP2 = m_animal2.getActualHealth();
	refreshOwnHealth(oldHP1, newHP1);
	refreshFoeHealth(oldHP2, newHP2);

	if (atk->getType().getBaseTypes().at(0) != BaseType::None && hit) {
		const EffectiveType eff = atk->getType().getEffectTypeAgainst(m_animal2.getType());
		if (m_logging) printAttack(m_animal1.getName(), atk->getName(), eff);
	}

}

void Fight::oneAttacksRandom() {

	const std::shared_ptr<Attack> atk = m_animal1.getRandomAttack();

	BattleConsole::addText(m_animal1.getName() + " uses " + atk->getName() + ".");
	BattleConsole::print();
	
	unsigned int oldHP1 = m_animal1.getActualHealth();
	unsigned int oldHP2 = m_animal2.getActualHealth();
	bool hit = m_animal1.useAttack(atk, m_animal2);
	unsigned int newHP1 = m_animal1.getActualHealth();
	unsigned int newHP2 = m_animal2.getActualHealth();
	refreshOwnHealth(oldHP1, newHP1);
	refreshFoeHealth(oldHP2, newHP2);
	
	if (atk->getType().getBaseTypes().at(0) != BaseType::None && hit) {
		const EffectiveType eff = atk->getType().getEffectTypeAgainst(m_animal2.getType());
		if (m_logging) printAttack(m_animal1.getName(), atk->getName(), eff);
	}

}

void Fight::twoAttacks(const std::shared_ptr<Attack> atk) {

	BattleConsole::addText(m_animal2.getName() + " uses " + atk->getName() + ".");
	BattleConsole::print();
	
	unsigned int oldHP1 = m_animal1.getActualHealth();
	unsigned int oldHP2 = m_animal2.getActualHealth();
	bool hit = m_animal2.useAttack(atk, m_animal1);
	unsigned int newHP1 = m_animal1.getActualHealth();
	unsigned int newHP2 = m_animal2.getActualHealth();
	refreshOwnHealth(oldHP1, newHP1);
	refreshFoeHealth(oldHP2, newHP2);

	if (atk->getType().getBaseTypes().at(0) != BaseType::None && hit) {
		const EffectiveType eff = atk->getType().getEffectTypeAgainst(m_animal1.getType());
		if (m_logging) printAttack(m_animal2.getName(), atk->getName(), eff);
	}

}

void Fight::twoAttacksRandom() {

	const std::shared_ptr<Attack> atk = m_animal2.getRandomAttack();
	
	BattleConsole::addText(m_animal2.getName() + " uses " + atk->getName() + ".");
	BattleConsole::print();
	
	unsigned int oldHP1 = m_animal1.getActualHealth();
	unsigned int oldHP2 = m_animal2.getActualHealth();
	bool hit = m_animal2.useAttack(atk, m_animal1);
	unsigned int newHP1 = m_animal1.getActualHealth();
	unsigned int newHP2 = m_animal2.getActualHealth();
	refreshOwnHealth(oldHP1, newHP1);
	refreshFoeHealth(oldHP2, newHP2);

	if (atk->getType().getBaseTypes().at(0) != BaseType::None && hit) {
		const EffectiveType eff = atk->getType().getEffectTypeAgainst(m_animal1.getType());
		if (m_logging) printAttack(m_animal2.getName(), atk->getName(), eff);
	}

}

void Fight::printAttack(const std::string & animalName, const std::string & atkName, const EffectiveType & eff) const {

	if (eff != EffectiveType::Neutral && eff != EffectiveType::Zero) {
		BattleConsole::addText("It is " + Database::getStringFromEffectivenessType(eff) + "!");
	} else if (eff == EffectiveType::Zero) {
		BattleConsole::addText("It has no effect!");
	}

}
