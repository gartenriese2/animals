#include "animal.hpp"

#include <stdlib.h>
#include <math.h>

static constexpr unsigned int k_healthBars = 50;
static constexpr unsigned int k_baseExpNeeds = 50;

const std::map<std::string, Animal> & Animal::getAnimals() {	
	
	static std::map<std::string, Animal> s_animals {
		// FireWater
		std::pair<std::string, Animal>("Waterdevil", Animal("Waterdevil",
															Type(BaseType::Fire, BaseType::Water),
															Stats(20, 18, 22, 2.4f, 1.0f),
															{Attack::getAttack("Tackle"),
																Attack::getAttack("Water Blast"),
																Attack::getAttack("Fire Blast")})),
		// WaterPlant
		std::pair<std::string, Animal>("Duckweed", Animal("Duckweed",
															Type(BaseType::Plant, BaseType::Water),
															Stats(16, 17, 16, 1.8f, 0.8f),
															{Attack::getAttack("Tackle"),
																Attack::getAttack("Water Blast"),
																Attack::getAttack("Twine")})),
		// DarkMagic
		std::pair<std::string, Animal>("Nightfairy", Animal("Nightfairy",
															Type(BaseType::Magic, BaseType::Dark),
															Stats(18, 24, 14, 2.0f, 1.5f),
															{Attack::getAttack("Hex"),
																Attack::getAttack("Darkness")})) 
	};
	return s_animals;

}

Animal::Animal(const std::string & name, const Type & type, const Stats & stats, const std::vector<std::shared_ptr<Attack>> & moves)
  : m_name(name),
	m_type(type),
	m_baseStats(stats),
	m_level(1),
	m_exp(0),
	m_actualHealth(getMaxHealth())
{	
	for (const auto atk : moves) {
		m_moves.emplace_back(atk);
	}
}

Animal::Animal(const Animal & other)
  : m_name(other.getNameCopy()),
	m_type(other.getTypeCopy()),
	m_baseStats(other.getBaseStatsCopy()),
	m_level(other.getLevel()),
	m_exp(other.getExp()),
	m_actualHealth(other.getActualHealth())
{
	for (const auto atk : other.getAttacks()) {
		m_moves.emplace_back(atk);
	}
}

Animal::~Animal() {
}

const Animal & Animal::getAnimal(const std::string s) {

	if (getAnimals().count(s) == 0) {
		std::cout << "no such animal: " << s << std::endl;
		abort();
	}

	return getAnimals().at(s);

}

void Animal::printHealth() const {
	
	float factor = static_cast<float>(m_actualHealth) / static_cast<float>(getMaxHealth());
	factor *= k_healthBars;
	unsigned int bars = round(factor);
	std::cout << "Health: [";
	for (unsigned int i = 0; i < k_healthBars; ++i) {
		if (i < bars) std::cout << "|";
		else std::cout << ".";
	}
	std::cout << "]" << std::endl;

}

void Animal::printInfo() const {

	std::cout << "----------INFO----------" << std::endl;
	std::cout << "Name:    " << m_name << std::endl;
	std::cout << "Type:    " << m_type << std::endl;
	std::cout << "Level:   " << m_level << std::endl;
	std::cout << "XP:      " << m_exp << "/" << getNeededExp() << std::endl;
	std::cout << "Health:  " << m_actualHealth << "/" << getMaxHealth() << std::endl;
	std::cout << "Attack:  " << getAttack() << std::endl;
	std::cout << "Defense: " << getDefense() << std::endl;
	std::cout << "Moves:" << std::endl;
	for (const auto i : m_moves) {
		std::cout << "---- " << i->getName() << " (" << i->getDamage() << ") ["
			<< i->getType() << "]" << std::endl;
	}
	std::cout << "------------------------" << std::endl;

}

void Animal::changeHealth(const int h) {

	if (static_cast<int>(m_actualHealth + h) < 0) {
		m_actualHealth = 0;
	} else {
		m_actualHealth += h;
	}

}

const unsigned int Animal::getNeededExp() const {

	return m_baseStats.getExpMultiplier() * (k_baseExpNeeds + m_level * m_level);

}

void Animal::gainExp(const unsigned int xp) {

	if (m_exp + xp > getNeededExp()) {
		m_exp = (m_exp + xp) % getNeededExp();
		levelUp();
	} else {
		m_exp += xp;
	}

}

void Animal::levelUp() {
	float ratio = static_cast<float>(getActualHealth()) / static_cast<float>(getMaxHealth());
	++m_level;
	m_actualHealth = static_cast<unsigned int>(ratio * static_cast<float>(getMaxHealth()));
	std::cout << getName() << " reached level " << getLevel() << "!" << std::endl;
}

const unsigned int Animal::getMaxHealth() const {

	return m_baseStats.getHealth() + m_baseStats.getMultiplier() * m_level;

}

const unsigned int Animal::getAttack() const {

	return m_baseStats.getAttack() + m_baseStats.getMultiplier() * m_level;

}

const unsigned int Animal::getDefense() const {

	return m_baseStats.getDefense() + m_baseStats.getMultiplier() * m_level;

}

const std::shared_ptr<Attack> Animal::getRandomAttack() const {

	int choice = rand() % m_moves.size();
	return m_moves[choice];

}

const Animal & Animal::getRandomAnimal() {

	int choice = rand() % getAnimals().size();
	std::vector<std::string> v;
	for (auto i : getAnimals()) {
		v.emplace_back(i.first);
	}
	return getAnimal(v[choice]);

}
