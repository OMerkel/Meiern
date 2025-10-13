#pragma once
#include <iostream>
#include <string>

class Interaction {
public:
    static std::string ask_name();
    static void output(const std::string& message);
};
