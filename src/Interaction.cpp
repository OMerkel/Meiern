#include "Interaction.h"
#include <iostream>
#include <string>

std::string Interaction::ask_name() {
    std::cout << "Enter your name: ";
    std::string name;
    std::getline(std::cin, name);
    return name;
}

void Interaction::output(const std::string& message) {
    std::cout << message << std::endl;
}
