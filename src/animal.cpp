#include "animal.hpp"

#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <random>
#include <chrono>
#include <thread>

#include "console.hpp"

extern std::mt19937 generator;

static constexpr unsigned int k_healthBars = 50;
static constexpr unsigned int k_baseExpNeeds = 20;
static constexpr float k_lvlRatio = 30.f;
static constexpr float k_typeFit = 1.f;
static constexpr float k_typeNoFit = 0.8f;
static constexpr float k_criticalHit = 0.1f;

Animal::Animal(const std::string & name, const Type & type,	const AnimalStats & stats,
	AttackSet attackSet, const unsigned int level = 1, const std::pair<unsigned int, std::string> evolve = {0,""})
  : m_log(true),
  	m_name(name),
	m_type(type),
	m_stats(stats),
	m_attackSet(attackSet),
	m_level(1),
	m_exp(0),
	m_evolve(evolve)
{	
	fillActualAttacks();
	raiseLevels(level - 1);
}

Animal::Animal(const Animal & other)
  : m_log(true),
  	m_name(other.getNameCopy()),
	m_type(other.getTypeCopy()),
	m_stats(other.getStatsCopy()),
	m_attackSet(other.getAttackSetCopy()),
	m_level(other.getLevel()),
	m_exp(other.getExp()),
	m_evolve(other.getEvolve())
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

	bool tmp = m_log;
	m_log = false;
	for (unsigned int i = 0; i < lvl; ++i) {
		levelUp();
	}
	m_log = tmp;

}

void Animal::changeHealth(const int h) {

	if (static_cast<int>(getActualHealth() + h) < 0) {
		m_stats.setActualHealth(0);
	} else {
		m_stats.setActualHealth(getActualHealth() + h);
	}

}

void Animal::heal() { 

	m_stats.setActualHealth(getMaxHealth());
	m_stats.setActualAttack(getMaxAttack());
	m_stats.setActualDefense(getMaxDefense());
	m_stats.setActualSpeed(getMaxSpeed());

}

void Animal::modifyAttack(float f) {

	float f2 = f * static_cast<float>(getActualAttack());
	int n = f < 1.f ? floor(f2) : ceil(f2);
	if (n == 0) n = 1;
	m_stats.setActualAttack(n);

}

void Animal::modifyDefense(float f) {

	float f2 = f * static_cast<float>(getActualDefense());
	int n = f < 1.f ? floor(f2) : ceil(f2);
	if (n == 0) n = 1;
	m_stats.setActualDefense(n);

}

void Animal::modifySpeed(float f) {

	float f2 = f * static_cast<float>(getActualSpeed());
	int n = f < 1.f ? floor(f2) : ceil(f2);
	if (n == 0) n = 1;
	m_stats.setActualSpeed(n);

}

void Animal::modifyHealth(float f) {

	f *= static_cast<float>(getMaxHealth());
	int n = ceil(f);
	n = std::min(getActualHealth() + n, getMaxHealth());
	m_stats.setActualHealth(n);

}

void Animal::resetBattleStats() {

	m_stats.setActualAttack(getMaxAttack());
	m_stats.setActualDefense(getMaxDefense());
	m_stats.setActualSpeed(getMaxSpeed());

}

const unsigned int Animal::getNeededExp() const {

	return m_stats.getExpMultiplier() * (k_baseExpNeeds + 2.f * m_level * m_level);

}

void Animal::gainExp(unsigned int xp) {

	if (m_exp + xp >= getNeededExp()) {
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

	// if (m_log) Console::addText(getName() + " reached level " + std::to_string(getLevel()) + "!");
	if (m_evolve.first == m_level) {
		std::string oldName = getName();
		Animal evolvement(getAnimal(m_evolve.second));
		evolvement.raiseLevels(m_level);
		evolveInto(evolvement);
		// if (m_log) Console::addText(oldName + " evolved into " + getName() + "!");
	}

	m_stats.setHealth(m_stats.getHealth() + round(m_stats.getHealthMultiplier() * sqrt(getLevel())));
	m_stats.setAttack(m_stats.getAttack() + round(m_stats.getAttackMultiplier() * sqrt(getLevel())));
	m_stats.setDefense(m_stats.getDefense() + round(m_stats.getDefenseMultiplier() * sqrt(getLevel())));
	m_stats.setSpeed(m_stats.getSpeed() + round(m_stats.getSpeedMultiplier() * sqrt(getLevel())));
	m_stats.setActualHealth(round(healthRatio * static_cast<float>(m_stats.getHealth())));
	m_stats.setActualAttack(round(attackRatio * static_cast<float>(m_stats.getAttack())));
	m_stats.setActualDefense(round(defenseRatio * static_cast<float>(m_stats.getDefense())));
	m_stats.setActualSpeed(round(speedRatio * static_cast<float>(m_stats.getSpeed())));

	checkForNewMoves();

}

bool Animal::checkForNewMoves() {

	const auto p = m_attackSet.get().equal_range(m_level);
	if (p.first == p.second) return false;
	for (auto i = p.first; i != p.second; ++i) {
		m_moves.emplace_back(i->second);
		// if (m_log) Console::addText(getName() + " learned " + i->second->getName() + ".");
	}
	return true;

}

void Animal::evolveInto(const Animal & other) {

	m_name = other.getNameCopy();
	m_type = other.getTypeCopy();
	m_stats = other.getStatsCopy();
	m_attackSet = other.getAttackSetCopy();
	m_evolve = other.getEvolveCopy();

}

bool Animal::useAttack(std::shared_ptr<Attack> atk, Animal & foe) {

	std::uniform_real_distribution<float> dist(0.f, 1.f);

	if (dist(generator) > atk->getProbability()) {

		// if (m_log) Console::addText("Attack missed!");
		return false;

	} else {

		float atkDefRatio = static_cast<float>(getActualAttack()) / static_cast<float>(foe.getActualDefense());
		float lvlRatio = static_cast<float>(getLevel()) / k_lvlRatio;
		float effValue = atk->getType().getEffectValueAgainst(foe.getType());
		float boost = atk->getType().isPartOf(getType()) ? k_typeFit : k_typeNoFit;
		int foeDmg = ceil(static_cast<float>(atk->getFoeDamage()) * atkDefRatio * lvlRatio * effValue * boost);

		if (dist(generator) < k_criticalHit && foeDmg != 0) {
			foeDmg *= 2;
			// if (m_log) Console::addText("Critical Hit!");
		}

		// if (m_log && foeDmg != 0) std::cout << "DEBUG: " << foeDmg << "dmg" << std::endl;

		foe.changeHealth(-foeDmg);
		if (effValue != 0.f || atk->getType().getBaseTypes()[0] == BaseType::None) {
			foe.modifyAttack(atk->getFoeAttackModifier());
			foe.modifyDefense(atk->getFoeDefenseModifier());
			foe.modifySpeed(atk->getFoeSpeedModifier());
		}

		changeHealth(-atk->getOwnDamage());
		modifyAttack(atk->getOwnAttackModifier());
		modifyDefense(atk->getOwnDefenseModifier());
		modifySpeed(atk->getOwnSpeedModifier());
		modifyHealth(atk->getOwnHealthModifier());

		return true;

	}

}

const std::shared_ptr<Attack> Animal::getRandomAttack() const {

	std::uniform_int_distribution<int> dist(0, m_moves.size() - 1);
	int choice = dist(generator);
	return m_moves[choice];

}

const Animal & Animal::getRandomAnimal() {

	std::uniform_int_distribution<int> dist(0, getAnimals().size() - 1);
	int choice = dist(generator);

	std::vector<std::string> v;
	for (auto i : getAnimals()) {
		v.emplace_back(i.first);
	}

	return getAnimal(v[choice]);

}

std::vector<Animal> Animal::getAnimalVector() {

	std::vector<Animal> v;
	for (auto i : getAnimals()) {
		v.emplace_back(i.second);
	}
	return v;

}

void Animal::printAnimalsSortByAllStats(unsigned int lvl) {

	if (lvl == 0) ++lvl;
	std::vector<Animal> v = getAnimalVector();
	for (auto & i : v) {
		i.raiseLevels(lvl - 1);
	}
	std::sort(v.begin(), v.end(), allStatsSort);
	std::cout << "Animals (Lvl." << lvl << ") sorted by sum of all stats:" << std::endl;
	for (auto i : v) {
		std::cout << i.getName() << ": " << i.getMaxHealth() + i.getMaxAttack() + i.getMaxDefense() + i.getMaxSpeed() << std::endl;
	}

}

bool Animal::allStatsSort(Animal a1, Animal a2) {

	return (a1.getMaxHealth() + a1.getMaxAttack() + a1.getMaxDefense() + a1.getMaxSpeed()) >
		(a2.getMaxHealth() + a2.getMaxAttack() + a2.getMaxDefense() + a2.getMaxSpeed());

}

void Animal::printAnimalsSortByHealth(unsigned int lvl) {

	if (lvl == 0) ++lvl;
	std::vector<Animal> v = getAnimalVector();
	for (auto & i : v) {
		i.raiseLevels(lvl - 1);
	}
	std::sort(v.begin(), v.end(), healthSort);
	std::cout << "Animals (Lvl." << lvl << ") sorted by health:" << std::endl;
	for (auto i : v) {
		std::cout << i.getName() << ": " << i.getMaxHealth() << std::endl;
	}

}

bool Animal::healthSort(Animal a1, Animal a2) {

	return a1.getMaxHealth() > a2.getMaxHealth();

}

void Animal::printAnimalsSortByAttack(unsigned int lvl) {

	if (lvl == 0) ++lvl;
	std::vector<Animal> v = getAnimalVector();
	for (auto & i : v) {
		i.raiseLevels(lvl - 1);
	}
	std::sort(v.begin(), v.end(), attackSort);
	std::cout << "Animals (Lvl." << lvl << ") sorted by attack:" << std::endl;
	for (auto i : v) {
		std::cout << i.getName() << ": " << i.getMaxAttack() << std::endl;
	}

}

bool Animal::attackSort(Animal a1, Animal a2) {

	return a1.getMaxAttack() > a2.getMaxAttack();

}

void Animal::printAnimalsSortByDefense(unsigned int lvl) {

	if (lvl == 0) ++lvl;
	std::vector<Animal> v = getAnimalVector();
	for (auto & i : v) {
		i.raiseLevels(lvl - 1);
	}
	std::sort(v.begin(), v.end(), defenseSort);
	std::cout << "Animals (Lvl." << lvl << ") sorted by defense:" << std::endl;
	for (auto i : v) {
		std::cout << i.getName() << ": " << i.getMaxDefense() << std::endl;
	}

}

bool Animal::defenseSort(Animal a1, Animal a2) {

	return a1.getMaxDefense() > a2.getMaxDefense();

}

void Animal::printAnimalsSortBySpeed(unsigned int lvl) {

	if (lvl == 0) ++lvl;
	std::vector<Animal> v = getAnimalVector();
	for (auto & i : v) {
		i.raiseLevels(lvl - 1);
	}
	std::sort(v.begin(), v.end(), speedSort);
	std::cout << "Animals (Lvl." << lvl << ") sorted by speed:" << std::endl;
	for (auto i : v) {
		std::cout << i.getName() << ": " << i.getMaxSpeed() << std::endl;
	}

}

bool Animal::speedSort(Animal a1, Animal a2) {

	return a1.getMaxSpeed() > a2.getMaxSpeed();

}

using AnimalEntry = std::pair<std::string, Animal>;
using AttackSetEntry = std::pair<unsigned int, std::shared_ptr<Attack>>;

const std::map<std::string, Animal> & Animal::getAnimals() {
	
	static std::map<std::string, Animal> s_animals {
		// Fire
		AnimalEntry("Firax", Animal("Firax",
										Type(BaseType::Fire),
										AnimalStats(12, 6, 5, 5,
											0.9f, 0.72f, 0.7f, 0.7f, 1.0f),
										AttackSet({
											AttackSetEntry(1, Attack::getAttack("Tackle")),
											AttackSetEntry(5, Attack::getAttack("Glow")),
											AttackSetEntry(7, Attack::getAttack("Fire Spark"))
										}),
										1,
										{15, "Firaxas"}
										)),
		AnimalEntry("Firaxas", Animal("Firaxas",
										Type(BaseType::Fire),
										AnimalStats(12, 6, 5, 5,
											0.93f, 0.76f, 0.72f, 0.73f, 1.0f),
										AttackSet({
											AttackSetEntry(1, Attack::getAttack("Tackle")),
											AttackSetEntry(5, Attack::getAttack("Glow")),
											AttackSetEntry(7, Attack::getAttack("Fire Spark")),
											AttackSetEntry(16, Attack::getAttack("Fire Blast"))
										}),
										1,
										{30, "Firaxor"}
										)),
		AnimalEntry("Firaxor", Animal("Firaxor",
										Type(BaseType::Fire),
										AnimalStats(12, 6, 5, 5,
											0.96f, 0.8f, 0.74f, 0.76f, 1.0f),
										AttackSet({
											AttackSetEntry(1, Attack::getAttack("Tackle")),
											AttackSetEntry(5, Attack::getAttack("Glow")),
											AttackSetEntry(7, Attack::getAttack("Fire Spark")),
											AttackSetEntry(16, Attack::getAttack("Fire Blast"))
										})
										)),
		// FireWater
		AnimalEntry("Waterdevil", Animal("Waterdevil",
										Type(BaseType::Fire, BaseType::Water),
										AnimalStats(15, 4, 5, 4, 
											0.95f, 0.7f, 0.7f, 0.65f, 1.0f),
										AttackSet({
											AttackSetEntry(1, Attack::getAttack("Tackle")),
											AttackSetEntry(12, Attack::getAttack("Fire Ball")),
											AttackSetEntry(19, Attack::getAttack("Water Blast")),
											AttackSetEntry(27, Attack::getAttack("Fire Blast")),
											AttackSetEntry(54, Attack::getAttack("Hellfire"))
										})
										)),
		// FireGhost
		AnimalEntry("Firaspar", Animal("Firaspar",
										Type(BaseType::Fire, BaseType::Ghost),
										AnimalStats(10, 6, 5, 6, 
											0.95f, 0.75f, 0.7f, 0.7f, 1.0f),
										AttackSet({
											AttackSetEntry(1, Attack::getAttack("Spook")),
											AttackSetEntry(8, Attack::getAttack("Fire Spark")),
											AttackSetEntry(15, Attack::getAttack("Haunt")),
											AttackSetEntry(23, Attack::getAttack("Fire Ball")),
											AttackSetEntry(31, Attack::getAttack("Nightmare"))
										})
										)),
		// Water
		AnimalEntry("Aquax", Animal("Aquax",
										Type(BaseType::Water),
										AnimalStats(12, 5, 6, 5,
											0.9f, 0.7f, 0.72f, 0.7f, 1.0f),
										AttackSet({
											AttackSetEntry(1, Attack::getAttack("Tackle")),
											AttackSetEntry(5, Attack::getAttack("Intimidate")),
											AttackSetEntry(7, Attack::getAttack("Water Splash")),
											AttackSetEntry(16, Attack::getAttack("Water Blast"))
										})
										)),
		// WaterPlant
		AnimalEntry("Duckweed", Animal("Duckweed",
										Type(BaseType::Plant, BaseType::Water),
										AnimalStats(12, 4, 3, 5,
											0.85f, 0.65f, 0.6f, 0.75f, 0.8f),
										AttackSet({
											AttackSetEntry(1, Attack::getAttack("Tackle")),
											AttackSetEntry(3, Attack::getAttack("Intimidate")),
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
											0.95f, 0.7f, 0.7f, 0.7f, 1.0f),
										AttackSet({
											AttackSetEntry(1, Attack::getAttack("Claw")),
											AttackSetEntry(3, Attack::getAttack("Intimidate")),
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
											0.85f, 0.65f, 0.65f, 0.65f, 0.7f),
										AttackSet({
											AttackSetEntry(1, Attack::getAttack("Nudge")),
											AttackSetEntry(3, Attack::getAttack("Intimidate")),
											AttackSetEntry(5, Attack::getAttack("Shove")),
											AttackSetEntry(10, Attack::getAttack("Tackle"))
										})
										)),
		// SteelUnderground
		AnimalEntry("Irobat", Animal("Irobat",
										Type(BaseType::Steel, BaseType::Underground),
										AnimalStats(9, 4, 7, 5,
											0.95f, 0.65f, 0.85f, 0.6f, 1.0f),
										AttackSet({
											AttackSetEntry(1, Attack::getAttack("Steel Blow")),
											AttackSetEntry(3, Attack::getAttack("Intimidate")),
											AttackSetEntry(6, Attack::getAttack("Claw")),
											AttackSetEntry(9, Attack::getAttack("Sonar")),
											AttackSetEntry(15, Attack::getAttack("Steel Edge")),
											AttackSetEntry(21, Attack::getAttack("Subduct"))
										})
										)),
		// DarkMagic
		AnimalEntry("Nightfairy", Animal("Nightfairy",
										Type(BaseType::Magic, BaseType::Dark),
										AnimalStats(10, 7, 4, 8,
											0.8f, 0.91f, 0.6f, 0.78f, 1.5f),
										AttackSet({
											AttackSetEntry(1, Attack::getAttack("Nudge")),
											AttackSetEntry(3, Attack::getAttack("Dark Eye")),
											AttackSetEntry(6, Attack::getAttack("Hex")),
											AttackSetEntry(14, Attack::getAttack("Curse")),
											AttackSetEntry(25, Attack::getAttack("Dark Shadow"))
										})
										)),
		// Poison
		AnimalEntry("Arachnom", Animal("Arachnom",
										Type(BaseType::Poison),
										AnimalStats(12, 6, 6, 6,
											0.9f, 0.7f, 0.7f, 0.75f, 1.0f),
										AttackSet({
											AttackSetEntry(1, Attack::getAttack("Tackle")),
											AttackSetEntry(3, Attack::getAttack("Intimidate")),
											AttackSetEntry(6, Attack::getAttack("Sting")),
											AttackSetEntry(14, Attack::getAttack("Poison Sting"))
										})
										)),
		// TechnologyElectro
		AnimalEntry("Computo", Animal("Computo",
										Type(BaseType::Technology, BaseType::Electro),
										AnimalStats(12, 7, 5, 4,
											0.9f, 0.85f, 0.6f, 0.65f, 1.1f),
										AttackSet({
											AttackSetEntry(1, Attack::getAttack("Disc Throw")),
											AttackSetEntry(5, Attack::getAttack("Modern Shock")),
											AttackSetEntry(11, Attack::getAttack("Short Circuit")),
											AttackSetEntry(15, Attack::getAttack("Disc Cannon"))
										})
										)),
	};

	return s_animals;

}

std::ostream & operator<<(std::ostream & os, Animal animal) {
  
	animal.printInfo();
	return os;

}
