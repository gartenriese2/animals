#ifndef _ANIMAL_H
#define _ANIMAL_H

#include "type.hpp"
#include "attack.hpp"
#include "stats.hpp"

class Animal {
	
	public:
		
		Animal(const std::string &, const Type &, const Stats &, const std::vector<std::shared_ptr<Attack>> &);
		~Animal();

		void printHealth() const;
		void printInfo() const;

		const std::string & getName() const { return m_name; }
		const Type & getType() const { return m_type; }
		const Stats & getBaseStats() const { return m_baseStats; }
		const std::vector<std::shared_ptr<Attack>> & getAttacks() const { return m_moves; }
		const unsigned int getActualHealth() const { return m_actualHealth; }
		const unsigned int getMaxHealth() const;
		const unsigned int getAttack() const;
		const unsigned int getDefense() const;
		const unsigned int getLevel() const { return m_level; }
		void setLevel(const unsigned int lvl) { m_level = lvl; }
		void changeHealth(const int h);
		const std::shared_ptr<Attack> getRandomAttack() const;

		void levelUp() { m_level++; }
		void heal() { m_actualHealth = getMaxHealth(); }

	private:

		std::string m_name;
		Type m_type;
		Stats m_baseStats;
		unsigned int m_level;
		std::vector<std::shared_ptr<Attack>> m_moves;

		unsigned int m_actualHealth;

		

	
};

#endif // _ANIMAL_H