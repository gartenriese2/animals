#include "databasefile.hpp"

#include <fstream>
#include <iostream>

DatabaseFile::DatabaseFile(const std::string & fileName)
  : m_fileName(fileName)
{

	readIn();
	fillEntries();

}

void DatabaseFile::readIn() {

	std::fstream file(m_fileName);
	if (!file.good()) {
		abort();
	}

	std::string tmp;
	while (file.good()) {
		getline(file, tmp);
		if (tmp.substr(0, 2) == "<e") break;
		if (tmp[0] != '/') m_lines.emplace_back(tmp);
	}

	file.close();

}

void DatabaseFile::fillEntries() {

	m_entries.clear();

	std::string entry;
	std::vector<tagContent> entryContent;
	entryContent.clear();
	char c;
	std::vector<std::string> content;
	content.clear();

	for (const auto & line : m_lines) {

		if (isTag(line)) {

			// pack up content
			if (!content.empty()) {
				entryContent.emplace_back(std::make_pair(c, content));
				content.clear();
			}

			// new entry
			if (isEntryTag(line) && !entryContent.empty()) {

				m_entries.emplace_back(std::make_pair(entryContent[0].second[0], entryContent));
				entryContent.clear();

			}

			c = line[1];

		} else {

			content.emplace_back(line);

		}

	}

	if (!content.empty()) {
		// last entry
		entryContent.emplace_back(std::make_pair(c, content));
		m_entries.emplace_back(std::make_pair(entryContent[0].second[0], entryContent));
	}

}

bool DatabaseFile::isTag(const std::string & line) const {

	return line.size() > 1 && line[0] == '<';

}

bool DatabaseFile::isEntryTag(const std::string & tag) const {

	return isTag(tag) && tag[1] == 'n';

}
