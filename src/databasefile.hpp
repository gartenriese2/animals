#ifndef _DATABASE_FILE_HPP
#define _DATABASE_FILE_HPP

#include <string>
#include <vector>

class DatabaseFile {

	public:

		DatabaseFile(const std::string &);

	private:

		void readIn();

		const std::string m_fileName;
		std::vector<std::string> m_lines;

};

#endif // _DATABASE_FILE_HPP