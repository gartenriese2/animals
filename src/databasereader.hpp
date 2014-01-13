#ifndef _DATABASEREADER_HPP
#define _DATABASEREADER_HPP

#include <fstream>

enum Tag : char { END = 'e', NAME = 'n', BASE = 'b', PORTALTAG = 'p', LIKELYHOODS = 'l' };

class DatabaseReader {

	public:

		DatabaseReader();
		virtual ~DatabaseReader();

		virtual void openFile() = 0;
		virtual const std::string nextEntry() = 0;

	protected:

		std::ifstream m_file;

		void goToNextLine();
		Tag getNextTag();
		const std::string getNextWord();
		const std::string getNextContent();
		const std::string getTagContentFromEntry(const Tag &, const std::string &);

};

#endif // _DATABASEREADER_HPP