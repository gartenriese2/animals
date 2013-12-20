#ifndef _TYPE_H
#define _TYPE_H

#include <vector>
#include <iostream>

#include "database.hpp"

class Type {
	
	public:
		
		Type(const BaseType, const BaseType = BaseType::None);
		~Type();

		const std::vector<BaseType> & getBaseTypes() const;

		const float getEffectValueAgainst(const Type &) const;
		const EffectiveType getEffectTypeAgainst(const Type &) const;
		const std::string getEffectStringAgainst(const Type & against) const;

		const bool isPartOf(const Type &) const;

	private:

		const std::string getString() const;
		friend std::ostream & operator<<(std::ostream &, Type);

		std::vector<BaseType> m_types;

	
};

std::ostream & operator<<(std::ostream & out, Type);

#endif // _TYPE_H