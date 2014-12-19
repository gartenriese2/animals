#ifndef _TYPE_H
#define _TYPE_H

#include <vector>
#include <iostream>

#include "database/database.hpp"

class Type {

	public:

		Type(const BaseType, const BaseType = BaseType::None);
		Type() { m_types.emplace_back(BaseType::None); }
		~Type();

		const std::string getString() const;
		const std::vector<BaseType> & getBaseTypes() const;

		float getEffectValueAgainst(const Type &) const;
		EffectiveType getEffectTypeAgainst(const Type &) const;
		const std::string getEffectStringAgainst(const Type & against) const;

		bool isPartOf(const Type &) const;

	private:

		friend std::ostream & operator<<(std::ostream &, Type);

		std::vector<BaseType> m_types;


};

std::ostream & operator<<(std::ostream & out, Type);

#endif // _TYPE_H
