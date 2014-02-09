#include "databasereader.hpp"

#include "typedefs.hpp"
#include "console.hpp"

DatabaseReader::DatabaseReader(const std::string & filename)
  : m_file(filename)
{
}

DatabaseReader::~DatabaseReader() {
}

const std::vector<std::string> DatabaseReader::getTagContentFromEntry(const char & tag, const std::string & name) {

	for (const auto & entry : m_file.getEntries()) {

		if (entry.first == name) {

			for (const auto & t : entry.second) {

				if (t.first == tag) return t.second;

			}

		}

	}

	std::vector<std::string> v;
	return v;

}
