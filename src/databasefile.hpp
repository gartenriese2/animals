#ifndef _DATABASE_FILE_HPP
#define _DATABASE_FILE_HPP

#include <string>
#include <vector>

typedef std::pair<char, std::vector<std::string>> tagContent;
typedef std::pair<std::string, std::vector<tagContent>> entry;

class DatabaseFile {

	public:

		DatabaseFile(const std::string &);
		const std::vector<entry> & getEntries() const { return m_entries; }

	private:

		void readIn();
		void fillEntries();

		bool isTag(const std::string &) const;
		bool isEntryTag(const std::string &) const;

		const std::string m_fileName;
		std::vector<std::string> m_lines;
		std::vector<entry> m_entries;

};

#endif // _DATABASE_FILE_HPP