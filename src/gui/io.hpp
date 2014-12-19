#ifndef _IO_
#define _IO_

#include <vector>
#include <memory>
#include <string>

#include "../attack.hpp"

enum class Key : char { NONE, UP, DOWN, LEFT, RIGHT, ENTER, MENU, ESCAPE };

class IO {

	public:

		static const std::shared_ptr<Attack> chooseAttack(const std::vector<std::shared_ptr<Attack>> &);
		static const std::string chooseStarter();

		static Key getKey();

	private:

		Key getKeyInstance() const;

		static IO & instance();

};

#endif // _IO_
