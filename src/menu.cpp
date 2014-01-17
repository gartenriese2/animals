#include "menu.hpp"

Menu::Menu(const std::vector<std::string> & entries)
  : m_entries(entries)
{
}

void Menu::activateLowerEntry() {
	for(unsigned int i = 0; i < m_entries.size(); ++i) {
		if (m_entries[i] == m_choice) {
			if (i == m_entries.size() - 1) {
				m_choice = m_entries[0];
			} else {
				m_choice = m_entries[i + 1];
			}
			break;
		}
	}
}

void Menu::activateUpperEntry() {
	for(unsigned int i = 0; i < m_entries.size(); ++i) {
		if (m_entries[i] == m_choice) {
			if (i == 0) {
				m_choice = m_entries[m_entries.size() - 1];
			} else {
				m_choice = m_entries[i - 1];
			}
			break;
		}
	}
}
