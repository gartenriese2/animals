#include "battle.hpp"

#include "io.hpp"

static IO s_io;

static constexpr unsigned int k_maxlvldiff = 50;

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

void Battle::addExp(Animal & winner, const Animal & loser) const {

	unsigned int loserStats = loser.getMaxHealth() + loser.getMaxAttack()
								+ loser.getMaxDefense() + loser.getMaxSpeed();
	float lvlDiff = static_cast<float>(static_cast<int>(k_maxlvldiff) + loser.getLevel() - winner.getLevel())
					/ static_cast<float>(k_maxlvldiff);
	if (lvlDiff < 0.f) lvlDiff = 0.f;
	unsigned int xpGain = static_cast<unsigned int>(static_cast<float>(loserStats) * lvlDiff);
	std::cout << winner.getName() << " gains " << xpGain << " experience points." << std::endl;
	winner.gainExp(xpGain);

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

		if (m_animal1.getActualSpeed() >= m_animal2.getActualSpeed()) {
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
		} else {
			f.twoAttacksRandom();
			if (m_animal1.getActualHealth() == 0) {
				if (log) std::cout << std::endl << m_animal1.getName() << " fainted!" << std::endl << std::endl;
				break;
			}
			f.oneAttacksRandom();
			if (m_animal2.getActualHealth() == 0) {
				if (log) std::cout << std::endl << m_animal2.getName() << " fainted!" << std::endl << std::endl;
				break;
			}
		}
		
		++roundCount;
		
	}
	
	if (m_animal1.getActualHealth() > m_animal2.getActualHealth()) {
		std::cout << m_animal1.getName() << " won!" << std::endl;
		addExp(m_animal1, m_animal2);
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
		if (m_animal1.getActualSpeed() >= m_animal2.getActualSpeed()) {
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
		} else {
			f.twoAttacksRandom();
			if (m_animal1.getActualHealth() == 0) {
				std::cout << std::endl << m_animal1.getName() << " fainted!" << std::endl << std::endl;
				break;
			}
			f.oneAttacks(atk);
			if (m_animal2.getActualHealth() == 0) {
				std::cout << std::endl << m_animal2.getName() << " fainted!" << std::endl << std::endl;
				break;
			}
		}

		++roundCount;
		
	}
	
	if (m_animal1.getActualHealth() > m_animal2.getActualHealth()) {
		std::cout << "You won!" << std::endl;
		addExp(m_animal1, m_animal2);
	} else {
		std::cout << "You lost!" << std::endl;
	}

}

void Battle::startUservsUser() {

	std::cout << "Player 1 uses " << m_animal1.getName() << std::endl;
	std::cout << "Player 2 uses " << m_animal2.getName() << std::endl;

	Fight f(m_animal1, m_animal2, true);

	unsigned int roundCount = 1;
	while(m_animal1.getActualHealth() != 0 && m_animal2.getActualHealth() != 0) {
		
		std::cout << std::endl << std::endl;
		std::cout << "############" << std::endl;
		std::cout << "# Round " << ((roundCount < 10) ? "0" : "") << roundCount << " #" << std::endl;
		std::cout << "############" << std::endl;

		f.printStatus();
		std::cout << std::endl;

		std::shared_ptr<Attack> atk1;
		std::shared_ptr<Attack> atk2;
		while (!(atk1 = s_io.chooseAttack(m_animal1.getAttacks())));
		while (!(atk2 = s_io.chooseAttack(m_animal2.getAttacks())));
		if (m_animal1.getActualSpeed() >= m_animal2.getActualSpeed()) {
			f.oneAttacks(atk1);
			if (m_animal2.getActualHealth() == 0) {
				std::cout << std::endl << m_animal2.getName() << " fainted!" << std::endl << std::endl;
				break;
			}
			f.twoAttacks(atk2);
			if (m_animal1.getActualHealth() == 0) {
				std::cout << std::endl << m_animal1.getName() << " fainted!" << std::endl << std::endl;
				break;
			}
		} else {
			f.twoAttacks(atk2);
			if (m_animal1.getActualHealth() == 0) {
				std::cout << std::endl << m_animal1.getName() << " fainted!" << std::endl << std::endl;
				break;
			}
			f.oneAttacks(atk1);
			if (m_animal2.getActualHealth() == 0) {
				std::cout << std::endl << m_animal2.getName() << " fainted!" << std::endl << std::endl;
				break;
			}
		}

		++roundCount;
		
	}
	
	if (m_animal1.getActualHealth() > m_animal2.getActualHealth()) {
		std::cout << "Player 1 won!" << std::endl;
		addExp(m_animal1, m_animal2);
	} else {
		std::cout << "Player 2 won!" << std::endl;
	}

}
