#ifndef _DATABASEREADER_HPP
#define _DATABASEREADER_HPP

#include <fstream>

class DatabaseReader {

	public:

		DatabaseReader();
		virtual ~DatabaseReader();

		virtual void openFile() = 0;

	protected:

		std::ifstream m_file;

		void goToNextLine();
		const char getNextTag();
		const std::string nextEntry();
		const std::string getNextWord();
		const std::string getNextContent();
		const std::string getTagContentFromEntry(const char &, const std::string &);

};

#endif // _DATABASEREADER_HPP