#ifndef _MENU_HPP
#define _MENU_HPP

#include <vector>
#include <string>

class Menu {

	public:

		Menu(const std::vector<std::string> &);

		const std::vector<std::string> & getEntries() const { return m_entries; }
		void activate() { m_choice = m_entries[0]; }

	private:

		std::vector<std::string> m_entries;
		std::string m_choice;

};

#endif // _MENU_HPP