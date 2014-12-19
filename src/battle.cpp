#include "battle.hpp"

#include "gui/io.hpp"
#include "gui/battleconsole.hpp"
#include "gui/console.hpp"

#include <chrono>
#include <thread>

static constexpr unsigned int k_maxlvldiff = 50;

Battle::Battle(Animal & a1, Animal & a2)
  : m_animal1(a1), m_animal2(a2)
{
}

Battle::~Battle() {
}

void Battle::addExp(Animal & winner, const Animal & loser) const {

	BattleConsole::emptyTextAutomatically(1000);

	unsigned int loserStats = loser.getMaxHealth() + loser.getMaxAttack()
								+ loser.getMaxDefense() + loser.getMaxSpeed();
	float lvlDiff = static_cast<float>(static_cast<int>(k_maxlvldiff) + loser.getLevel() - winner.getLevel())
					/ static_cast<float>(k_maxlvldiff);
	if (lvlDiff < 0.f) lvlDiff = 0.f;
	unsigned int xpGain = static_cast<unsigned int>(static_cast<float>(loserStats) * lvlDiff);
	BattleConsole::addTextAndPrint(winner.getName() + " gains " + std::to_string(xpGain) + " experience points.");

	winner.gainExp(xpGain);

}

void Battle::startUservsAIRandom() {

	Console::clear();
	BattleConsole::addTextAndPrint("You use " + m_animal1.getName() + ".");
	BattleConsole::emptyTextAutomatically(1000);

	BattleConsole::printOwn(m_animal1.getName(), m_animal1.getLevel(), m_animal1.getActualHealth(),
		m_animal1.getMaxHealth(), m_animal1.getExp(), m_animal1.getNeededExp());
	BattleConsole::printFoe(m_animal2.getName(), m_animal2.getLevel(), m_animal2.getActualHealth(),
		m_animal2.getMaxHealth());

	Fight f(m_animal1, m_animal2, true);

	while(m_animal1.getActualHealth() != 0 && m_animal2.getActualHealth() != 0) {

		BattleConsole::printOwn(m_animal1.getName(), m_animal1.getLevel(), m_animal1.getActualHealth(),
			m_animal1.getMaxHealth(), m_animal1.getExp(), m_animal1.getNeededExp());
		BattleConsole::printFoe(m_animal2.getName(), m_animal2.getLevel(), m_animal2.getActualHealth(),
			m_animal2.getMaxHealth());

		BattleConsole::emptyTextAutomatically(1000);

		std::shared_ptr<Attack> atk;
		atk = IO::chooseAttack(m_animal1.getAttacks());

		if (m_animal1.getActualSpeed() >= m_animal2.getActualSpeed()) {

			f.ownAttacks(atk);
			if (m_animal2.getActualHealth() == 0) {
				BattleConsole::addText(m_animal2.getName() + " fainted!");
				break;
			}

			BattleConsole::printOwn(m_animal1.getName(), m_animal1.getLevel(), m_animal1.getActualHealth(),
				m_animal1.getMaxHealth(), m_animal1.getExp(), m_animal1.getNeededExp());
			BattleConsole::printFoe(m_animal2.getName(), m_animal2.getLevel(), m_animal2.getActualHealth(),
				m_animal2.getMaxHealth());
			BattleConsole::emptyTextAutomatically(1000);

			f.foeAttacksRandom();
			if (m_animal1.getActualHealth() == 0) {
				BattleConsole::addText(m_animal1.getName() + " fainted!");
				break;
			}

		} else {

			f.foeAttacksRandom();
			if (m_animal1.getActualHealth() == 0) {
				BattleConsole::addText(m_animal1.getName() + " fainted!");
				break;
			}

			BattleConsole::printOwn(m_animal1.getName(), m_animal1.getLevel(), m_animal1.getActualHealth(),
				m_animal1.getMaxHealth(), m_animal1.getExp(), m_animal1.getNeededExp());
			BattleConsole::printFoe(m_animal2.getName(), m_animal2.getLevel(), m_animal2.getActualHealth(),
				m_animal2.getMaxHealth());
			BattleConsole::emptyTextAutomatically(1000);

			f.ownAttacks(atk);
			if (m_animal2.getActualHealth() == 0) {
				BattleConsole::addText(m_animal2.getName() + " fainted!");
				break;
			}

		}

	}

	if (m_animal1.getActualHealth() > m_animal2.getActualHealth()) {
		BattleConsole::addTextAndPrint("You won!");
		addExp(m_animal1, m_animal2);
	} else {
		BattleConsole::addTextAndPrint("You lost!");
	}

	BattleConsole::emptyTextAutomatically(1000);

}
