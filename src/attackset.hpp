#ifndef _ATTACKSET_HPP
#define _ATTACKSET_HPP

#include "attack.hpp"

class AttackSet {
	
	public:

		AttackSet(const std::multimap<unsigned int, std::shared_ptr<Attack>> &);
		~AttackSet();

	private:

		std::multimap<unsigned int, std::shared_ptr<Attack>> m_set;

};

#endif // _ATTACKSET_HPP