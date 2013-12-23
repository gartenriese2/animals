#include "io.hpp"

IO::IO() {
}

IO::~IO() {
}

const std::shared_ptr<Attack> IO::chooseAttack(const std::vector<std::shared_ptr<Attack>> & attacks) {

    std::cout << "Possible Attacks: " << std::endl;

    for (const auto i : attacks) {
        std::cout << "---- " << i->getName() << std::endl;
    }

    std::cout << "Please enter the attack you choose: ";
    std::string str;
    std::getline(std::cin, str);

    for (const auto i : attacks) {
        if (i->getName() == str) return i;
    }

    return std::shared_ptr<Attack>();

}
