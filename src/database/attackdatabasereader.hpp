#ifndef _ATTACKDATABASEREADER_HPP
#define _ATTACKDATABASEREADER_HPP

#include "databasereader.hpp"
#include "../type.hpp"

#include <string>
#include <unordered_map>

class AttackDatabaseReader : public DatabaseReader {

	public:

		AttackDatabaseReader();
		~AttackDatabaseReader();

		const Type getTypeFromEntry(const std::string &);
		const std::unordered_map<std::string, double> getMapFromEntry(const std::string &);

	private:

        const Type convertContentToType(const std::vector<std::string> &);
        const std::unordered_map<std::string, double> convertContentToMap(const std::vector<std::string> &);

};

#endif // _ATTACKDATABASEREADER_HPP
