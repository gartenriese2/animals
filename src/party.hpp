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

		const std::string heal();

	private:

		std::vector<Animal> m_animals;

};

#endif // _PARTY_HPP