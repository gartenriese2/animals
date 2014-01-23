#include "battle.hpp"

#include "io.hpp"
#include "battleconsole.hpp"

static IO s_io;

static constexpr unsigned int k_maxlvldiff = 50;

Battle::Battle(Animal & a1, Animal & a2)
  : m_animal1(a1), m_animal2(a2)
{
	// std::cout << "------------------------" << std::endl;
	// std::cout << m_animal1.getName() << " vs. " << m_animal2.getName() << std::endl;
	// std::cout << "------------------------" << std::endl;
	// m_animal1.printInfo();
	// m_animal2.printInfo();
}

Battle::~Battle() {
}

void Battle::addExp(Animal & winner, const Animal & loser) const {

	unsigned int loserStats = loser.getMaxHealth() + loser.getMaxAttack()
								+ loser.getMaxDefense() + loser.getMaxSpeed();
	float lvlDiff = static_cast<float>(static_cast<int>(k_maxlvldiff) + loser.getLevel() - winner.getLevel())
					/ static_cast<float>(k_maxlvldiff);
	if (lvlDiff < 0.f) lvlDiff = 0.f;
	unsigned int xpGain = static_cast<unsigned int>(static_cast<float>(loserStats) * lvlDiff);
	BattleConsole::addText(winner.getName() + " gains " + std::to_string(xpGain) + " experience points.");
	BattleConsole::print();
	winner.gainExp(xpGain);

}

void Battle::startUservsAIRandom() {

	BattleConsole::addText("You use " + m_animal1.getName() + ".");
	BattleConsole::print();
	BattleConsole::emptyText();

	Fight f(m_animal1, m_animal2, true);

	while(m_animal1.getActualHealth() != 0 && m_animal2.getActualHealth() != 0) {

		//f.printStatus();

		std::shared_ptr<Attack> atk;
		atk = s_io.chooseAttack(m_animal1.getAttacks());
		
		if (m_animal1.getActualSpeed() >= m_animal2.getActualSpeed()) {
			f.oneAttacks(atk);
			if (m_animal2.getActualHealth() == 0) {
				BattleConsole::addText(m_animal2.getName() + " fainted!");
				break;
			}
			// IO::emptyOutput();
			//f.printStatus();
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
			// IO::emptyOutput();
			//f.printStatus();
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
