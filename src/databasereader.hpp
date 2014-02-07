#ifndef _DATABASEREADER_HPP
#define _DATABASEREADER_HPP

#include "databasefile.hpp"

#include <fstream>

class DatabaseReader {

	public:

		DatabaseReader(const std::string &);
		virtual ~DatabaseReader();

	protected:

		DatabaseFile m_file;

		const std::vector<std::string> getTagContentFromEntry(const char &, const std::string &);

};

#endif // _DATABASEREADER_HPP