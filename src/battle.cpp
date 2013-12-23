#include "battle.hpp"

#include "io.hpp"

static IO s_io;

Battle::Battle(Animal & a1, Animal & a2)
  : m_animal1(a1), m_animal2(a2)
{
	std::cout << "------------------------" << std::endl;
	std::cout << m_animal1.getName() << " vs. " << m_animal2.getName() << std::endl;
	std::cout << "------------------------" << std::endl;
	m_animal1.printInfo();
	m_animal2.printInfo();
}

Battle::~Battle() {
}

void Battle::addExp() const {

	unsigned int foeStats = m_animal2.getMaxHealth() + m_animal2.getAttack() + m_animal2.getDefense();
	foeStats *= m_animal2.getLevel() / m_animal1.getLevel();
	std::cout << m_animal1.getName() << " gains " << foeStats << " experience points." << std::endl;
	m_animal1.gainExp(foeStats);

}

void Battle::startAIvsAIRandom(const bool log) {

	Fight f(m_animal1, m_animal2, log);

	unsigned int roundCount = 1;
	while(m_animal1.getActualHealth() != 0 && m_animal2.getActualHealth() != 0) {
		
		if (log) {
			std::cout << std::endl << std::endl;
			std::cout << "############" << std::endl;
			std::cout << "# Round " << ((roundCount < 10) ? "0" : "") << roundCount << " #" << std::endl;
			std::cout << "############" << std::endl;

			f.printStatus();
			std::cout << std::endl;
		}

		f.oneAttacksRandom();
		if (m_animal2.getActualHealth() == 0) {
			if (log) std::cout << std::endl << m_animal2.getName() << " fainted!" << std::endl << std::endl;
			break;
		}
		f.twoAttacksRandom();
		if (m_animal1.getActualHealth() == 0) {
			if (log) std::cout << std::endl << m_animal1.getName() << " fainted!" << std::endl << std::endl;
			break;
		}

		++roundCount;
		
	}
	
	if (m_animal1.getActualHealth() > m_animal2.getActualHealth()) {
		std::cout << m_animal1.getName() << " won!" << std::endl;
		addExp();
	} else {
		std::cout << m_animal2.getName() << " won!" << std::endl;
	}

}

void Battle::startUservsAIRandom() {

	std::cout << "You use " << m_animal1.getName() << std::endl;

	Fight f(m_animal1, m_animal2, true);

	unsigned int roundCount = 1;
	while(m_animal1.getActualHealth() != 0 && m_animal2.getActualHealth() != 0) {
		
		std::cout << std::endl << std::endl;
		std::cout << "############" << std::endl;
		std::cout << "# Round " << ((roundCount < 10) ? "0" : "") << roundCount << " #" << std::endl;
		std::cout << "############" << std::endl;

		f.printStatus();
		std::cout << std::endl;

		std::shared_ptr<Attack> atk;
		while (!(atk = s_io.chooseAttack(m_animal1.getAttacks())));
		f.oneAttacks(atk);
		if (m_animal2.getActualHealth() == 0) {
			std::cout << std::endl << m_animal2.getName() << " fainted!" << std::endl << std::endl;
			break;
		}
		f.twoAttacksRandom();
		if (m_animal1.getActualHealth() == 0) {
			std::cout << std::endl << m_animal1.getName() << " fainted!" << std::endl << std::endl;
			break;
		}

		++roundCount;
		
	}
	
	if (m_animal1.getActualHealth() > m_animal2.getActualHealth()) {
		std::cout << "You won!" << std::endl;
		addExp();
	} else {
		std::cout << "You lost!" << std::endl;
	}

}
