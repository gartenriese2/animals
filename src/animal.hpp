#ifndef _ANIMAL_H
#define _ANIMAL_H

#include "animalstats.hpp"
#include "attackset.hpp"

class Animal {

	public:

		Animal(const std::string &, const Type &, const AnimalStats &, AttackSet,
			const unsigned int, const std::pair<unsigned int,std::string>);
		Animal(const Animal &);
		~Animal();

		void setLog(bool b) { m_log = b; }

		const std::string & getName() const { return m_name; }
		const std::string getNameCopy() const { return m_name; }
		const Type & getType() const { return m_type; }
		const Type getTypeCopy() const { return m_type; }
		const AnimalStats & getStats() const { return m_stats; }
		const AnimalStats getStatsCopy() const { return m_stats; }
		const AttackSet & getAttackSet() const;
		AttackSet getAttackSetCopy() const;
		const std::vector<std::shared_ptr<Attack>> & getAttacks() const { return m_moves; }
		unsigned int getActualHealth() const { return m_stats.getActualHealth(); }
		unsigned int getMaxHealth() const { return m_stats.getHealth(); }
		unsigned int getActualAttack() const { return m_stats.getActualAttack(); }
		unsigned int getMaxAttack() const { return m_stats.getAttack(); }
		unsigned int getActualDefense() const { return m_stats.getActualDefense(); }
		unsigned int getMaxDefense() const { return m_stats.getDefense(); }
		unsigned int getActualSpeed() const { return m_stats.getActualSpeed(); }
		unsigned int getMaxSpeed() const { return m_stats.getSpeed(); }
		unsigned int getLevel() const { return m_level; }
		bool isWild() const { return m_isWild; }
		void setWild(bool wild) { m_isWild = wild; }
		const std::pair<unsigned int, std::string> & getEvolve() const { return m_evolve; }
		const std::pair<unsigned int, std::string> getEvolveCopy() const { return m_evolve; }

		void raiseLevels(const unsigned int);

		unsigned int getExp() const { return m_exp; }
		unsigned int getNeededExp() const;
		void showExpGain(unsigned int from, unsigned int to) const;
		void gainExp(unsigned int);
		void changeHealth(const int h);
		bool useAttack(std::shared_ptr<Attack>, Animal &);
		const std::shared_ptr<Attack> getRandomAttack() const;

		void heal();
		bool modifyAttack(double);
		bool modifyDefense(double);
		bool modifySpeed(double);
		bool modifyHealth(float);
		void resetBattleStats();

		static const std::map<std::string, Animal> & getAnimals();
		static const Animal & getAnimal(const std::string);
		static const Animal & getRandomAnimal();
		static std::vector<Animal> getAnimalVector();
		static void printAnimalsSortByAllStats(unsigned int);
		static bool allStatsSort(Animal, Animal);
		static void printAnimalsSortByHealth(unsigned int);
		static bool healthSort(Animal, Animal);
		static void printAnimalsSortByAttack(unsigned int);
		static bool attackSort(Animal, Animal);
		static void printAnimalsSortByDefense(unsigned int);
		static bool defenseSort(Animal, Animal);
		static void printAnimalsSortBySpeed(unsigned int);
		static bool speedSort(Animal, Animal);

	private:

		bool m_log;

		std::string m_name;
		Type m_type;
		AnimalStats m_stats;
		AttackSet m_attackSet;
		bool m_isWild;

		unsigned int m_level;
		unsigned int m_exp;
		std::vector<std::shared_ptr<Attack>> m_moves;

		std::pair<unsigned int, std::string> m_evolve;

		void fillActualAttacks();
		bool checkForNewMoves();
		void levelUp();
		void evolveInto(const Animal &);

};

std::ostream & operator<<(std::ostream & out, Animal);

#endif // _ANIMAL_H
