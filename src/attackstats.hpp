#ifndef _ATTACKSTATS_HPP
#define _ATTACKSTATS_HPP

#include "type.hpp"

#include <unordered_map>

class AttackStats {

	public:

		AttackStats(const Type &, const std::unordered_map<std::string, double> &);
		~AttackStats();

		const Type & getType() const { return m_type; }
		const std::unordered_map<std::string, double> & getMap() const { return m_values; }

	private:

		Type m_type;
		std::unordered_map<std::string, double> m_values;

		void initValues();

};

#endif // _ATTACKSTATS_HPP