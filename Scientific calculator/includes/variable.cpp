#include <iostream>

#include "variable.hpp"

Variable::Variable() {}

Variable::Variable(std::string val): value(val) {}

std::ostream &operator<<(std::ostream &os, const Variable &var) 
{
    return os << var.value;
}

std::string Variable::get_value() const 
{
    return value;
}    
