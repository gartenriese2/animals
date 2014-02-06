#include "databasefile.hpp"

#include <fstream>

DatabaseFile::DatabaseFile(const std::string & fileName)
  : m_fileName(fileName)
{
}

void DatabaseFile::readIn() {

	std::fstream file(m_fileName);
	if (!file.good()) {
		abort();
	}
	std::string tmp;
	while (file.good()) {
		getline(file, tmp);
		m_lines.emplace_back(tmp);
	}
	file.close();

}
