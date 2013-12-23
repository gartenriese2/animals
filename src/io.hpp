#ifndef _IO_HPP
#define _IO_HPP

#include <iostream>
#include <vector>

#include "attack.hpp"

class IO {

    public:

        IO();
        ~IO();

        const std::shared_ptr<Attack> chooseAttack(const std::vector<std::shared_ptr<Attack>> &);


};

#endif // _IO_HPP