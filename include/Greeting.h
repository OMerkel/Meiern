/**
 * @file Greeting.h
 * @brief Declaration of the Greeting class.
 *
 * @author Oliver Merkel
 * @date 2025-10-14
 */
#pragma once
#include <string>

class Greeting {
public:
    Greeting(const std::string& name);
    std::string get_greeting() const;
private:
    std::string name_;
};
