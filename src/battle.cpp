#include "battle.hpp"

#include "io.hpp"
#include "battleconsole.hpp"

#include <chrono>
#include <thread>

static IO s_io;

static constexpr unsigned int k_maxlvldiff = 50;
static constexpr float k_ratioStep = 0.02f;
static constexpr unsigned int k_sleep = 100;

Battle::Battle(Animal & a1, Animal & a2)
  : m_animal1(a1), m_animal2(a2)
{
}

Battle::~Battle() {
}

void Battle::addExp(Animal & winner, const Animal & loser) const {

	BattleConsole::emptyText();

	unsigned int loserStats = loser.getMaxHealth() + loser.getMaxAttack()
								+ loser.getMaxDefense() + loser.getMaxSpeed();
	float lvlDiff = static_cast<float>(static_cast<int>(k_maxlvldiff) + loser.getLevel() - winner.getLevel())
					/ static_cast<float>(k_maxlvldiff);
	if (lvlDiff < 0.f) lvlDiff = 0.f;
	unsigned int xpGain = static_cast<unsigned int>(static_cast<float>(loserStats) * lvlDiff);
	BattleConsole::addText(winner.getName() + " gains " + std::to_string(xpGain) + " experience points.");
	BattleConsole::print();

	unsigned int oldXP = winner.getExp();
	winner.gainExp(xpGain);
	unsigned int newXP = winner.getExp();

	if (oldXP != newXP) {

		unsigned int maxXP = m_animal1.getNeededExp();
		float oldRatio = static_cast<float>(oldXP) / static_cast<float>(maxXP);
		float newRatio = static_cast<float>(newXP) / static_cast<float>(maxXP);
		if (oldRatio < newRatio) {
			for (float old = oldRatio; old < newRatio; old += k_ratioStep) {
				std::this_thread::sleep_for(std::chrono::milliseconds(k_sleep));
				unsigned int xp = static_cast<unsigned int>(old * static_cast<float>(maxXP));
				BattleConsole::printOwn(m_animal1.getName(), m_animal1.getLevel(),
					m_animal1.getActualHealth(), m_animal1.getMaxHealth(), xp, m_animal1.getNeededExp());
			}
		} else {
			for (float old = oldRatio; old > newRatio; old -= k_ratioStep) {
				std::this_thread::sleep_for(std::chrono::milliseconds(k_sleep));
				unsigned int xp = static_cast<unsigned int>(old * static_cast<float>(maxXP));
				BattleConsole::printOwn(m_animal1.getName(), m_animal1.getLevel(),
					m_animal1.getActualHealth(), m_animal1.getMaxHealth(), xp, m_animal1.getNeededExp());
			}
		}
		
	}

}

void Battle::startUservsAIRandom() {

	Console::clear();
	BattleConsole::addText("You use " + m_animal1.getName() + ".");
	BattleConsole::print();
	BattleConsole::emptyText();

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

		BattleConsole::emptyText();

		std::shared_ptr<Attack> atk;
		atk = s_io.chooseAttack(m_animal1.getAttacks());
		
		if (m_animal1.getActualSpeed() >= m_animal2.getActualSpeed()) {
			
			f.oneAttacks(atk);
			if (m_animal2.getActualHealth() == 0) {
				BattleConsole::addText(m_animal2.getName() + " fainted!");
				break;
			}
			
			BattleConsole::printOwn(m_animal1.getName(), m_animal1.getLevel(), m_animal1.getActualHealth(),
				m_animal1.getMaxHealth(), m_animal1.getExp(), m_animal1.getNeededExp());
			BattleConsole::printFoe(m_animal2.getName(), m_animal2.getLevel(), m_animal2.getActualHealth(),
				m_animal2.getMaxHealth());
			BattleConsole::emptyText();

			f.twoAttacksRandom();
			if (m_animal1.getActualHealth() == 0) {
				BattleConsole::addText(m_animal1.getName() + " fainted!");
				break;
			}
		} else {
			f.twoAttacksRandom();
			if (m_animal1.getActualHealth() == 0) {
				BattleConsole::addText(m_animal1.getName() + " fainted!");
				break;
			}
			
			BattleConsole::printOwn(m_animal1.getName(), m_animal1.getLevel(), m_animal1.getActualHealth(),
				m_animal1.getMaxHealth(), m_animal1.getExp(), m_animal1.getNeededExp());
			BattleConsole::printFoe(m_animal2.getName(), m_animal2.getLevel(), m_animal2.getActualHealth(),
				m_animal2.getMaxHealth());
			BattleConsole::emptyText();

			f.oneAttacks(atk);
			if (m_animal2.getActualHealth() == 0) {
				BattleConsole::addText(m_animal2.getName() + " fainted!");
				break;
			}
		}
		
	}

	if (m_animal1.getActualHealth() > m_animal2.getActualHealth()) {
		BattleConsole::addText("You won!");
		BattleConsole::print();
		addExp(m_animal1, m_animal2);
	} else {
		BattleConsole::addText("You lost!");
		BattleConsole::print();
	}

	BattleConsole::emptyText();

}
