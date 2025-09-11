#include "Greeting.h"
#include <string>

Greeting::Greeting(const std::string& name) : name_(name) {}

std::string Greeting::get_greeting() const {
    return "Hello, " + name_ + "!";
}
