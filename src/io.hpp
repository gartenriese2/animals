#ifndef _IO_HPP
#define _IO_HPP

#include <iostream>
#include <vector>

#include "attack.hpp"

enum class Key : char { NONE, UP, DOWN, LEFT, RIGHT, ENTER, MENU };

class IO {

	public:

		IO();
		~IO();

		static Key getKey();
		static void emptyOutput();

		const std::shared_ptr<Attack> chooseAttackWithArrowKeys(const std::vector<std::shared_ptr<Attack>> &);
		const std::string chooseStarter() const;

	private:

		void printAttacks(const std::vector<std::shared_ptr<Attack>> &);
		Key getKeyInstance() const;

		static IO & instance();

};

#endif // _IO_HPP