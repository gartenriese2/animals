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

		ArrowKey getArrowKey();

		const std::shared_ptr<Attack> chooseAttack(const std::vector<std::shared_ptr<Attack>> &);
		const std::shared_ptr<Attack> chooseAttackWithArrowKeys(const std::vector<std::shared_ptr<Attack>> &);

	private:

		void printAttacks(const std::vector<std::shared_ptr<Attack>> &);

};

#endif // _IO_HPP