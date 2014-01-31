#ifndef _ATTACKDATABASEREADER_HPP
#define _ATTACKDATABASEREADER_HPP

#include "databasereader.hpp"
#include "type.hpp"

#include <string>
#include <unordered_map>

class AttackDatabaseReader : public DatabaseReader {

	public:

		AttackDatabaseReader();
		~AttackDatabaseReader();
		
		const Type getTypeFromEntry(const std::string &);
		const std::unordered_map<std::string, double> getMapFromEntry(const std::string &);

	private:

		const std::string k_filename = "data/attacks.database";

        void openFile();

        const Type convertStringToType(const std::string &);
        const std::unordered_map<std::string, double> convertStringToMap(const std::string &);

};

#endif // _ATTACKDATABASEREADER_HPP