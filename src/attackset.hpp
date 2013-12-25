#ifndef _ATTACKSET_HPP
#define _ATTACKSET_HPP

#include "attack.hpp"

using AttackSetMap = std::multimap<unsigned int, std::shared_ptr<Attack>>;

class AttackSet {
	
	public:

		AttackSet(const AttackSetMap &);
		~AttackSet();

        const AttackSetMap & get() const { return m_set; }

	private:

		AttackSetMap m_set;

};

#endif // _ATTACKSET_HPP