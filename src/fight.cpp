#include "fight.hpp"

#include <math.h>
#include <chrono>
#include <thread>

#include "gui/battleconsole.hpp"

//static constexpr float k_ratioStep = 0.02f;
static constexpr unsigned int k_ratioSteps = 400;
static constexpr unsigned int k_sleep = 2000;

Fight::Fight(Animal & own, Animal & foe, bool logging)
  : m_own(own), m_foe(foe), m_logging(logging)
{
}

Fight::~Fight() {
}

bool Fight::refreshOwnHealth(unsigned int oldHealth, unsigned int newHealth) const {

	if (oldHealth != newHealth) {

		unsigned int sleep = k_sleep;
		if (static_cast<float>(std::abs(static_cast<int>(oldHealth) - static_cast<int>(newHealth)))
			/ static_cast<float>(m_own.getMaxHealth()) < 0.25f)
			sleep /= 2;

		for (unsigned int i = 0; i < k_ratioSteps; ++i) {

			std::this_thread::sleep_for(std::chrono::milliseconds(sleep / k_ratioSteps));

			float health;
			if (oldHealth > newHealth) {
				health = static_cast<float>(oldHealth) - static_cast<float>(i + 1)
					/ static_cast<float>(k_ratioSteps) * static_cast<float>(oldHealth - newHealth);
			} else {
				health = static_cast<float>(oldHealth) + static_cast<float>(i + 1)
					/ static_cast<float>(k_ratioSteps) * static_cast<float>(newHealth - oldHealth);
			}

			BattleConsole::printOwn(m_own.getName(), m_own.getLevel(),
				health,	m_own.getMaxHealth(), m_own.getExp(), m_own.getNeededExp());

		}

		return true;

	}

	return false;

}

bool Fight::refreshFoeHealth(unsigned int oldHealth, unsigned int newHealth) const {

	if (oldHealth != newHealth) {

		unsigned int sleep = k_sleep;
		if (static_cast<float>(std::abs(static_cast<int>(oldHealth) - static_cast<int>(newHealth)))
			/ static_cast<float>(m_own.getMaxHealth()) < 0.25f)
			sleep /= 2;

		for (unsigned int i = 0; i < k_ratioSteps; ++i) {

			std::this_thread::sleep_for(std::chrono::milliseconds(sleep / k_ratioSteps));

			float health;
			if (oldHealth > newHealth) {
				health = static_cast<float>(oldHealth) - static_cast<float>(i + 1)
					/ static_cast<float>(k_ratioSteps) * static_cast<float>(oldHealth - newHealth);
			} else {
				health = static_cast<float>(oldHealth) + static_cast<float>(i + 1)
					/ static_cast<float>(k_ratioSteps) * static_cast<float>(newHealth - oldHealth);
			}

			BattleConsole::printFoe(m_foe.getName(), m_foe.getLevel(),
				health,	m_foe.getMaxHealth());

		}

		return true;

	}

	return false;

}

void Fight::ownAttacks(const std::shared_ptr<Attack> atk) {

	BattleConsole::emptyTextAutomatically(1000);
	BattleConsole::addTextAndPrint(m_own.getName() + " uses " + atk->getName() + ".");

	unsigned int oldHP1 = m_own.getActualHealth();
	unsigned int oldHP2 = m_foe.getActualHealth();
	bool hit = m_own.useAttack(atk, m_foe);
	unsigned int newHP1 = m_own.getActualHealth();
	unsigned int newHP2 = m_foe.getActualHealth();

	bool refreshFoe = refreshFoeHealth(oldHP2, newHP2);
	bool refreshOwn = refreshOwnHealth(oldHP1, newHP1);

	if (!refreshOwn && !refreshFoe) {
		BattleConsole::emptyTextAutomatically(1000);
	} else {
		BattleConsole::emptyTextAutomatically();
	}

	if (atk->getType().getBaseTypes().at(0) != BaseType::None && hit) {
		const EffectiveType eff = atk->getType().getEffectTypeAgainst(m_foe.getType());
		if (m_logging) printAttack(eff);
	}

}

void Fight::ownAttacksRandom() {

	const std::shared_ptr<Attack> atk = m_own.getRandomAttack();

	BattleConsole::emptyTextAutomatically(1000);
	BattleConsole::addTextAndPrint(m_own.getName() + " uses " + atk->getName() + ".");

	unsigned int oldHP1 = m_own.getActualHealth();
	unsigned int oldHP2 = m_foe.getActualHealth();
	bool hit = m_own.useAttack(atk, m_foe);
	unsigned int newHP1 = m_own.getActualHealth();
	unsigned int newHP2 = m_foe.getActualHealth();

	bool refreshFoe = refreshFoeHealth(oldHP2, newHP2);
	bool refreshOwn = refreshOwnHealth(oldHP1, newHP1);

	if (!refreshOwn && !refreshFoe) {
		BattleConsole::emptyTextAutomatically(1000);
	} else {
		BattleConsole::emptyTextAutomatically();
	}

	if (atk->getType().getBaseTypes().at(0) != BaseType::None && hit) {
		const EffectiveType eff = atk->getType().getEffectTypeAgainst(m_foe.getType());
		if (m_logging) printAttack(eff);
	}

}

void Fight::foeAttacks(const std::shared_ptr<Attack> atk) {

	BattleConsole::emptyTextAutomatically(1000);
	BattleConsole::addTextAndPrint(m_foe.getName() + " uses " + atk->getName() + ".");

	unsigned int oldHP1 = m_own.getActualHealth();
	unsigned int oldHP2 = m_foe.getActualHealth();
	bool hit = m_foe.useAttack(atk, m_own);
	unsigned int newHP1 = m_own.getActualHealth();
	unsigned int newHP2 = m_foe.getActualHealth();

	bool refreshOwn = refreshOwnHealth(oldHP1, newHP1);
	bool refreshFoe = refreshFoeHealth(oldHP2, newHP2);

	if (!refreshOwn && !refreshFoe) {
		BattleConsole::emptyTextAutomatically(1000);
	} else {
		BattleConsole::emptyTextAutomatically();
	}

	if (atk->getType().getBaseTypes().at(0) != BaseType::None && hit) {
		const EffectiveType eff = atk->getType().getEffectTypeAgainst(m_own.getType());
		if (m_logging) printAttack(eff);
	}

}

void Fight::foeAttacksRandom() {

	const std::shared_ptr<Attack> atk = m_foe.getRandomAttack();

	BattleConsole::emptyTextAutomatically(1000);
	BattleConsole::addTextAndPrint(m_foe.getName() + " uses " + atk->getName() + ".");

	unsigned int oldHP1 = m_own.getActualHealth();
	unsigned int oldHP2 = m_foe.getActualHealth();
	bool hit = m_foe.useAttack(atk, m_own);
	unsigned int newHP1 = m_own.getActualHealth();
	unsigned int newHP2 = m_foe.getActualHealth();

	bool refreshOwn = refreshOwnHealth(oldHP1, newHP1);
	bool refreshFoe = refreshFoeHealth(oldHP2, newHP2);

	if (!refreshOwn && !refreshFoe) {
		BattleConsole::emptyTextAutomatically(1000);
	} else {
		BattleConsole::emptyTextAutomatically();
	}

	if (atk->getType().getBaseTypes().at(0) != BaseType::None && hit) {
		const EffectiveType eff = atk->getType().getEffectTypeAgainst(m_own.getType());
		if (m_logging) printAttack(eff);
	}

}

void Fight::printAttack(const EffectiveType & eff) const {

	if (eff != EffectiveType::Neutral && eff != EffectiveType::Zero) {
		BattleConsole::addTextAndPrint("It is " + Database::getStringFromEffectivenessType(eff) + "!");
	} else if (eff == EffectiveType::Zero) {
		BattleConsole::addTextAndPrint("It has no effect!");
	}

}
