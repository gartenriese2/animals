#ifndef _ANIMAL_H
#define _ANIMAL_H

#include "stats.hpp"
#include "attackset.hpp"

class Animal {
	
	public:
		
		Animal(const std::string &, const Type &, const Stats &, const AttackSet &, const unsigned int);
		Animal(const Animal &);
		~Animal();

		void printHealth() const;
		void printInfo() const;

		void reset();

		const std::string & getName() const { return m_name; }
		const std::string getNameCopy() const { return m_name; }
		const Type & getType() const { return m_type; }
		const Type getTypeCopy() const { return m_type; }
		const Stats & getStats() const { return m_stats; }
		const Stats getStatsCopy() const { return m_stats; }
		const AttackSet & getAttackSet() const { return m_attackSet; }
		const AttackSet getAttackSetCopy() const { return m_attackSet; }
		const std::vector<std::shared_ptr<Attack>> & getAttacks() const { return m_moves; }
		const unsigned int getActualHealth() const { return m_stats.getActualHealth(); }
		const unsigned int getMaxHealth() const { return m_stats.getHealth(); }
		const unsigned int getMaxAttack() const { return m_stats.getAttack(); }
		const unsigned int getMaxDefense() const { return m_stats.getDefense(); }
		const unsigned int getActualSpeed() const { return m_stats.getActualSpeed(); }
		const unsigned int getMaxSpeed() const { return m_stats.getSpeed(); }
		const unsigned int getLevel() const { return m_level; }
		void setLevel(const unsigned int);
		void levelUp();
		const unsigned int getExp() const { return m_exp; }
		const unsigned int getNeededExp() const;
		void gainExp(unsigned int);
		void changeHealth(const int h);
		const std::shared_ptr<Attack> getRandomAttack() const;

		void heal() { m_stats.setActualHealth(getMaxHealth()); }

		static const std::map<std::string, Animal> & getAnimals();
		static const Animal & getAnimal(const std::string);
		static const Animal & getRandomAnimal();

	private:

		std::string m_name;
		Type m_type;
		Stats m_stats;
		AttackSet m_attackSet;

		unsigned int m_level;
		unsigned int m_exp;
		std::vector<std::shared_ptr<Attack>> m_moves;

		void fillActualAttacks();
		bool checkForNewMoves();
	
};

#endif // _ANIMAL_H