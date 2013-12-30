#include "animal.hpp"

#include <stdlib.h>
#include <math.h>

static constexpr unsigned int k_healthBars = 50;
static constexpr unsigned int k_baseExpNeeds = 20;
static constexpr float k_lvlRatio = 30.f;
static constexpr float k_typeFit = 1.f;
static constexpr float k_typeNoFit = 0.8f;

Animal::Animal(const std::string & name, const Type & type,
	const AnimalStats & stats, AttackSet attackSet, const unsigned int level = 1)
  : m_name(name),
	m_type(type),
	m_stats(stats),
	m_attackSet(attackSet),
	m_level(1),
	m_exp(0)
{	
	fillActualAttacks();
	raiseLevels(level - 1);
}

Animal::Animal(const Animal & other)
  : m_name(other.getNameCopy()),
	m_type(other.getTypeCopy()),
	m_stats(other.getStatsCopy()),
	m_attackSet(other.getAttackSetCopy()),
	m_level(other.getLevel()),
	m_exp(other.getExp())
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

const AttackSet & Animal::getAttackSet() const {
	return m_attackSet;
}

AttackSet Animal::getAttackSetCopy() const {
	return m_attackSet;
}

void Animal::fillActualAttacks() {

	for (const auto i : m_attackSet.get()) {
		if (i.first == 1) m_moves.emplace_back(i.second);
	}

}

void Animal::printHealth() const {
	
	float factor = static_cast<float>(getActualHealth()) / static_cast<float>(getMaxHealth());
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
	std::cout << "Health:  " << getActualHealth() << "/" << getMaxHealth() << std::endl;
	std::cout << "Attack:  " << getMaxAttack() << std::endl;
	std::cout << "Defense: " << getMaxDefense() << std::endl;
	std::cout << "Speed:   " << getMaxSpeed() << std::endl;
	std::cout << "Moves:" << std::endl;
	for (const auto i : m_moves) {
		std::cout << "---- " << i->getName() << " (" << i->getFoeDamage() << ") ["
			<< i->getType() << "]" << std::endl;
	}
	std::cout << "------------------------" << std::endl;

}

void Animal::raiseLevels(const unsigned int lvl) {

	for (unsigned int i = 0; i < lvl; ++i) {
		levelUp();
	}

}

void Animal::changeHealth(const int h) {

	if (static_cast<int>(getActualHealth() + h) < 0) {
		m_stats.setActualHealth(0);
	} else {
		m_stats.setActualHealth(getActualHealth() + h);
	}

}

void Animal::modifyAttack(float f) {

	m_stats.setActualAttack(f * static_cast<float>(m_stats.getActualAttack()));

}

void Animal::modifyDefense(float f) {

	m_stats.setActualDefense(f * static_cast<float>(m_stats.getActualDefense()));

}

void Animal::modifySpeed(float f) {

	m_stats.setActualSpeed(f * static_cast<float>(m_stats.getActualSpeed()));

}

const unsigned int Animal::getNeededExp() const {

	return m_stats.getExpMultiplier() * (k_baseExpNeeds + 2.f * m_level * m_level);

}

void Animal::gainExp(unsigned int xp) {

	if (m_exp + xp > getNeededExp()) {
		xp -= (getNeededExp() - m_exp);
		levelUp();
		m_exp = 0;
		gainExp(xp);
	} else {
		m_exp += xp;
	}

}

void Animal::levelUp() {
	
	float healthRatio = static_cast<float>(m_stats.getActualHealth()) / static_cast<float>(m_stats.getHealth());
	float attackRatio = static_cast<float>(m_stats.getActualAttack()) / static_cast<float>(m_stats.getAttack());
	float defenseRatio = static_cast<float>(m_stats.getActualDefense()) / static_cast<float>(m_stats.getDefense());
	float speedRatio = static_cast<float>(m_stats.getActualSpeed()) / static_cast<float>(m_stats.getSpeed());
	++m_level;
	m_stats.setHealth(m_stats.getHealth() + round(m_stats.getHealthMultiplier() * sqrt(getLevel())));
	m_stats.setAttack(m_stats.getAttack() + round(m_stats.getAttackMultiplier() * sqrt(getLevel())));
	m_stats.setDefense(m_stats.getDefense() + round(m_stats.getDefenseMultiplier() * sqrt(getLevel())));
	m_stats.setSpeed(m_stats.getSpeed() + round(m_stats.getSpeedMultiplier() * sqrt(getLevel())));
	m_stats.setActualHealth(round(healthRatio * static_cast<float>(m_stats.getHealth())));
	m_stats.setActualAttack(round(attackRatio * static_cast<float>(m_stats.getAttack())));
	m_stats.setActualDefense(round(defenseRatio * static_cast<float>(m_stats.getDefense())));
	m_stats.setActualSpeed(round(speedRatio * static_cast<float>(m_stats.getSpeed())));

	std::cout << getName() << " reached level " << getLevel() << "!" << std::endl;

	checkForNewMoves();

}

bool Animal::checkForNewMoves() {

	const auto p = m_attackSet.get().equal_range(m_level);
	if (p.first == p.second) return false;
	for (auto i = p.first; i != p.second; ++i) {
		m_moves.emplace_back(i->second);
		std::cout << getName() << " learned " << i->second->getName() << std::endl;
	}
	return true;

}

void Animal::useAttack(std::shared_ptr<Attack> atk, Animal & foe) {

	float atkDefRatio = static_cast<float>(getActualAttack()) / static_cast<float>(foe.getActualDefense());
	float lvlRatio = static_cast<float>(getLevel()) / k_lvlRatio;
	float effValue = atk->getType().getEffectValueAgainst(foe.getType());
	float boost = atk->getType().isPartOf(getType()) ? k_typeFit : k_typeNoFit;
	int foeDmg = ceil(static_cast<float>(atk->getFoeDamage()) * atkDefRatio * lvlRatio * effValue * boost);

	foe.changeHealth(-foeDmg);
	foe.modifyAttack(atk->getFoeAttackModifier());
	foe.modifyDefense(atk->getFoeDefenseModifier());
	foe.modifySpeed(atk->getFoeSpeedModifier());

	changeHealth(-atk->getOwnDamage());
	modifyAttack(atk->getOwnAttackModifier());
	modifyDefense(atk->getOwnDefenseModifier());
	modifySpeed(atk->getOwnSpeedModifier());

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

using AnimalEntry = std::pair<std::string, Animal>;
using AttackSetEntry = std::pair<unsigned int, std::shared_ptr<Attack>>;

const std::map<std::string, Animal> & Animal::getAnimals() {	
	
	static std::map<std::string, Animal> s_animals {
		// Fire
		AnimalEntry("Firestarter", Animal("Firestarter",
										Type(BaseType::Fire),
										AnimalStats(12, 6, 5, 5,
											0.7f, 0.7f, 0.7f, 0.7f, 1.0f),
										AttackSet({
											AttackSetEntry(1, Attack::getAttack("Tackle")),
											AttackSetEntry(7, Attack::getAttack("Fire Spark")),
											AttackSetEntry(16, Attack::getAttack("Fire Blast"))
										})
										)),
		// FireWater
		AnimalEntry("Waterdevil", Animal("Waterdevil",
										Type(BaseType::Fire, BaseType::Water),
										AnimalStats(15, 4, 5, 4, 
											0.75f, 0.7f, 0.7f, 0.65f, 1.0f),
										AttackSet({
											AttackSetEntry(1, Attack::getAttack("Tackle")),
											AttackSetEntry(20, Attack::getAttack("Water Blast")),
											AttackSetEntry(20, Attack::getAttack("Fire Blast")),
											AttackSetEntry(50, Attack::getAttack("Hellfire"))
										})
										)),
		// FireGhost
		AnimalEntry("Firaspar", Animal("Firaspar",
										Type(BaseType::Fire, BaseType::Ghost),
										AnimalStats(10, 6, 5, 6, 
											0.75f, 0.75f, 0.7f, 0.7f, 1.0f),
										AttackSet({
											AttackSetEntry(1, Attack::getAttack("Spook")),
											AttackSetEntry(8, Attack::getAttack("Fire Spark")),
											AttackSetEntry(15, Attack::getAttack("Haunt")),
											AttackSetEntry(23, Attack::getAttack("Fire Ball")),
											AttackSetEntry(31, Attack::getAttack("Nightmare"))
										})
										)),
		// Water
		AnimalEntry("Waterstarter", Animal("Waterstarter",
										Type(BaseType::Water),
										AnimalStats(12, 5, 6, 5,
											0.7f, 0.7f, 0.7f, 0.7f, 1.0f),
										AttackSet({
											AttackSetEntry(1, Attack::getAttack("Tackle")),
											AttackSetEntry(7, Attack::getAttack("Water Splash")),
											AttackSetEntry(16, Attack::getAttack("Water Blast"))
										})
										)),
		// WaterPlant
		AnimalEntry("Duckweed", Animal("Duckweed",
										Type(BaseType::Plant, BaseType::Water),
										AnimalStats(12, 4, 3, 5,
											0.65f, 0.65f, 0.6f, 0.75f, 0.8f),
										AttackSet({
											AttackSetEntry(1, Attack::getAttack("Tackle")),
											AttackSetEntry(5, Attack::getAttack("Leaf Wrap")),
											AttackSetEntry(12, Attack::getAttack("Water Splash")),
											AttackSetEntry(19, Attack::getAttack("Twine")),
											AttackSetEntry(27, Attack::getAttack("Water Blast")),
										})
										)),
		// SnowAir
		AnimalEntry("Snowly", Animal("Snowly",
										Type(BaseType::Snow, BaseType::Air),
										AnimalStats(14, 6, 6, 5,
											0.75f, 0.7f, 0.7f, 0.7f, 1.0f),
										AttackSet({
											AttackSetEntry(1, Attack::getAttack("Claw")),
											AttackSetEntry(5, Attack::getAttack("Shove")),
											AttackSetEntry(11, Attack::getAttack("Ice Blow")),
											AttackSetEntry(14, Attack::getAttack("Snowball")),
											AttackSetEntry(34, Attack::getAttack("Snowstorm")),
											AttackSetEntry(51, Attack::getAttack("Avalanche")),
										})
										)),
		// Normal
		AnimalEntry("Mousey", Animal("Mousey",
										Type(BaseType::Normal),
										AnimalStats(8, 3, 3, 5,
											0.65f, 0.65f, 0.65f, 0.65f, 0.7f),
										AttackSet({
											AttackSetEntry(1, Attack::getAttack("Nudge")),
											AttackSetEntry(5, Attack::getAttack("Shove")),
											AttackSetEntry(10, Attack::getAttack("Tackle"))
										})
										)),
		// SteelUnderground
		AnimalEntry("Irobat", Animal("Irobat",
										Type(BaseType::Steel, BaseType::Underground),
										AnimalStats(9, 4, 7, 5,
											0.75f, 0.65f, 0.85f, 0.6f, 1.0f),
										AttackSet({
											AttackSetEntry(1, Attack::getAttack("Steel Blow")),
											AttackSetEntry(6, Attack::getAttack("Claw")),
											AttackSetEntry(9, Attack::getAttack("Sonar")),
											AttackSetEntry(21, Attack::getAttack("Subduct"))
										})
										)),
		// DarkMagic
		AnimalEntry("Nightfairy", Animal("Nightfairy",
										Type(BaseType::Magic, BaseType::Dark),
										AnimalStats(10, 7, 4, 8,
											0.6f, 0.8f, 0.6f, 0.75f, 1.5f),
										AttackSet({
											AttackSetEntry(1, Attack::getAttack("Nudge")),
											AttackSetEntry(6, Attack::getAttack("Hex")),
											AttackSetEntry(25, Attack::getAttack("Dark Shadow"))
										})
										)),
	};

	return s_animals;

}

std::ostream & operator<<(std::ostream & os, Animal animal) {
  
	animal.printInfo();
	return os;

}
