#ifndef _AREADATABASEREADER_HPP
#define _AREADATABASEREADER_HPP

#include "databasereader.hpp"

class AreaDatabaseReader : public DatabaseReader {

	public:

		AreaDatabaseReader();
		~AreaDatabaseReader();

		void openFile();
		const std::string nextEntry();
		const std::string getBaseFromEntry(const std::string &);
		const std::string getPortalsFromEntry(const std::string &);

	private:

		const std::string k_filename = "data/areas.database";

};

#endif // _AREADATABASEREADER_HPP