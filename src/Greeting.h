#pragma once
#include <string>

class Greeting {
public:
    Greeting(const std::string& name);
    std::string get_greeting() const;
private:
    std::string name_;
};
