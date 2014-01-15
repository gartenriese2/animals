#include "console.hpp"

#include <iostream>

static constexpr unsigned int k_outputLines = 2;
static constexpr unsigned int k_worldY = 20;
static constexpr unsigned int k_worldX = 50;

void Console::debug(const std::string & str) {
	instance().moveCursorToUpperBorder();
	
	std::cout << "\033[1A" << "\r\033[K" << "DEBUG: ";
	std::cout << str;

	instance().moveCursorToBottom();
}

void Console::print() {

	instance().printWorldLines();
	instance().printBorders();
	instance().printTextLines();
	
}

void Console::printText() {
	instance().printTextLines();
}

void Console::printInputText() {
	instance().printInputTextLines();
}

void Console::addText(const std::string & str) {
	instance().m_outputList.emplace_back(str);
}

void Console::setInputText(const std::string & str) {
	instance().m_inputText = str;
}

void Console::advanceText() {
	if (instance().m_outputList.size() > 0) {
		instance().m_outputList.pop_front();
	}
}

bool Console::textEmpty() {
	return instance().m_outputList.empty();
}

void Console::printArea() {
	instance().printWorldLines();
}

void Console::clearArea() {
	instance().printEmptyWorld();
}

void Console::setAreaBase(const twoDimArray & arr) {
	instance().m_area = arr;
}

void Console::setPosition(const Position & pos) {
	instance().m_pos = pos;
}


Console::Console() {
	for (unsigned int i = 0; i < 1 + k_outputLines + 2 + k_worldY; ++i) {
		std::cout << std::endl;
	}
}

void Console::printTextLines() {

	for (unsigned int i = 0; i < k_outputLines; ++i) {
		std::cout << "\033[1A" << "\r\033[K";
	}
	unsigned int count = 0;
	for (int i = k_outputLines - 1; i >= 0; --i) {
		if (count >= m_outputList.size()) {
			std::cout << "" << std::endl;
		} else {
			std::cout << m_outputList[count++] << std::endl;
		}
	}

}

void Console::printBorders() {

	moveCursorToLowerBorder();
	std::cout << "\r\033[K";
	for (unsigned int i = 0; i < k_worldX; ++i) {
		std::cout << "=";
	}

	moveCursorToUpperBorder();
	std::cout << "\r\033[K";
	for (unsigned int i = 0; i < k_worldX; ++i) {
		std::cout << "=";
	}

	moveCursorToBottom();

}

void Console::printInputTextLines() {

	std::cout << "\r\033[K";

	std::cout << m_inputText;

}

void Console::printEmptyWorld() {

	printBorders();
	moveCursorToTopOfArea();
	for (unsigned int i = 0; i < k_worldY; ++i) {
		std::cout << "\033[K\n";
	}
	moveCursorToBottom();


}

void Console::printWorldLines() {

	moveCursorToTopOfArea();

	int fromY = static_cast<int>(m_pos.getY()) - static_cast<int>(k_worldY) / 2;
	int toY = fromY + static_cast<int>(k_worldY);
	int fromX = static_cast<int>(m_pos.getX()) - static_cast<int>(k_worldX) / 2;
	int toX = fromX + static_cast<int>(k_worldX);

	for (int i = fromY; i < toY; ++i) {
		
		std::cout << "\r\033[K";

		if (i >= 0 && i < m_area.size()) {
					
			for (int j = fromX; j < toX; ++j) {
				if (j < 0 || j >= m_area[i].size()) {
					std::cout << " ";
				} else if (i == m_pos.getY() && j == m_pos.getX()) {
					std::cout << "P";
				} else {
					std::cout << m_area[i][j];
				}
			}

		}

		std::cout << std::endl;
		
	}
	
	moveCursorToBottom();

}

void Console::moveCursorToBottom() {

	std::cout << "\033[100B";
	std::cout << "\r";

}

void Console::moveCursorToBottomOfTextOutput() {

	moveCursorToBottom();
	std::cout << "\033[1A";

}

void Console::moveCursorToLowerBorder() {

	moveCursorToBottom();
	moveCursorToBottomOfTextOutput();
	std::cout << "\033[" << k_outputLines << "A";

}

void Console::moveCursorToBottomOfArea() {

	moveCursorToBottom();
	moveCursorToLowerBorder();
	std::cout << "\033[1A";

}

void Console::moveCursorToTopOfArea() {

	moveCursorToBottom();
	moveCursorToBottomOfArea();
	std::cout << "\033[" << k_worldY - 1 << "A";

}

void Console::moveCursorToUpperBorder() {

	moveCursorToBottom();
	moveCursorToTopOfArea();
	std::cout << "\033[1A";

}
