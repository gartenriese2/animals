#ifndef _ANIMAL_H
#define _ANIMAL_H

#include "type.hpp"
#include "attack.hpp"

class Animal {
	
	public:
		
		Animal(const Type &, const unsigned int, const std::vector<Attack> &);
		~Animal();

		const Type & getType() const { return m_type; }

		const unsigned int getHealth() const { return m_health; }
		void changeHealth(const int); 

	private:

		Type m_type;
		unsigned int m_health;
		std::vector<Attack> m_moves;

	
};

#endif // _ANIMAL_H