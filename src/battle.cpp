#include "battle.hpp"

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
	} else {
		std::cout << m_animal2.getName() << " won!" << std::endl;
	}

}
