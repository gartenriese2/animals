#ifndef _IO_HPP
#define _IO_HPP

#include <iostream>
#include <vector>

#include "attack.hpp"

enum class ArrowKey : char { NONE, UP, DOWN, LEFT, RIGHT, ENTER };

class IO {

	public:

		IO();
		~IO();

		static ArrowKey getKey();

		ArrowKey getArrowKey() const;

		const std::shared_ptr<Attack> chooseAttackWithArrowKeys(const std::vector<std::shared_ptr<Attack>> &);
		const std::string chooseStarter() const;

	private:

		void printAttacks(const std::vector<std::shared_ptr<Attack>> &);

		static IO & instance();

};

#endif // _IO_HPP