#ifndef _PARTY_HPP
#define _PARTY_HPP

#include <vector>

#include "animal.hpp"

class Party {

	public:

		Party();
		~Party();

		unsigned int getSize() const { return m_animals.size(); }
		void addAnimal(const std::string &);
		Animal & getFrontAnimal();
		Animal & getFirstHealthyAnimal();
		Animal & getAnimal(unsigned int num) { if (num > getSize() - 1) abort(); else return m_animals[num]; }

		bool isHealthy() const;
		void heal();

	private:

		std::vector<Animal> m_animals;

};

#endif // _PARTY_HPP